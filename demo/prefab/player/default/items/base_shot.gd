extends BaseItem

var fire_rate := 3.0
var fire_timer := 0.0

var data: PackedFloat64Array

func _ready():
	data = PackedFloat64Array()
	data.resize(15)
	data[0] = 32*5 # source x (integer)
	data[1] = 0 # source y (integer)
	data[2] = 32*4				# source width (integer)
	data[3] = 32*4				# source height (integer)
	data[4] = 64.0				# bullet size [0, inf)
	data[5] = 0.5 # hitbox ratio [0, 1]
	data[6] = 0					# Sprite offset y (integer)
	data[7] = 1					# anim frame, 1 for no animation (integer)
	data[8] = 0					# spin
	data[9] = 0	# layer
	data[10] = 1	# rgb
	data[11] = 1
	data[12] = 1
	data[13] = 0				# damage type
	data[14] = 0				# damage amount

func process_item(time_scale: float, player_position: Vector2):
	if GameInput.is_action_just_pressed("player_shoot") and fire_timer < 0.0:
		fire_timer = 0.0
	
	if GameInput.is_action_pressed("player_shoot") and fire_timer <= 0.0:
		fire_timer += fire_rate
		SFX.play("base_shot")
		Bullets.create_shot_a1(player_position + Vector2(16, -12), 20, -PI * 0.5, data, false)
		Bullets.create_shot_a1(player_position + Vector2(-16, -12), 20, -PI * 0.5, data, false)
		
	fire_timer -= time_scale
