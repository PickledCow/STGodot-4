extends Control
class_name UIManager

var attack_index := 0
var attack_names : Array[String]

var prev_timer := 0

const DIFFICULTY_TEXTS : PackedStringArray = ["EASY", "NORMAL", "HARD", "LUNATIC", "OVERDRIVE"]
const DIFFICULTY_COLOURS : PackedColorArray = [Color("00902c"), Color("0054b2"), Color("0009c5"), Color("9700a0"), Color("bd0000")]

var player_close := false

func _ready() -> void:
	System.ui = self
	
	$RightBar/DifficultyText/Label.text = DIFFICULTY_TEXTS[System.difficulty]
	$RightBar/DifficultyText/Label.add_theme_color_override("font_outline_color", DIFFICULTY_COLOURS[System.difficulty])

func set_health(health: float) -> void:
	$RightBar/Healthbar/ProgressBar.value = health + 0.5

	
func set_boss_health(norm_health: float) -> void:
	$MiddleUI/TopBar/Healthbar/ProgressBar.value = 0.075 + norm_health * (1.0 - 0.075)
	$MiddleUI/TopBar/Healthbar/ProgressBar/Percent.text = str(int(floor(norm_health * 100.0))) + "%"
	$MiddleUI/TopBar/Healthbar/ProgressBar/Percent.position.x = -41.0 + (690.0 + 41.0) * norm_health
	$MiddleUI/TopBar/Healthbar/ProgressBar.material.set_shader_parameter("progress", 0.075 + norm_health * (1.0 - 0.075))

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

func slide_in_top_bar(reversed := false):
	if not reversed:
		$MiddleUI/TopBar/BarAnimator.play("fade_in")
	else:
		$MiddleUI/TopBar/BarAnimator.play_backwards("fade_in")
		$MiddleUI/SpellName/AnimationPlayer.play("out")
		$MiddleUI/Timer/TimerFader.play("exit")

func proximity_fade(reversed := false):
	if not reversed and not player_close:
		player_close = true
		$MiddleUI/TopBar/ProximityFade.play("fade_out")
	elif reversed and player_close:
		player_close = false
		$MiddleUI/TopBar/ProximityFade.play_backwards("fade_out")

func fade_in_timer():
	set_timer(60)
	$MiddleUI/Timer/TimerFader.play("entry")

func show_halo():
	$RightBar/Healthbar/Halo.show()
	$RightBar/Healthbar/ProgressBar/HaloShadow.show()

func set_timer(time: float) -> void:
	var whole_int : int = int(floor(time))
	if whole_int < prev_timer:
		if whole_int < 3:
			SFX.play("timer2")
		elif whole_int < 10:
			SFX.play("timer1")
	prev_timer = whole_int
	 
	var whole : String = str(whole_int)
	var dec : String = str(int(floor((time - floor(time)) * 100)))
	while dec.length() < 2:
		dec += '0'
		
	$MiddleUI/Timer/Integer.text = whole
	$MiddleUI/Timer/Decimal.text = dec
	
func fill_healthbar():
	$MiddleUI/TopBar/BarFill.play("fill")
	SFX.play("bar_fill")

func game_over():
	$PauseMenu.game_over()

func now_playing(song_name: String):
	$MiddleUI/NowPlaying/HBoxContainer/SongName.text = song_name
	$MiddleUI/NowPlaying/AnimationPlayer.play("song")
