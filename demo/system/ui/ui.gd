extends Control
class_name UIManager

var attack_index := 0
var attack_names : Array[String]

func _ready() -> void:
	System.ui = self

func set_health(health: float) -> void:
	$RightBar/Healthbar/ProgressBar.value = health

func set_boss_health(norm_health: float) -> void:
	$MiddleUI/TopBar/Healthbar/ProgressBar.value = 0.075 + norm_health * (1.0 - 0.075)
	$MiddleUI/TopBar/Healthbar/ProgressBar/Percent.text = str(int(floor(norm_health * 100.0))) + "%"
	$MiddleUI/TopBar/Healthbar/ProgressBar/Percent.position.x = -41.0 + (690.0 + 41.0) * norm_health


func update_name(new_name: String) -> void:
	$RightBar/Healthbar/Name.text = new_name

func update_boss_data(boss_name: String, boss_attacks: Array[System.ATTACK_TYPE], names : Array[String]) -> void:
	$MiddleUI/TopBar/Healthbar/Name.text = boss_name
	attack_index = boss_attacks.size() - 1
	names.reverse()
	attack_names = names
	boss_attacks.reverse() # First in first out
	for i in 6:
		var icon_container : Control = get_node("MiddleUI/TopBar/SecondBar/Spells/" + str(i))
		
		get_node("MiddleUI/TopBar/SecondBar/Spells/" + str(i) + "/Timer").start()
		if i < boss_attacks.size():
			icon_container.show()
			var icon : TextureRect = get_node("MiddleUI/TopBar/SecondBar/Spells/" + str(i) + "/Clip/Icon")
			var glow : TextureRect = get_node("MiddleUI/TopBar/SecondBar/Spells/" + str(i) + "/Clip/Glow")
			var offset : float = (boss_attacks[i] + 1.0) * -64.0
			icon.position.x = offset
			glow.position.x = offset
			
		else:
			icon_container.hide()

func increment_attack():
	if attack_index >= 0:
		get_node("MiddleUI/TopBar/SecondBar/Spells/" + str(attack_index) + "/AnimationPlayer").play("fade_out")
		$MiddleUI/SpellName/AnimationPlayer.play("spawn")
	$MiddleUI/SpellName/Text.text = attack_names[attack_index]
	attack_index -= 1
