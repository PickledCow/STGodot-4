class_name Enemy
extends Node2D

var ice_cube := preload("res://prefab/player/yuuma/ice_block.tscn")

@export var hitbox_radius := 16.0
@export var hurtbox_radius := 16.0
@export var invincible := false
@export var suck_only := false
@export var hurt_on_contact := true
@export var star_damage_multiplier := 1.0
@export var parasol_damage_multiplier := 1.0

@export var max_health := 100.0

var is_boss := false

var star_data : PackedFloat64Array

@export var ability : Player.PLAYER_ABILITY

var health: float

var velocity := Vector2()
var acceleration := Vector2()
var apply_max_velocity := false
var max_velocity := Vector2()

var difficulty : System.DIFFICULTY

var enemy_hitbox : PackedInt64Array

var t := 0
var t_float := 0.0

var invincibility_timer := 0.0

var in_timeout := false

enum DEATH_TYPE { NORMAL, DESPAWNED, SUCKED, FROZEN }
var how_i_died : DEATH_TYPE = DEATH_TYPE.NORMAL

var spark_effect : Sprite2D

var hurt_timer := 0.0
var hurt_flicker_timer := 0.0
var hurt_flicker_cycle := 10.0

var hit_bullet : PackedFloat64Array

var start_position : Vector2
var target_position : Vector2
var travel_time := -1.0
var travel_timer := -1.0
enum MOVEMENT_INTERPOLATION_TYPE { LINEAR, SMOOTH_OUT }
var movement_interpolation : MOVEMENT_INTERPOLATION_TYPE

var death_explosion := preload("res://prefab/death_explosion.tscn")
var spark_prefab := preload("res://prefab/boss/shock.tscn")

func set_destination(target: Vector2, time: float, interp: MOVEMENT_INTERPOLATION_TYPE = MOVEMENT_INTERPOLATION_TYPE.SMOOTH_OUT) -> void:
	if time <= 0.0:
		position = target
	else:
		start_position = position
		target_position = target
		travel_time = time
		travel_timer = time
		movement_interpolation = interp
		

func random_walk(bounds_start: Vector2, bounds_end: Vector2, max_movement: Vector2, time: float) -> void:
	var min_x : float = max(bounds_start.x, position.x - max_movement.x)
	var max_x : float = min(bounds_end.x, position.x + max_movement.x)
	var min_y : float = max(bounds_start.y, position.y - max_movement.y)
	var max_y : float = min(bounds_end.y, position.y + max_movement.y)
	set_destination(Vector2(randf_range(min_x, max_x), randf_range(min_y, max_y)), time)

func get_damage_taken() -> Array[PackedInt64Array]:
	return Bullets.get_enemy_collisions(enemy_hitbox)

func _ready() -> void:
	_pre_ready()
	health = max_health
	enemy_hitbox = Bullets.create_enemy(hitbox_radius, hurtbox_radius if hurt_on_contact else -1.0, not suck_only)
	
	star_data = System.get_item_data(System.ITEM_TYPE.STAR)
	star_data[Bullets.ITEM_DATA_DAMAGE_AMOUNT] = float(ability)
	
	difficulty = System.difficulty
	
	hit_bullet = PackedFloat64Array()
	hit_bullet.resize(15)
	hit_bullet[0] = 0 # source x (integer)
	hit_bullet[1] = 0 # source y (integer)
	hit_bullet[2] = 128				# source width (integer)
	hit_bullet[3] = 128				# source height (integer)
	hit_bullet[4] = 32				# bullet size [0, inf)
	hit_bullet[5] = 0 				# hitbox ratio [0, 1]
	hit_bullet[6] = 0					# Sprite offset y (integer)
	hit_bullet[7] = 1					# anim frame, 1 for no animation (integer)
	hit_bullet[8] = 0.25					# spin
	hit_bullet[9] = 1	# layer
	hit_bullet[10] = 1	# rgb
	hit_bullet[11] = 1
	hit_bullet[12] = 1
	hit_bullet[13] = System.DAMAGE_TYPE.NO_COLLISION			# damage type
	hit_bullet[14] = 0				# damage amount
	
	_post_ready()
	
func _movement() -> void:
	if travel_time > 0.0:
		travel_timer -= System.time_scale
		if travel_timer > 0.0:
			var prog := 1.0 - (travel_timer / travel_time)
			match movement_interpolation:
				MOVEMENT_INTERPOLATION_TYPE.SMOOTH_OUT:
					prog = 1.0 - (travel_timer / travel_time) * (travel_timer / travel_time)
			position = lerp(start_position, target_position, prog)
		else:
			position = target_position
			travel_time = -1.0
			travel_timer = -1.0
	elif velocity:
		position += velocity * System.time_scale
		velocity += acceleration * System.time_scale
		if apply_max_velocity:
			if acceleration.x and velocity.x * sign(acceleration.x) > abs(max_velocity.x):
				velocity.x = max_velocity.x
			if acceleration.y and velocity.y * sign(acceleration.y) > abs(max_velocity.y):
				velocity.y = max_velocity.y
	
func _process(_delta) -> void:
	
	
	var new_frame := false
	
	t_float += System.time_scale
	var new_t := int(t_float)
	if new_t > t:
		new_frame = true
		t = new_t
	
	if new_frame:
		_pre_process(System.time_scale)
	
	_movement()
	
	if not is_boss and ((not invincible and not System.enemy_active_rect.has_point(position)) or System.in_dialogue or System.clear_enemies):
		how_i_died = DEATH_TYPE.DESPAWNED
		_on_death()
		return
	
	# Offset makes attacks not disappear as fast
	Bullets.set_position(enemy_hitbox, position + Vector2(0, -16))
	
	
	var collisions : Array
	
	if not in_timeout:
		collisions = Bullets.get_enemy_collisions(enemy_hitbox)
	
	if not invincible:
		var died := false
		for bullet in collisions:
			var damage_type : int = Bullets.get_damage_type(bullet)
			var damage : float = Bullets.get_damage(bullet)
			var bullet_position : Vector2 = Bullets.get_position(bullet)
			
			match damage_type:
				System.DAMAGE_TYPE.NORMAL:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage
						_boss_hit_sfx()
						create_stars(bullet_position, 4)
				System.DAMAGE_TYPE.WATER:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage * parasol_damage_multiplier
						_boss_hit_sfx()
						if randf() > 0.6:
							create_stars(bullet_position, 1)
				System.DAMAGE_TYPE.CANOPY:
					if not suck_only and not is_boss and invincibility_timer <= 0.0:
						health -= damage
				System.DAMAGE_TYPE.STAR:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage * star_damage_multiplier
						SFX.play("break")
						SFX.play("enemy_hit")
						create_stars(bullet_position, 8)
						_boss_hit_sfx()
					
				System.DAMAGE_TYPE.STAR_STRONG:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage * star_damage_multiplier
						SFX.play("enemy_hit")
						create_stars(bullet_position, 12)
						_boss_hit_sfx()
				System.DAMAGE_TYPE.SUCK:
					if not is_boss:
						health = 0
						died = true
						how_i_died = DEATH_TYPE.SUCKED
						break
				System.DAMAGE_TYPE.CRIT:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage
						_boss_hit_sfx()
						create_stars(bullet_position, 16)
						if is_boss:
							SFX.play("crit")
				System.DAMAGE_TYPE.SNIPE:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage
						_boss_hit_sfx()
						create_stars(System.player.position, 20)
						if is_boss:
							SFX.play("crit")
				System.DAMAGE_TYPE.SHOCK:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage
						_boss_hit_sfx()
						if is_boss:
							spark_effect.show()
							spark_effect.shock_timer = 30.0
							SFX.play("plasma_shock")
				System.DAMAGE_TYPE.SHOCK_SHIELD:
					if not suck_only and not is_boss:
						health -= damage
				System.DAMAGE_TYPE.SHARP:
					if not suck_only:
						if invincibility_timer <= 0.0:
							health -= damage
						_boss_hit_sfx()
						create_stars(bullet_position, 6)
						if is_boss:
							SFX.play("slash_hit")
				System.DAMAGE_TYPE.CHILL:
					if invincibility_timer <= 0.0:
						health -= damage * 0.25 if is_boss else damage
						if health <= 0.0 and not is_boss:
							how_i_died = DEATH_TYPE.FROZEN
							SFX.play("freeze")
								
						_boss_hit_sfx()
						#SFX.play("enemy_hit")
			
		if health <= 0.0:
			died = true
	
		if died:
			_on_death()
	
	invincibility_timer -= System.time_scale
	
	if new_frame:
		_post_process(System.time_scale)

func _boss_hit_sfx():
	if is_boss:
		hurt_timer = max(hurt_timer, 30.0)
		SFX.play("boss_hurt_low" if health / max_health < 0.1 else "boss_hurt_high", 0.0, false)

func _pre_ready() -> void:
	pass

func _post_ready() -> void:
	pass

@warning_ignore("unused_parameter")
func _pre_process(time_scale: float) -> void:
	pass
	
@warning_ignore("unused_parameter")
func _post_process(time_scale: float) -> void:
	pass

func _pre_death():
	pass

func _post_death():
	pass


func create_stars(bullet_position: Vector2, count := 8) -> void:
	var ref_pos := position + Vector2(0.0, -16.0)
	var angle: float = ref_pos.angle_to_point(bullet_position)
	for i in count:
		var a := angle + randf_range(-0.4, 0.4) * PI
		var b = Bullets.create_shot_a1(position + Vector2(hurtbox_radius, 0.0).rotated(a), randf_range(2.0, 10.0), a, hit_bullet, false)
		Bullets.set_lifespan(b, randf_range(10, 15))
		Bullets.set_pierce(b, true)
		Bullets.set_spin(b, randf_range(0.25, 0.5) * (1.0 if randf() > 0.5 else -1.0))

func _on_death() -> void:
	_post_death()
	Bullets.clear_entity(enemy_hitbox)
	
	if how_i_died != DEATH_TYPE.DESPAWNED and how_i_died != DEATH_TYPE.SUCKED:
		SFX.play("enemy_death")
	
	match how_i_died:
		DEATH_TYPE.SUCKED:
			var item : PackedInt64Array = Bullets.create_item(position, 0.0, 0.0, 1.0, star_data, false)
			Bullets.set_item_magnet(item, System.player)
			System.player.declare_eated()
		DEATH_TYPE.FROZEN:
			var cube := ice_cube.instantiate()
			cube.position = position
			get_parent().add_child(cube)
	
	if how_i_died != DEATH_TYPE.SUCKED and how_i_died != DEATH_TYPE.DESPAWNED and how_i_died != DEATH_TYPE.FROZEN:
		var de : GPUParticles2D = death_explosion.instantiate()
		de.position = position
		de.emitting = true
		get_parent().add_child(de)
	
	
	queue_free()
