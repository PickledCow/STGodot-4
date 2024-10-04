extends Node
class_name GameInputManager
## Translates either live player input or replay input to be used by the player.
## Also removes issues with is_action_just_pressed/released with pauses.
##
## In the default system it is set up as a singleton named GameInput.

## List of player inputs applicable to the game.
var player_inputs := {}
## Player inputs in the previous frame.
var prev_player_inputs := {}

var is_replay := false

# -----------------------------------------------------------------------------
# Reimplementation of Input functions that works with pausing
# -----------------------------------------------------------------------------

func is_action_pressed(action: StringName) -> bool:
	return player_inputs[action]
	
func is_action_just_pressed(action: StringName) -> bool:
	return player_inputs[action] && not prev_player_inputs[action]
	
func is_action_just_released(action: StringName) -> bool:
	return not player_inputs[action] && prev_player_inputs[action]
	
# -----------------------------------------------------------------------------
# Input processor functions
# -----------------------------------------------------------------------------

## Register the player inputs and reject irrelevant inputs.
func register_inputs():
	for key in InputMap.get_actions():
		if key.begins_with("player"):
			player_inputs[key] = false
			prev_player_inputs[key] = false

## Function for updating input map for when playing the game
func process_live_inputs():
	for key in player_inputs:
		prev_player_inputs[key] = player_inputs[key]
		player_inputs[key] = Input.is_action_pressed(key)

## Function for updating input map for when going through a replay. TODO.
func process_replay_inputs():
	pass

# -----------------------------------------------------------------------------
# Yeah uh comments whoo
# -----------------------------------------------------------------------------

func _ready():
	register_inputs()

func _physics_process(delta):
	if is_replay:
		process_replay_inputs()
	else:
		process_live_inputs()
			
