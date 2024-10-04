@tool
extends AudioStreamPlayer

func _on_finished():
	stream = null
	volume_db = 0.0
