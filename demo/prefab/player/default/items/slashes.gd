extends BaseItem

var fire_rate := [72.0, 66.0, 66.0, 60.0, 60.0, 53.0, 53.0, 48.0]
var fire_timer := 0.0

var subsequent_slash_delay := 4.0
var subsequent_slash_timer := 0.0
var subsequent_slash_count := 0

var animation_speed := 1.0

var slash_count := 2

var slash_frames : Array[float] = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]

func upgrade_to_level(next_level: int):
	slash_count = (int(level + 1) / 2) * 2

func process_item(time_scale: float, _player_position: Vector2):
	for i in 8:
		slash_frames[i]  += animation_speed * time_scale
	
	fire_timer -= time_scale
	subsequent_slash_timer -= time_scale
	
	for i in 8:
		if slash_frames[i] >= 8.0:
			get_child(i).hide()
	
	if GameInput.is_action_just_pressed("player_shoot") and fire_timer < 0.0:
		fire_timer = 0.0
	
	if GameInput.is_action_pressed("player_shoot") and fire_timer <= 0.0:
		fire_timer += fire_rate[level - 1]
		slash_frames[0] = 0.0
		subsequent_slash_timer = subsequent_slash_delay
		subsequent_slash_count = slash_count - 1
		get_child(0).show()
		SFX.play("slash_air")
		
	if subsequent_slash_timer <= 0.0 and subsequent_slash_count > 0:
		subsequent_slash_count -= 1
		var slash = slash_count-subsequent_slash_count - 1
		slash_frames[slash] = 0.0
		subsequent_slash_timer = subsequent_slash_delay
		get_child(slash).show()
		SFX.play("slash_air")
		
		#
	for i in 8:
		get_child(i).frame = min(slash_frames[i], 7)
	
	#$LSlash.frame = l_frame
	#$RSlash.frame = r_frame
	
	
	
