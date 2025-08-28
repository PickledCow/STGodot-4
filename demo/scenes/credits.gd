extends Control

var skip_timer := 0.0
var skip_requirement := 3.0

var skipped := false

func _ready() -> void:
	Engine.max_fps = 0
	$AnimationPlayer.play("credits")
	Input.mouse_mode = Input.MOUSE_MODE_VISIBLE

func _process(delta: float) -> void:
	if not skipped:
		if Input.is_action_pressed("pause"):
			skip_timer += delta
		else:
			skip_timer = max(skip_timer - delta * 2.0, 0.0)
		
		$Skip.modulate.a = skip_timer / skip_requirement
	
		if skip_timer >= skip_requirement:
			skipped = true
			$AnimationPlayer2.play("fade")

func _on_animation_player_2_animation_finished(_anim_name: StringName) -> void:
	get_tree().change_scene_to_packed(System.main_menu_scene)


func _on_animation_player_animation_finished(_anim_name: StringName) -> void:
	skipped = true
	$AnimationPlayer2.play("fade")
	$AnimationPlayer.play("off")
