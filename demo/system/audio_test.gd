@tool
extends AudioStreamPlayer

## Keep track of sample position so it does not loop forever
var last_playback_position : float = 0.0

func _on_finished():
	stream = null
	volume_db = 0.0

func _process(_delta: float) -> void:
	if stream:
		var current_playback_position := get_playback_position()
		if current_playback_position < last_playback_position:
			stop()
			_on_finished()
			last_playback_position = 0.0
		else:
			last_playback_position = current_playback_position
