extends Node2D

var radius := 36.0
var velocity := Vector2(0.0, -18.0)

var lifespan := 60.0
var lifetime := 0.0

var regular_bomb : PackedFloat64Array
var crit_bomb : PackedFloat64Array
var self_damage : PackedFloat64Array

var bounced := false

var exploded := false

var explosion_radius := 128.0

var impact_bullet : PackedInt64Array

func _ready() -> void:
	regular_bomb = PackedFloat64Array()
	regular_bomb.resize(15)
	regular_bomb[0] = 0 # source x (integer)
	regular_bomb[1] = 0 # source y (integer)
	regular_bomb[2] = 0 				# source width (integer)
	regular_bomb[3] = 0				# source height (integer)
	regular_bomb[4] = explosion_radius				# bullet size [0, inf)
	regular_bomb[5] = 1 				# hitbox ratio [0, 1]
	regular_bomb[6] = 0					# Sprite offset y (integer)
	regular_bomb[7] = 1					# anim frame, 1 for no animation (integer)
	regular_bomb[8] = 0					# spin
	regular_bomb[9] = 1	# layer
	regular_bomb[10] = 1	# rgb
	regular_bomb[11] = 1
	regular_bomb[12] = 1
	regular_bomb[13] = System.DAMAGE_TYPE.NORMAL				# damage type
	regular_bomb[14] = 35				# damage amount
	
	crit_bomb = PackedFloat64Array()
	crit_bomb.resize(15)
	crit_bomb[0] = 0 # source x (integer)
	crit_bomb[1] = 0 # source y (integer)
	crit_bomb[2] = 0 				# source width (integer)
	crit_bomb[3] = 0				# source height (integer)
	crit_bomb[4] = explosion_radius				# bullet size [0, inf)
	crit_bomb[5] = 1 				# hitbox ratio [0, 1]
	crit_bomb[6] = 0					# Sprite offset y (integer)
	crit_bomb[7] = 1					# anim frame, 1 for no animation (integer)
	crit_bomb[8] = 0					# spin
	crit_bomb[9] = 1	# layer
	crit_bomb[10] = 1	# rgb
	crit_bomb[11] = 1
	crit_bomb[12] = 1
	crit_bomb[13] = System.DAMAGE_TYPE.CRIT				# damage type
	crit_bomb[14] = 40				# damage amount
	
	self_damage = PackedFloat64Array()
	self_damage.resize(15)
	self_damage[0] = 0 # source x (integer)
	self_damage[1] = 0 # source y (integer)
	self_damage[2] = 0 				# source width (integer)
	self_damage[3] = 0				# source height (integer)
	self_damage[4] = explosion_radius * 0.5				# bullet size [0, inf)
	self_damage[5] = 1 				# hitbox ratio [0, 1]
	self_damage[6] = 0					# Sprite offset y (integer)
	self_damage[7] = 1					# anim frame, 1 for no animation (integer)
	self_damage[8] = 0					# spin
	self_damage[9] = 1	# layer
	self_damage[10] = 1	# rgb
	self_damage[11] = 1
	self_damage[12] = 1
	self_damage[13] = 1			# damage type
	self_damage[14] = 1				# damage amount

	var impact_damage : PackedFloat64Array = PackedFloat64Array()
	impact_damage.resize(15)
	impact_damage[0] = 0 # source x (integer)
	impact_damage[1] = 0 # source y (integer)
	impact_damage[2] = 0 				# source width (integer)
	impact_damage[3] = 0				# source height (integer)
	impact_damage[4] = radius*1.5				# bullet size [0, inf)
	impact_damage[5] = 1 				# hitbox ratio [0, 1]
	impact_damage[6] = 0					# Sprite offset y (integer)
	impact_damage[7] = 1					# anim frame, 1 for no animation (integer)
	impact_damage[8] = 0					# spin
	impact_damage[9] = 1	# layer
	impact_damage[10] = 1	# rgb
	impact_damage[11] = 1
	impact_damage[12] = 1
	impact_damage[13] = System.DAMAGE_TYPE.NORMAL			# damage type
	impact_damage[14] = 15				# damage amount
	
	impact_bullet = Bullets.create_shot_a1(position, 18.0, -PI * 0.5, impact_damage, false)
	Bullets.set_pierce(impact_bullet, true)

func _process(_delta: float) -> void:
	if System.current_boss:
		#var distance : Vector2 = System.current_boss.position - position
		#var enemy_radius : float = System.current_boss.hitbox_radius
		
		#if not bounced and distance.length_squared() < (enemy_radius + radius) * (enemy_radius + radius):
		var collisions : Array = Bullets.get_enemies_in_range(position, radius)
		if not bounced and collisions.size() > 0:
			# Just go off first collision
			var distance : Vector2 = Bullets.get_position(collisions[0]) - position
			position -= velocity
			var angle := distance.angle() + PI
			velocity = Vector2(8.0, 0.0).rotated(angle)
			bounced = true
			SFX.play("item")
			Bullets.set_lifespan(impact_bullet, 0)
			
	
	position += velocity * System.time_scale
	lifetime += System.time_scale
	rotation += 0.05 * System.time_scale
	
	if lifetime >= lifespan and not exploded:
		var explosion_type := crit_bomb if bounced else regular_bomb
		var b = Bullets.create_shot_a1(position, 0.0,  0.0, explosion_type, false)
		Bullets.set_lifespan(b, 2)
		Bullets.set_pierce(b, true)
		
		var sb = Bullets.create_bullet_a1(position, 0.0,  0.0, self_damage, false)
		Bullets.set_lifespan(sb, 2)
		Bullets.skip_fade(sb)
		
		SFX.play("explode")
		$Sprite2D.hide()
		$Flames.emitting = true
		$Smoke.emitting = true
		exploded = true
		


func _on_flames_finished() -> void:
		queue_free()
