extends Node
class_name GameSystem
## The default system holding onto most global data that is not part of the 
## STGodot environment.
##
## arshtaoit
## @experimental

@onready var bullet_constructor := $BulletConstructor

var playfield_size := Vector2(1280, 720)

func get_bullet_data(type: int, color: int) -> PackedFloat64Array:
	return bullet_constructor.get_bullet_data(type, color)
	
func get_item_data(type: int) -> PackedFloat64Array:
	return bullet_constructor.get_item_data(type)
	
