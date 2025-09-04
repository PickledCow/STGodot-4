extends Sprite2D

var shock_timer := 0.0
var anim_timer := 0.0
var last_frame := 0

func _process(delta: float) -> void:
	
	shock_timer -= System.time_scale
	if shock_timer < 0.0:
		hide()
	else:
		anim_timer -= delta * 6.0
		
		while anim_timer < 0.0:
			anim_timer += 1.0
		
		frame = 0 if anim_timer < 0.5 else 1
		
		if last_frame != frame:
			rotation = randf()*TAU
		last_frame = frame
	
