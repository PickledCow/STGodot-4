extends Node
class_name PlayerLoader
## Manages loading in and initializing the correct player object.
##
## Holds onto a list of player scenes and default values to set and loads one
## in at the start of the game.

@export var players : Array[PackedScene]

var current_player : Player




func instantiate_player(id: int):
	current_player = players[id].instantiate() as Player
	
	current_player.position = Vector2(1280 * 0.5, 600)
	
	get_parent().add_child.call_deferred(current_player)


func _ready():
	instantiate_player(0)
