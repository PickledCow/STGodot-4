extends Enemy


var bounce_count := 2
var decay_factor := 0.8

func _post_process(_time_scale: float) -> void:
	if bounce_count > 0:
		if position.x < 0.0:
			position.x *= -1.0
			bounce_count -= 1
			velocity.x *= -decay_factor
		if position.x > 1000.0:
			position.x = 2000.0 - position.x
			bounce_count -= 1
			velocity.x *= -decay_factor
		if position.y < 0.0:
			position.y *= -1.0
			bounce_count -= 1
			velocity.y *= -decay_factor
	
	Bullets.clear_bullets(position, hitbox_radius * 2.0, false)
	
	rotation += 0.05
