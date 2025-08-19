extends Enemy
class_name Boss

func _ready() -> void:
	super()
	is_boss = true
	System.current_boss = self
	System.bg.set_boss_texture($Sprite.texture)

func _on_death() -> void:
	super()
	System.boss_manager.increment_boss()
