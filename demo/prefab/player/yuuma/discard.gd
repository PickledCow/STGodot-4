extends Node2D


func _ready():
	$AnimationPlayer.play("arst")

func play_sfx():
	SFX.play("break")


func _on_animation_player_animation_finished(_anim_name: StringName) -> void:
	queue_free()
