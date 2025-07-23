extends Label

func _process(_delta: float) -> void:
	text = (
"FPS: " + str(Engine.get_frames_per_second()) + 
"\nBullets: " + str(Bullets.get_active_bullets()) + 
"\nShots: " + str(Bullets.get_active_shots()) + 
"\nItems: " + str(Bullets.get_active_items()) + 
"\nLasers: " + str(Bullets.get_active_lasers()) + 
"\nCurve Lasers: " + str(Bullets.get_active_curve_lasers())
)
