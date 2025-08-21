extends Control
class_name PauseMenu

# SO lazy this is also just any persistent shit
func _ready():
	get_viewport().focus_exited.connect(_on_window_focus_out)
	get_tree().paused = true

func _on_window_focus_out():
	if not get_tree().paused:
		pause()

func _process(_delta: float) -> void:
	if Input.is_action_just_pressed("pause"):
		if get_tree().paused:
			unpause()
		else:
			pause()
	
	
	Input.mouse_mode = Input.MOUSE_MODE_HIDDEN if not get_tree().paused and Rect2(Vector2(460, 40), Vector2(1000, 1000)).has_point(get_global_mouse_position()) else Input.MOUSE_MODE_VISIBLE

func pause():
	get_tree().paused = true
	$Pause.play()
	

func unpause():
	get_tree().paused = false
