extends Control
class_name UIManager

func _ready() -> void:
	System.ui = self

func set_health(health: float) -> void:
	$RightBar/Healthbar/ProgressBar.value = health

func update_name(new_name: String) -> void:
	$RightBar/Healthbar/Name. text = new_name
