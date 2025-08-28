extends Node2D

var ice_cube : PackedFloat64Array
var invisible_cube : PackedFloat64Array

var static_collision_bullet : PackedInt64Array

func _ready() -> void:
	ice_cube = PackedFloat64Array()
	ice_cube.resize(15)
	ice_cube[0] = 128*2 # source x (integer)
	ice_cube[1] = 128*3 # source y (integer)
	ice_cube[2] = 128				# source width (integer)
	ice_cube[3] = 128				# source height (integer)
	ice_cube[4] = 128				# bullet size [0, inf)
	ice_cube[5] = 0 				# hitbox ratio [0, 1]
	ice_cube[6] = 0					# Sprite offset y (integer)
	ice_cube[7] = 1					# anim frame, 1 for no animation (integer)
	ice_cube[8] = 0					# spin
	ice_cube[9] = 1	# layer
	ice_cube[10] = 1	# rgb
	ice_cube[11] = 1
	ice_cube[12] = 1
	ice_cube[13] = System.DAMAGE_TYPE.STAR			# damage type
	ice_cube[14] = 70				# damage amount
	
	invisible_cube = PackedFloat64Array()
	invisible_cube.resize(15)
	invisible_cube[0] = 128*1 # source x (integer)
	invisible_cube[1] = 128*3 # source y (integer)
	invisible_cube[2] = 128				# source width (integer)
	invisible_cube[3] = 128				# source height (integer)
	invisible_cube[4] = 128				# bullet size [0, inf)
	invisible_cube[5] = 0 				# hitbox ratio [0, 1]
	invisible_cube[6] = 0					# Sprite offset y (integer)
	invisible_cube[7] = 1					# anim frame, 1 for no animation (integer)
	invisible_cube[8] = 0					# spin
	invisible_cube[9] = 1	# layer
	invisible_cube[10] = 1	# rgb
	invisible_cube[11] = 1
	invisible_cube[12] = 1
	invisible_cube[13] = System.DAMAGE_TYPE.STAR			# damage type
	invisible_cube[14] = 70				# damage amount
	
	static_collision_bullet = Bullets.create_shot_a1(position, 0, 0, invisible_cube, false)
	Bullets.set_lifespan(static_collision_bullet, 600)
	
func _process(_delta: float) -> void:
	if not Bullets.is_valid(static_collision_bullet):
		queue_free()
		return
	
	var player_position : Vector2 = System.player.position
	
	if position.distance_squared_to(player_position) < 64 * 64:
		var boss_position : Vector2 = position + Vector2.UP
		if System.current_boss:
			boss_position = System.current_boss.position
		Bullets.set_lifespan(static_collision_bullet, -1)
		var angle : float = position.angle_to_point(boss_position)
		var kicked_bullet = Bullets.create_shot_a1(position, 20.0, angle, ice_cube, false)
		Bullets.set_rotation(kicked_bullet, -angle - PI * 0.5)
		SFX.play("ice_kick")
		queue_free()
		
	
	
