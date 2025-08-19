class_name Enemy
extends Node2D

@export var hitbox_radius := 16.0
@export var hurtbox_radius := 16.0
@export var suck_only := false
@export var hurt_on_contact := true
@export var star_damage_multiplier := 1.0

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

enum DEATH_TYPE { NORMAL, DESPAWNED, SUCKED, FROZEN }
var how_i_died : DEATH_TYPE = DEATH_TYPE.NORMAL

var start_position : Vector2
var target_position : Vector2
var travel_time := -1.0
var travel_timer := -1.0
enum MOVEMENT_INTERPOLATION_TYPE { LINEAR, SMOOTH_OUT }
var movement_interpolation : MOVEMENT_INTERPOLATION_TYPE

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
	health = max_health
	enemy_hitbox = Bullets.create_enemy(hitbox_radius, hurtbox_radius if hurt_on_contact else -1.0, not suck_only)
	
	star_data = System.get_item_data(System.ITEM_TYPE.STAR)
	star_data[Bullets.ITEM_DATA_DAMAGE_AMOUNT] = float(ability)
	
	difficulty = System.difficulty
	
	_post_ready()
	
func _process(_delta) -> void:
	var new_frame := false
	t_float += System.time_scale
	var new_t := int(t_float)
	if new_t > t:
		new_frame = true
		t = new_t
	
	if new_frame:
		_pre_process(System.time_scale)
	
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
	else:
		position += velocity * System.time_scale
		velocity += acceleration * System.time_scale
		if apply_max_velocity:
			if acceleration.x and velocity.x * sign(acceleration.x) > abs(max_velocity.x):
				velocity.x = max_velocity.x
			if acceleration.y and velocity.y * sign(acceleration.y) > abs(max_velocity.y):
				velocity.y = max_velocity.y
	
	if not is_boss and not System.enemy_active_rect.has_point(position):
		how_i_died = DEATH_TYPE.DESPAWNED
		_on_death()
		return
	
	# Offset makes attacks not disappear as fast
	Bullets.set_position(enemy_hitbox, position + Vector2(0, -16))
	
	
	var collisions : Array = Bullets.get_enemy_collisions(enemy_hitbox)
	
	var died := false
	
	for bullet in collisions:
		var damage_type : int = Bullets.get_damage_type(bullet)
		var damage : float = Bullets.get_damage(bullet)
		
		match damage_type:
			System.DAMAGE_TYPE.NORMAL:
				if not suck_only:
					health -= damage
			System.DAMAGE_TYPE.CANOPY:
				if not suck_only and not is_boss:
					health -= damage
			System.DAMAGE_TYPE.STAR:
				if not suck_only:
					health -= damage * star_damage_multiplier
					SFX.play("break")
					SFX.play("enemy_hit")
			System.DAMAGE_TYPE.STAR_STRONG:
				if not suck_only:
					health -= damage * star_damage_multiplier
					SFX.play("enemy_hit")
			System.DAMAGE_TYPE.SUCK:
				if not is_boss:
					health = 0
					died = true
					how_i_died = DEATH_TYPE.SUCKED
					break
			System.DAMAGE_TYPE.CRIT:
				if not suck_only:
					health -= damage
					if is_boss:
						SFX.play("crit")
		
		if health <= 0.0:
			died = true
			break
	if died:
		_on_death()
	
	if new_frame:
		_post_process(System.time_scale)

func _post_ready() -> void:
	pass

@warning_ignore("unused_parameter")
func _pre_process(time_scale: float) -> void:
	pass
	
@warning_ignore("unused_parameter")
func _post_process(time_scale: float) -> void:
	pass

func _post_death():
	pass

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
	
	queue_free()
