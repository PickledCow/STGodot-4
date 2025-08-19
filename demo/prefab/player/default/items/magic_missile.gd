extends BaseItem

var fire_rate := 8.0
var fire_timer := 0.0

var data: PackedFloat64Array

var option_positions = [
	[Vector2(0, -16)],
	[Vector2(-20, -16), Vector2(20, -16)],
	[Vector2(-32, -12), Vector2(0, -20), Vector2(32, -12)],
	[Vector2(-40, -12), Vector2(-13.5, -20), Vector2(13.5, -20), Vector2(40, -12)],
	[Vector2(-46, -12), Vector2(-23, -16), Vector2(0, -20), Vector2(23, -16), Vector2(46, -12)],
	[Vector2(-52, -12), Vector2(-30, -16), Vector2(-10, -20), Vector2(10, -20), Vector2(30, -16), Vector2(52, -12)],
	[Vector2(-56, -12), Vector2(-37, -14), Vector2(-19, -17), Vector2(0, -20), Vector2(19, -17), Vector2(37, -14), Vector2(56, -12)],
	[Vector2(-60, -12), Vector2(-43, -14), Vector2(-26, -17), Vector2(-9, -20), Vector2(9, -20), Vector2(26, -17), Vector2(43, -14), Vector2(60, -12)],
]

func _ready():
	data = PackedFloat64Array()
	data.resize(15)
	data[0] = 0 # source x (integer)
	data[1] = 0 # source y (integer)
	data[2] = 32*6				# source width (integer)
	data[3] = 32*6				# source height (integer)
	data[4] = 96.0				# bullet size [0, inf)
	data[5] = 0.35 # hitbox ratio [0, 1]
	data[6] = 0					# Sprite offset y (integer)
	data[7] = 1					# anim frame, 1 for no animation (integer)
	data[8] = 0					# spin
	data[9] = 1	# layer
	data[10] = 1	# rgb
	data[11] = 1
	data[12] = 1
	data[13] = 0				# damage type
	data[14] = 10				# damage amount


func upgrade_to_level(_next_level: int):
	for i in get_child_count():
		var option = get_child(i)
		option.visible = i < level
		if i < level:
			option.position = option_positions[level-1][i] * 1.5

func process_item(time_scale: float, player_position: Vector2):
	#position = player_position
	if GameInput.is_action_just_pressed("player_shoot") and fire_timer < 0.0:
		fire_timer = 0.0
	
	if GameInput.is_action_pressed("player_shoot") and fire_timer <= 0.0:
		fire_timer += fire_rate
		SFX.play("missile")
		for i in level:
			Bullets.create_shot_a2(player_position + option_positions[level-1][i] * 1.5, 0.0, -PI * 0.5, 0.5, 12.0, 0.0, data, false)
			
		
	fire_timer -= time_scale
	#print(fire_timer)

func _process(delta: float) -> void:
	for option in get_children():
		option.rotate(delta * 1.5)
