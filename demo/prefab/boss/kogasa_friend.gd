extends Enemy

var position_trail : PackedVector2Array

var initial_catchup := true

func _post_ready() -> void:
	position_trail.resize(5)
	
func _post_process(_time_scale: float) -> void:
	var targ_position : Vector2 = System.player.position + Vector2(-150, -150)
	if initial_catchup:
		if (targ_position - position).length_squared() < 50 * 50:
			initial_catchup = false
			position = targ_position
			for i in 5:
				position_trail[4-i] = position
		else:
			position = lerp(position, targ_position, 0.1)
	else:
		for i in 4:
			position_trail[4-i] = position_trail[4-i-1]
		position_trail[0] = targ_position
		
		position = position_trail[4]
	Bullets.clear_bullets(position, hitbox_radius * 2.0)
	
	rotation += 0.05
