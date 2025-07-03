class_name BaseItem
extends Node2D

@export var level := 1
@export var max_level := 8

func _upgrade_to_level(next_level: int):
	level = next_level
	upgrade_to_level(next_level)
	
func upgrade_to_level(_next_level: int):
	pass

func process_item(_time_scale: float, _player_position: Vector2):
	pass
