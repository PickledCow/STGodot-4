extends Node2D

var time := 0.0

func _process(delta: float) -> void:
	time += delta
	
	rotation = sin(time * 0.5) * 0.25
	$Refraction.material.set("shader_parameter/rotation", rotation)
	
