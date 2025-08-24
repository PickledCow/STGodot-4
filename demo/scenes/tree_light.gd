extends OmniLight3D

var t := 0.0

func _process(delta: float) -> void:
	t += delta
	
	light_energy = 4.0 + 1.5 * sin(t)
	
