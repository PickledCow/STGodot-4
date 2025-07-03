extends BaseItem

const LASER_WIDTH := 0.75
const GLOW_WIDTH := 0.5

var laser_fade_in_time := 6.0
var laser_fade_in_timer := 0.0

func upgrade_to_level(next_level: int):
	var middle = level / 2
	var angle_dif = TAU / 24.0
	for i in level:
		var laser := $Lasers.get_child(i)
		var glow := $Glows.get_child(i)
		var angle = angle_dif * (i - middle) if level % 2 == 1 else angle_dif * (i - middle + 0.5)
		laser.position = Vector2(96, 0).rotated(angle + PI*0.5) + Vector2(0, -32)
		laser.rotation = -angle * 0.5 - PI * 0.5
		
		glow.position = Vector2(96, 0).rotated(angle + PI*0.5) + Vector2(0, -32)

func process_item(time_scale: float, _player_position: Vector2):
	if GameInput.is_action_just_pressed("player_shoot"):
		laser_fade_in_timer = laser_fade_in_time
		for i in level:
			var laser := $Lasers.get_child(i)
			var glow := $Glows.get_child(i)
			if laser_fade_in_timer >= laser_fade_in_time:
				laser.show()
				glow.show()
	if GameInput.is_action_just_released("player_shoot"):
		laser_fade_in_timer = 0.0
	
	laser_fade_in_timer -= time_scale if GameInput.is_action_pressed("player_shoot") else -time_scale
	if laser_fade_in_timer < 0.0:
		laser_fade_in_timer = 0.0
	if laser_fade_in_timer > laser_fade_in_timer:
		laser_fade_in_timer = laser_fade_in_timer
	
	for i in level:
		var laser := $Lasers.get_child(i)
		var glow := $Glows.get_child(i)
		if laser_fade_in_timer >= laser_fade_in_time:
			laser.hide()
			glow.hide()
		laser.scale.y = LASER_WIDTH * (1.0 - laser_fade_in_timer / laser_fade_in_time)
		glow.scale = Vector2.ONE * GLOW_WIDTH * (1.0 - laser_fade_in_timer / laser_fade_in_time)
		
func _process(delta: float) -> void:
	for i in level:
		var glow := $Glows.get_child(i)
		glow.rotation += 2.3999632297
	
	
