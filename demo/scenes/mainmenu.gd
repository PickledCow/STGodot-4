extends Control

@export var star_paths : Array[NodePath] = []
var stars : Array[TextureRect] = []

var sprites : Array[CompressedTexture2D] = [
	preload("res://prefab/boss/futo.png"),
	preload("res://prefab/boss/cirno.png"),
	preload("res://prefab/boss/kogasa.png"),
	preload("res://prefab/boss/marisa.png"),
	preload("res://prefab/boss/sanae.png"),
	preload("res://prefab/boss/megumu.png"),
	preload("res://prefab/boss/youmu.png")
]

var ABILITY_DESCRIPTIONS : PackedStringArray = PackedStringArray([
'''Suck in enemies with [Z] and spit them back at the enemy with [Z].
With something in your mouth, press [X] to swallow and take on their powers!
When you have a different ability, press [C] to discard the ability.
Recommended for a first playthrough.''',
'''Throw sharp boomerangs that return back to you shortly after thrown. 
Can be thrown both forwards and backwards using [Z] and [X].

Move around while unfocused to change your aim and focus [Shift] to lock.''',
'''Hold [Z] to breath freezing ice on enemies to freeze them into solid blocks of ice.

Touch ice blocks to kick them into the boss for massive damage.''',
'''Block incoming bullets with your canopy by holding down [Z].

Pressing [Z] also shoots out a shotgun of water pellets that rapidly lose damage as it travels.''',
'''Wiggle around rapidly and graze bullets to build up static charge and release the stored power with [Z].

The strength and properties of the fired shot varies depending on how much charge you've built up.''',
'''Hold down [Z] to start charging your bomb and release to throw.
Time your bombs so that they explode right after hitting the boss for a large boost of damage.
Be careful not to charge for too long or the bomb will explode in your face.''',
'''Hold down [Z] to scope in and take aim.
Release [Z] to shoot at where you're aiming for massive amounts of damage.

After shooting, time your [Z] press to the red area for an "Active Reload" to be able to shoot again earlier.''',
'''Press [Z] to swing your sword and slice up your enemies.  The type of swing changes depending on if you're either focused or unfocused.

Press [X] just before you're about to get hit to parry the attack.''',
'''Spooky'''
])

var stats = [
	[9, 5, 2, 5], # Normal	21
	[3, 7, 8, 3], # Cutter	21
	[5, 3, 6, 6], # Freeze	20
	[4, 2, 5, 9], # Parasol	220
	[5, 4, 5, 7], # Spark	21
	[7, 4, 5, 5], # Bomb	21
	[8, 9, 5, 1], # Sniper	23
	[3, 1, 9, 6], # Sword	20
	[1, 1, 1, 1]  # Ghost	
]

enum MENUS { MAIN, DIFFICULTY, ABILITY, OPTIONS }
enum MAIN_MENU_SELECTIONS { START, OPTIONS, QUIT }
enum ABILITY_SELECTIONS { NORMAL, CUTTER, FREEZE, PARASOL, SPARK, BOMB, SNIPER, SWORD }
enum STAT_ORDER { POWER, RANGE, FIRERATE, DIFFICULTY }

var current_menu : MENUS = MENUS.MAIN

var main_menu_selection := 0
var difficulty_selection : System.DIFFICULTY = System.DIFFICULTY.NORMAL
var ability_selection : ABILITY_SELECTIONS = ABILITY_SELECTIONS.NORMAL

var ui_lock := true

var power_bar_timer := 0.0
var range_bar_timer := 0.0
var firerate_bar_timer := 0.0
var difficulty_bar_timer := 0.0

var power_bar_start := 0.0
var range_bar_start := 0.0
var firerate_bar_start := 0.0
var difficulty_bar_start := 0.0

var power_bar_end := 0.0
var range_bar_end := 0.0
var firerate_bar_end := 0.0
var difficulty_bar_end := 0.0

var bar_drain_rate := 5.0

@onready var power_bar = $Ability/BoxContainer/MarginContainer/HBoxContainer/VBoxContainer/DescriptionBoxMargin/DescriptionBox/Stats/Power/ProgressBar
@onready var range_bar = $Ability/BoxContainer/MarginContainer/HBoxContainer/VBoxContainer/DescriptionBoxMargin/DescriptionBox/Stats/Range/ProgressBar
@onready var firerate_bar = $Ability/BoxContainer/MarginContainer/HBoxContainer/VBoxContainer/DescriptionBoxMargin/DescriptionBox/Stats/Firerate/ProgressBar
@onready var difficulty_bar = $Ability/BoxContainer/MarginContainer/HBoxContainer/VBoxContainer/DescriptionBoxMargin/DescriptionBox/Stats/Difficulty/ProgressBar
@onready var description_label = $Ability/BoxContainer/MarginContainer/HBoxContainer/VBoxContainer/DescriptionBoxMargin/DescriptionBox/PanelContainer/MarginContainer/VBoxContainer/Description

func _ready() -> void:
	Engine.max_fps = 0
	get_tree().paused = false
	$MenuAnimator.play("intro")
	Input.mouse_mode = Input.MOUSE_MODE_VISIBLE
	
	var sprite_id := randi()%7
	$PortraitContainer/Character.texture = sprites[sprite_id]
	$PortraitContainer/Character/Shadow.texture = sprites[sprite_id]
	
	if System.just_booted:
		System.just_booted = false
	else:
		$Splash/Disclaimer.hide()
	
	for path in star_paths:
		stars.append(get_node(path))
	
	power_bar_timer = 1.0
	range_bar_timer = 1.0
	firerate_bar_timer = 1.0
	difficulty_bar_timer = 1.0
	
	power_bar_start = power_bar.value * 10 - 1
	range_bar_start = range_bar.value * 10 - 1
	firerate_bar_start = firerate_bar.value * 10 - 1
	difficulty_bar_start = difficulty_bar.value * 10 - 1
	
	power_bar_end = stats[0][STAT_ORDER.POWER]
	range_bar_end = stats[0][STAT_ORDER.RANGE]
	firerate_bar_end = stats[0][STAT_ORDER.FIRERATE]
	difficulty_bar_end = stats[0][STAT_ORDER.DIFFICULTY]

	

func start_sway() -> void:
	$LogoSwayAnimator.play("sway")


func main_menu() -> void:
	if Input.is_action_just_pressed("player_up"):
		main_menu_selection += MAIN_MENU_SELECTIONS.size() - 1
		SFX.play("menu_select")
	if Input.is_action_just_pressed("player_down"):
		main_menu_selection += 1
		SFX.play("menu_select")
	
	main_menu_selection %= MAIN_MENU_SELECTIONS.size()
	
	if Input.is_action_just_pressed("player_bomb"):
		main_menu_selection = MAIN_MENU_SELECTIONS.QUIT
		SFX.play("menu_cancel")	
	
	if Input.is_action_just_pressed("player_shoot"):
		match main_menu_selection:
			MAIN_MENU_SELECTIONS.START:
				$MenuAnimator.play("main2difficulty")
				SFX.play("menu_ok")
				current_menu = MENUS.DIFFICULTY
				ui_lock = true
			MAIN_MENU_SELECTIONS.OPTIONS:
				$MenuAnimator.play("main2options")
				SFX.play("menu_ok")
				current_menu = MENUS.OPTIONS
				ui_lock = true
			MAIN_MENU_SELECTIONS.QUIT:
				SFX.play("menu_cancel")
				get_tree().quit()
	
	for i in MAIN_MENU_SELECTIONS.size():
		var selection_icon : TextureRect = $MainMenu/VBoxContainer/OptionsMargin/OptionsContainer.get_child(i).get_node("SelectionContainer/Selection")
		selection_icon.visible = i == main_menu_selection

func difficulty_menu() -> void:
	if Input.is_action_pressed("player_bomb"):
		current_menu = MENUS.MAIN
		$MenuAnimator.play_backwards("main2difficulty")
		SFX.play("menu_cancel")
		ui_lock = true
		return
	
	var last_difficulty : System.DIFFICULTY = difficulty_selection
	
	if Input.is_action_pressed("player_left") and difficulty_selection != System.DIFFICULTY.EASY:
		@warning_ignore("int_as_enum_without_cast")
		difficulty_selection -= 1
	if Input.is_action_pressed("player_right") and difficulty_selection != System.DIFFICULTY.OVERDRIVE:
		@warning_ignore("int_as_enum_without_cast")
		difficulty_selection += 1
		
	if difficulty_selection > last_difficulty:
		var anim_name : String
		match last_difficulty:
			System.DIFFICULTY.EASY:
				anim_name = "e2n"
			System.DIFFICULTY.NORMAL:
				anim_name = "n2h"
			System.DIFFICULTY.HARD:
				anim_name = "h2l"
			System.DIFFICULTY.LUNATIC:
				anim_name = "l2o"
		$Difficulty/DifficultyChangeAnimator.play(anim_name)
		SFX.play("menu_select")
		ui_lock = true

	elif difficulty_selection < last_difficulty:
		var anim_name : String
		match last_difficulty:
			System.DIFFICULTY.NORMAL:
				anim_name = "e2n"
			System.DIFFICULTY.HARD:
				anim_name = "n2h"
			System.DIFFICULTY.LUNATIC:
				anim_name = "h2l"
			System.DIFFICULTY.OVERDRIVE:
				anim_name = "l2o"
		$Difficulty/DifficultyChangeAnimator.play_backwards(anim_name)
		SFX.play("menu_select")
		ui_lock = true


	if Input.is_action_pressed("player_shoot"):
		current_menu = MENUS.ABILITY
		$MenuAnimator.play("difficulty2ability")
		SFX.play("menu_ok")
		ui_lock = true
	

func ability_menu() -> void:
	if Input.is_action_pressed("player_bomb"):
		current_menu = MENUS.DIFFICULTY
		$MenuAnimator.play_backwards("difficulty2ability")
		SFX.play("menu_cancel")
		ui_lock = true
		return
	var ability_change := 0
	if Input.is_action_just_pressed("player_left"):
		ability_change = -1
		@warning_ignore("int_as_enum_without_cast")
		ability_selection += ABILITY_SELECTIONS.size() - 1
	if Input.is_action_just_pressed("player_right"):
		ability_change = 1
		@warning_ignore("int_as_enum_without_cast")
		ability_selection += 1
	@warning_ignore("int_as_enum_without_cast")
	ability_selection %= ABILITY_SELECTIONS.size()
	
	var swap_animator := $Ability/AbilitySwapAnimator
	
	if Input.is_action_just_pressed("player_shoot"):
		SFX.play("menu_ok")
		$MenuAnimator.play("ability2start")
		ui_lock = true
	
	if ability_change != 0:
		power_bar_timer = 1.0
		range_bar_timer = 1.0
		firerate_bar_timer = 1.0
		difficulty_bar_timer = 1.0
		
		power_bar_start = power_bar.value * 10 - 1
		range_bar_start = range_bar.value * 10 - 1
		firerate_bar_start = firerate_bar.value * 10 - 1
		difficulty_bar_start = difficulty_bar.value * 10 - 1
		
		power_bar_end = stats[ability_selection][STAT_ORDER.POWER]
		range_bar_end = stats[ability_selection][STAT_ORDER.RANGE]
		firerate_bar_end = stats[ability_selection][STAT_ORDER.FIRERATE]
		difficulty_bar_end = stats[ability_selection][STAT_ORDER.DIFFICULTY]
		
		description_label.text = ABILITY_DESCRIPTIONS[ability_selection]
		
		
		if ability_change > 0:
			SFX.play("menu_select")
			match ability_selection:
				ABILITY_SELECTIONS.NORMAL:
					swap_animator.play("sword2normal")
				ABILITY_SELECTIONS.CUTTER:
					swap_animator.play("normal2cutter")
				ABILITY_SELECTIONS.FREEZE:
					swap_animator.play("cutter2freeze")
				ABILITY_SELECTIONS.PARASOL:
					swap_animator.play("freeze2parasol")
				ABILITY_SELECTIONS.SPARK:
					swap_animator.play("parasol2spark")
				ABILITY_SELECTIONS.BOMB:
					swap_animator.play("spark2bomb")
				ABILITY_SELECTIONS.SNIPER:
					swap_animator.play("bomb2sniper")
				ABILITY_SELECTIONS.SWORD:
					swap_animator.play("sniper2sword")
		elif ability_change < 0:
			SFX.play("menu_select")
			match ability_selection:
				ABILITY_SELECTIONS.NORMAL:
					swap_animator.play_backwards("normal2cutter")
				ABILITY_SELECTIONS.CUTTER:
					swap_animator.play_backwards("cutter2freeze")
				ABILITY_SELECTIONS.FREEZE:
					swap_animator.play_backwards("freeze2parasol")
				ABILITY_SELECTIONS.PARASOL:
					swap_animator.play_backwards("parasol2spark")
				ABILITY_SELECTIONS.SPARK:
					swap_animator.play_backwards("spark2bomb")
				ABILITY_SELECTIONS.BOMB:
					swap_animator.play_backwards("bomb2sniper")
				ABILITY_SELECTIONS.SNIPER:
					swap_animator.play_backwards("sniper2sword")
				ABILITY_SELECTIONS.SWORD:
					swap_animator.play_backwards("sword2normal")

func _process(delta: float) -> void:
	for star in stars:
		star.rotation += TAU * delta * 0.3
	
	if power_bar_timer > 0.0:
		power_bar_timer -= delta * bar_drain_rate
		if power_bar_timer < 0.0:
			power_bar_timer = 0.0
		power_bar.value = (lerp(power_bar_start, power_bar_end, (1 - power_bar_timer) * (1 - power_bar_timer)) + 1) / 10
	if range_bar_timer > 0.0:
		range_bar_timer -= delta * bar_drain_rate
		if range_bar_timer < 0.0:
			range_bar_timer = 0.0
		range_bar.value = (lerp(range_bar_start, range_bar_end, (1 - range_bar_timer) * (1 - range_bar_timer)) + 1) / 10
	if firerate_bar_timer > 0.0:
		firerate_bar_timer -= delta * bar_drain_rate
		if firerate_bar_timer < 0.0:
			firerate_bar_timer = 0.0
		firerate_bar.value = (lerp(firerate_bar_start, firerate_bar_end, (1 - firerate_bar_timer) * (1 - firerate_bar_timer)) + 1) / 10
	if difficulty_bar_timer > 0.0:
		difficulty_bar_timer -= delta * bar_drain_rate
		if difficulty_bar_timer < 0.0:
			difficulty_bar_timer = 0.0
		difficulty_bar.value = (lerp(difficulty_bar_start, difficulty_bar_end, (1 - difficulty_bar_timer) * (1 - difficulty_bar_timer)) + 1) / 10
	
	
	
	if not ui_lock:
		match current_menu:
			MENUS.MAIN:
				main_menu()
			MENUS.DIFFICULTY:
				difficulty_menu()
			MENUS.OPTIONS:
				if $Options.options_menu():
					$Options.options_menu_selection = $Options.OPTIONS_MENU_SELECTIONS.MASTER
					$MenuAnimator.play_backwards("main2options")
					current_menu = MENUS.MAIN
			MENUS.ABILITY:
				ability_menu()
				

func _on_menu_animator_animation_finished(_anim_name: StringName) -> void:
	ui_lock = false


func _on_difficulty_change_animator_animation_finished(_anim_name: StringName) -> void:
	ui_lock = false

func change_to_game() -> void:
	System.player_starting_ability = ability_selection as Player.PLAYER_ABILITY
	System.difficulty = difficulty_selection as System.DIFFICULTY
	System.in_dialogue = true
	System.clear_enemies = false
	get_tree().change_scene_to_packed(System.game_scene)
