extends Node2D

var shake_intensity := 0.0
var shake_time := 0.0

@onready var origin := position

func shake_screen(intensity: float, duration: float):
	shake_intensity = intensity
	shake_time = duration

func _ready() -> void:
	Bullets.init(self)
	System.root = self

func _process(_delta: float) -> void:
	if shake_time > 0.0:
		shake_time -= System.time_scale
		if shake_time > 0.0:
			position = origin + Vector2(randf() * shake_intensity, 0.0).rotated(randf()*TAU)
		else:
			position = origin
	
