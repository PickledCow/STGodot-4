extends Control
class_name PauseMenu

@export_node_path("SubViewportContainer") var bg_viewport_path
@onready var bg_viewport : SubViewportContainer = get_node(bg_viewport_path)

var paused_from_game_over := false

enum MENUS { MAIN, RESTART, OPTIONS, QUIT }
enum MAIN_MENU_SELECTIONS { RESUME, RESTART, OPTIONS, QUIT }

var current_menu : MENUS = MENUS.MAIN

var main_menu_selection : MAIN_MENU_SELECTIONS = MAIN_MENU_SELECTIONS.RESUME

var pause_min_timer := 0.0

var ui_lock := false

@export var star_paths : Array[NodePath] = []
var stars : Array[TextureRect] = []


# SO lazy this is also just any persistent shit
func _ready():
	for path in star_paths:
		stars.append(get_node(path))
		
	get_viewport().focus_exited.connect(_on_window_focus_out)
	#get_tree().paused = true

func _on_window_focus_out():
	if not get_tree().paused:
		pause()


func main_menu() -> void:
	if Input.is_action_just_pressed("player_up"):
		@warning_ignore("int_as_enum_without_cast")
		main_menu_selection += MAIN_MENU_SELECTIONS.size() - 1
		SFX.play("menu_select")
	if Input.is_action_just_pressed("player_down"):
		@warning_ignore("int_as_enum_without_cast")
		main_menu_selection += 1
		SFX.play("menu_select")
	
	@warning_ignore("int_as_enum_without_cast")
	main_menu_selection %= MAIN_MENU_SELECTIONS.size()
	
	if Input.is_action_just_pressed("player_bomb"):
		main_menu_selection = MAIN_MENU_SELECTIONS.QUIT
		unpause()

	if Input.is_action_just_pressed("player_shoot"):
		match main_menu_selection:
			MAIN_MENU_SELECTIONS.RESUME:
				unpause()
				#ui_lock = true
			MAIN_MENU_SELECTIONS.RESTART:
				unpause()
				SFX.play("menu_ok")
				Bullets.unmount()
				System.warp_rect.reset_warps()
				SFX.stop_all()
				System.in_dialogue = true
				System.clear_enemies = false
				get_tree().reload_current_scene()
			MAIN_MENU_SELECTIONS.OPTIONS:
				current_menu = MENUS.OPTIONS
				$Panel/Options.show()
				$Panel/VBoxContainer.hide()
				SFX.play("menu_ok")
				#ui_lock = true
			MAIN_MENU_SELECTIONS.QUIT:
				SFX.play("menu_ok")
				Bullets.unmount()
				System.warp_rect.reset_warps()
				SFX.stop_all()
				get_tree().change_scene_to_packed(System.main_menu_scene)
				#get_tree().quit()
	
	for i in MAIN_MENU_SELECTIONS.size():
		var selection_icon : TextureRect = $Panel/VBoxContainer/Bottom/OptionsContainer.get_child(i).get_node("SelectionContainer/Selection")
		selection_icon.visible = i == main_menu_selection
func pause():
	SFX.stop_all()
	get_tree().paused = true
	if not paused_from_game_over:
		$Pause.play()
		pause_min_timer = 0.2
	else:
		$GameOver.play()
		pause_min_timer = 1.0
	show()
	

func unpause():
	if paused_from_game_over:
		paused_from_game_over = false
		System.player.current_lives = 8
		System.ui.set_health(8)
		System.ui.show_halo()
		System.player.show()
		System.player.get_node("halo").show()
		System.player.position = Vector2(500, 900)
		$GameOver.stop()
	$Panel/VBoxContainer/Top/VBoxContainer/Paused.show()
	$Panel/VBoxContainer/Top/VBoxContainer/GameOver.hide()
	$Panel/VBoxContainer/Bottom/OptionsContainer/Resume/ResumeText.show()
	$Panel/VBoxContainer/Bottom/OptionsContainer/Resume/ContinueText.hide()
	SFX.play("menu_cancel")
	hide()
	get_tree().paused = false
	main_menu_selection = MAIN_MENU_SELECTIONS.RESUME
	current_menu = MENUS.MAIN
	$Panel/Options.hide()
	$Panel/VBoxContainer.show()
	


func _process(delta: float) -> void:
	if pause_min_timer > 0.0:
		pause_min_timer -= delta
		
	for star in stars:
		star.rotation += TAU * delta * 0.3
		
	if Input.is_action_just_pressed("pause") and not (paused_from_game_over and pause_min_timer > 0.0):
		if get_tree().paused and not paused_from_game_over:
			unpause()
		else:
			pause()
	
	if get_tree().paused:
		if not ui_lock and pause_min_timer <= 0.0:
			match current_menu:
				MENUS.MAIN:
					main_menu()
				MENUS.OPTIONS:
					if $Panel/Options.options_menu():
						$Panel/Options.hide()
						$Panel/Options.options_menu_selection = $Panel/Options.OPTIONS_MENU_SELECTIONS.MASTER
						$Panel/VBoxContainer.show()
						current_menu = MENUS.MAIN
						
	
	if is_inside_tree():
		Input.mouse_mode = Input.MOUSE_MODE_HIDDEN if not get_tree().paused and Rect2(Vector2(460, 40), Vector2(1000, 1000)).has_point(get_global_mouse_position()) else Input.MOUSE_MODE_VISIBLE


func _on_options_bg_scale_changed(stretch_shrink: int) -> void:
	bg_viewport.stretch_shrink = stretch_shrink

func game_over():
	paused_from_game_over = true
	$Panel/VBoxContainer/Top/VBoxContainer/Paused.hide()
	$Panel/VBoxContainer/Top/VBoxContainer/GameOver.show()
	$Panel/VBoxContainer/Bottom/OptionsContainer/Resume/ResumeText.hide()
	$Panel/VBoxContainer/Bottom/OptionsContainer/Resume/ContinueText.show()
	pause()
