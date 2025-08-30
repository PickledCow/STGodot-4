extends MarginContainer

signal bg_scale_changed(scale: int)

@export var star_paths : Array[NodePath] = []
var stars : Array[TextureRect] = []

@export var meter_paths : Array[NodePath] = []
var meters : Array[ProgressBar] = []

enum OPTIONS_MENU_SELECTIONS { MASTER, MUSIC, SFX, WINDOWED, BORDERLESS, FULLSCREEN, SCALE, EXIT }
enum WINDOW_MODE { WINDOWED, BORDERLESS, FULLSCREEN }

const PROG_BAR_MIN := 0.1
const PROG_TEXT_MIN := -28.0
const PROG_TEXT_MAX := 620.0

const BG_SCALE_MAX := 8

var windowed_mode : WINDOW_MODE

var options_menu_selection := 0

func _ready() -> void:
	for path in star_paths:
		stars.append(get_node(path))
		
	for path in meter_paths:
		meters.append(get_node(path))
		
	var real_window_mode = DisplayServer.window_get_mode()
	if real_window_mode == DisplayServer.WINDOW_MODE_FULLSCREEN:
		windowed_mode = WINDOW_MODE.BORDERLESS
	elif real_window_mode == DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN:
		windowed_mode = WINDOW_MODE.FULLSCREEN
	else:
		windowed_mode = WINDOW_MODE.WINDOWED
	
	set_meter(0, System.master_volume)
	set_meter(1, System.music_volume)
	set_meter(2, System.sfx_volume)
	set_scale_meter(System.bg_scale)
	
	update_window_labels()

func set_meter(index: int, value: float) -> void:
	var progress_bar := meters[index]
	var percent_label : Label = progress_bar.get_node("Percent")
	
	progress_bar.value = PROG_BAR_MIN + (1.0 - PROG_BAR_MIN) * value
	progress_bar.material.set_shader_parameter("progress", progress_bar.value)
	percent_label.position.x = PROG_TEXT_MIN + (PROG_TEXT_MAX - PROG_TEXT_MIN) * value
	percent_label.text = str(int(floor(value * 100.0))) + "%"
	
func set_scale_meter(value: int) -> void:
	var progress_bar := meters[3]
	var percent_label : Label = progress_bar.get_node("Percent")
	
	var progress : float = (BG_SCALE_MAX + 1.0 - value) / BG_SCALE_MAX
	
	progress_bar.value = PROG_BAR_MIN + (1.0 - PROG_BAR_MIN) * progress
	progress_bar.material.set_shader_parameter("progress", progress_bar.value)
	percent_label.position.x = PROG_TEXT_MIN + (PROG_TEXT_MAX - PROG_TEXT_MIN) * progress
	percent_label.text = "1 / " + str(value)

func update_window_labels() -> void:
	for i in WINDOW_MODE.size():
		var colour : Color = Color(1,1,1,1) if i == windowed_mode else Color(0.6, 0.6, 0.6, 1.0)
		$VBoxContainer/Windows.get_child(i).get_node("Text").modulate = colour
	
func options_menu() -> bool:
	if Input.is_action_pressed("player_bomb"):
		#$MenuAnimator.play_backwards("main2options")
		SFX.play("menu_cancel")
		return true
	
	
	if Input.is_action_just_pressed("player_up"):
		if options_menu_selection in [3, 4, 5]:
			options_menu_selection = 2
		elif options_menu_selection == 6:
			options_menu_selection = 3 + windowed_mode
		else:
			options_menu_selection += OPTIONS_MENU_SELECTIONS.size() - 1
		SFX.play("menu_select")
	if Input.is_action_just_pressed("player_down"):
		if options_menu_selection in [3, 4, 5]:
			options_menu_selection = 6
		elif options_menu_selection == 2:
			options_menu_selection = 3 + windowed_mode
		else:
			options_menu_selection += 1
		SFX.play("menu_select")
		
	if Input.is_action_just_pressed("player_left"):
		match options_menu_selection:
			OPTIONS_MENU_SELECTIONS.MASTER:
				var volume : float = clamp(System.master_volume - 0.1, 0.0, 1.0)
				System.set_master_volume(volume)
				set_meter(0, volume)
				SFX.play("menu_select")
			OPTIONS_MENU_SELECTIONS.MUSIC:
				var volume : float = clamp(System.music_volume - 0.1, 0.0, 1.0)
				System.set_music_volume(volume)
				set_meter(1, volume)
				SFX.play("menu_select")
			OPTIONS_MENU_SELECTIONS.SFX:
				var volume : float = clamp(System.sfx_volume - 0.1, 0.0, 1.0)
				System.set_sfx_volume(volume)
				set_meter(2, volume)
				SFX.play("menu_select")
				
			OPTIONS_MENU_SELECTIONS.BORDERLESS, OPTIONS_MENU_SELECTIONS.FULLSCREEN:
				options_menu_selection -= 1
				SFX.play("menu_select")
			
			OPTIONS_MENU_SELECTIONS.SCALE:
				var bg_scale : int = clamp(System.bg_scale + 1, 1, BG_SCALE_MAX)
				System.bg_scale = bg_scale
				set_scale_meter(bg_scale)
				bg_scale_changed.emit(bg_scale)
				SFX.play("menu_select")
				
	if Input.is_action_just_pressed("player_right"):
		match options_menu_selection:
			OPTIONS_MENU_SELECTIONS.MASTER:
				var volume : float = clamp(System.master_volume + 0.1, 0.0, 1.0)
				System.set_master_volume(volume)
				set_meter(0, volume)
				SFX.play("menu_select")
			OPTIONS_MENU_SELECTIONS.MUSIC:
				var volume : float = clamp(System.music_volume + 0.1, 0.0, 1.0)
				System.set_music_volume(volume)
				set_meter(1, volume)
				SFX.play("menu_select")
			OPTIONS_MENU_SELECTIONS.SFX:
				var volume : float = clamp(System.sfx_volume + 0.1, 0.0, 1.0)
				System.set_sfx_volume(volume)
				set_meter(2, volume)
				SFX.play("menu_select")
				
			OPTIONS_MENU_SELECTIONS.WINDOWED, OPTIONS_MENU_SELECTIONS.BORDERLESS:
				options_menu_selection += 1
				SFX.play("menu_select")
	
			OPTIONS_MENU_SELECTIONS.SCALE:
				var bg_scale : int = clamp(System.bg_scale - 1, 1, BG_SCALE_MAX)
				System.bg_scale = bg_scale
				set_scale_meter(bg_scale)
				bg_scale_changed.emit(bg_scale)
				SFX.play("menu_select")
				
	options_menu_selection %= OPTIONS_MENU_SELECTIONS.size()
	
	
	if Input.is_action_just_pressed("player_shoot"):
		match options_menu_selection:
			OPTIONS_MENU_SELECTIONS.WINDOWED:
				SFX.play("menu_ok")
				windowed_mode = WINDOW_MODE.WINDOWED
				if not DisplayServer.window_get_mode() in [DisplayServer.WINDOW_MODE_MAXIMIZED, DisplayServer.WINDOW_MODE_MINIMIZED]:
					DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_WINDOWED)
				update_window_labels()
			OPTIONS_MENU_SELECTIONS.BORDERLESS:
				SFX.play("menu_ok")
				windowed_mode = WINDOW_MODE.BORDERLESS
				DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_FULLSCREEN)
				update_window_labels()
			OPTIONS_MENU_SELECTIONS.FULLSCREEN:
				SFX.play("menu_ok")
				windowed_mode = WINDOW_MODE.FULLSCREEN
				DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_EXCLUSIVE_FULLSCREEN)
				update_window_labels()
			OPTIONS_MENU_SELECTIONS.EXIT:
				#$MenuAnimator.play_backwards("main2options")
				SFX.play("menu_cancel")
				return true
	
	return false	
	
func _process(delta: float) -> void:
	for star in stars:
		star.rotation += TAU * delta * 0.3
	for i in OPTIONS_MENU_SELECTIONS.size():
		var selection_icon : TextureRect = stars[i]
		selection_icon.visible = i == options_menu_selection
