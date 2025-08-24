extends Node2D
class_name BossManager

## The turbo jank pseudo root

@export var health_bar_path : NodePath
@onready var health_bar : ProgressBar = get_node(health_bar_path)
@export var health_percent_path : NodePath
@onready var health_percent : Label = get_node(health_percent_path)

@export var dialogue_path : NodePath
@onready var dialogue_manager : Node = get_node(dialogue_path)

var current_boss := -1
var next_boss := 0

var bosses : Array[PackedScene] = [
	preload("res://prefab/boss/futo.tscn"),
	preload("res://prefab/boss/cirno.tscn"),
	preload("res://prefab/boss/kogasa.tscn"),
	preload("res://prefab/boss/marisa.tscn"),
	preload("res://prefab/boss/sanae.tscn"), 
	preload("res://prefab/boss/megumu.tscn"),
	preload("res://prefab/boss/youmu.tscn"),
]

var mizuchi := preload("res://prefab/boss/mizuchi.tscn")

const BEAT : float = 60.0 / 170.0
const BAR : float = BEAT * 4
const FUTO_INTRO : float = BEAT * 3 * 4 * 4
const FUTO_BRIDGE : float = BEAT * 7 * 4
const FUTO_CHORUS_SECTION : float = BAR * 4
const CIRNO_START : float = FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION * 4
const CIRNO_INTRO : float = BAR * 4 * 4
const CIRNO_CHORUS_SECTION : float = BAR * 4
const KOGASA_START : float = CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION * 4
const KOGASA_INTRO : float = BAR * 4 * 4
const KOGASA_CHORUS_SECTION : float = BAR * 4
const MARISA_START : float = KOGASA_START + KOGASA_INTRO + KOGASA_CHORUS_SECTION * 4
const MARISA_INTRO : float = BAR * 4 * 4
const MARISA_CHORUS_SECTION : float = BAR * 6
const SANAE_START : float = MARISA_START + MARISA_INTRO + MARISA_CHORUS_SECTION * 2 + BAR * 2
const SANAE_INTRO : float = BAR * 4 * 2
const SANAE_BRIDGE : float = BAR * 4 * 2
const SANAE_CHORUS_SECTION : float = BAR * 8
const MEGUMU_START : float = SANAE_START + SANAE_INTRO + SANAE_BRIDGE + SANAE_CHORUS_SECTION * 2
const MEGUMU_INTRO_SECTION : float = BAR * 8
const MEGUMU_CHORUS_SECTION : float = BAR * 8
const YOUMU_START : float = MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION * 2
const YOUMU_BEAT : float = 60.0 / 160.0
const YOUMU_BAR : float = YOUMU_BEAT * 4
const YOUMU_INTRO : float = YOUMU_BAR * 8
const YOUMU_BRIDGE : float = YOUMU_BAR * 4
const YOUMU_CHORUS_SECTION : float = YOUMU_BAR * 8
const YOUMU_CHORUS_SECTION_2 : float = YOUMU_BAR * 8
const YOUMU_END : float = YOUMU_START + YOUMU_INTRO + YOUMU_BRIDGE + YOUMU_CHORUS_SECTION * 2 + YOUMU_CHORUS_SECTION_2 * 2

# Start and end of regular loops
var loop_points = [
	[ # Futo
		FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION - BAR, 
		FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION * 3 - BAR
	], [ # Cirno
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION, 
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION * 3
	], [ # Kogasa
		KOGASA_START + KOGASA_INTRO + BAR * 3,
		KOGASA_START + KOGASA_INTRO + KOGASA_CHORUS_SECTION * 2 + BAR * 3
	], [ # Marisa
		MARISA_START + MARISA_INTRO + BAR * 4, 
		MARISA_START + MARISA_INTRO + MARISA_CHORUS_SECTION + BAR * 4
	], [ # Sanae
		SANAE_START + SANAE_INTRO + SANAE_BRIDGE + BAR * 5, 
		SANAE_START + SANAE_INTRO + SANAE_BRIDGE + SANAE_CHORUS_SECTION + BAR * 5
	], [ # Megumu
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + BAR * 2,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION + BAR * 2,
	], [ # Youmu
		YOUMU_START + YOUMU_INTRO + YOUMU_BRIDGE + YOUMU_CHORUS_SECTION * 2 + YOUMU_BAR * 4,
		YOUMU_START + YOUMU_INTRO + YOUMU_BRIDGE + YOUMU_CHORUS_SECTION * 2 + YOUMU_CHORUS_SECTION_2 + YOUMU_BAR * 4
	], [ 0.0, 10000000.0]
]

# Points where the song can skip to the "end" 
var skip_points = [
	[ # Futo
		FUTO_INTRO + FUTO_BRIDGE / 2, 
		FUTO_INTRO + FUTO_BRIDGE, 
		FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION, 
		FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION * 2 - BEAT
	], [ # Cirno
		CIRNO_START + BAR * 6, 
		CIRNO_START + CIRNO_INTRO, 
		CIRNO_START + CIRNO_INTRO + BEAT * 8,
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION + BEAT * 8,
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION * 2 + BEAT * 8,
	], [ # Kogasa
		KOGASA_START + KOGASA_INTRO + KOGASA_CHORUS_SECTION,
		KOGASA_START + KOGASA_INTRO + KOGASA_CHORUS_SECTION * 2 - BEAT,
	], [ # Marisa
		MARISA_START + BAR * 2,
		MARISA_START + BAR * (8 + 2),
		MARISA_START + MARISA_INTRO + MARISA_CHORUS_SECTION,
	], [ # Sanae
		SANAE_START + SANAE_INTRO + BAR,
		SANAE_START + SANAE_INTRO + SANAE_BRIDGE + BAR * 7
	], [ # Megumu
		MEGUMU_START + BAR * 7,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + BAR * 4,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION + BAR * 3 - BEAT * 2,
	], [ # Youmu
	]	
]

var skip_destinations = [
	[ # Futo
		CIRNO_START, 
		CIRNO_START, 
		FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION * 3,
		FUTO_INTRO + FUTO_BRIDGE + FUTO_CHORUS_SECTION * 3 - BEAT
	], [ # Cirno
		CIRNO_START + BAR * 14, 
		KOGASA_START, 
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION * 3 + BEAT * 8,
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION * 3 + BEAT * 8,
		CIRNO_START + CIRNO_INTRO + CIRNO_CHORUS_SECTION * 3 + BEAT * 8,
	], [ # Kogasa
		KOGASA_START + KOGASA_INTRO + KOGASA_CHORUS_SECTION * 3,
		KOGASA_START + KOGASA_INTRO + KOGASA_CHORUS_SECTION * 3 - BEAT,
	], [ # Marisa
		MARISA_START + BAR * 6,
		MARISA_START + BAR * (8 + 6),
		MARISA_START + MARISA_INTRO + MARISA_CHORUS_SECTION * 2,
	], [ # Sanae
		SANAE_START + SANAE_INTRO + BAR * 5,
		SANAE_START + SANAE_INTRO + SANAE_BRIDGE + SANAE_CHORUS_SECTION + BAR * 7
	], [ # Megumu 
		MEGUMU_START + MEGUMU_INTRO_SECTION + BAR * 7,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION * 2,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION + BAR * 4,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION * 2,
		MEGUMU_START + MEGUMU_INTRO_SECTION * 2 + MEGUMU_CHORUS_SECTION + BAR * 7 - BEAT * 2,
	], [ # Youmu
	]
]

var panic_skips : Array = [
	0.0,
	0.0,
	CIRNO_START,
	KOGASA_START,
	MARISA_START,
	SANAE_START,
	MEGUMU_START,
	YOUMU_START
]

var prev_time : float = 0.0

var music_fade : float = 1.0
var fade_out : bool = false

var music2_fade : float = 1.0
var fade_out2 : bool = false

var mizuch_timer := 120

var dialogue_music_warp_value : float = 1.0
var dialogue_music_is_warping : bool = false
var warp_target := 1.0

enum SECTIONS {BOSS_RUSH, PRE_DIALOUGE, DIALOGUE_1, MIZUCHI_ENTRY, DIALOGUE2, FIRST_FIGHT, DIALOGUE3, SECOND_FIGHT}
var section : SECTIONS = SECTIONS.MIZUCHI_ENTRY

var pre_dialogue_wait_timer := 180.0

var mizuch_music_started := false

# -1 
var debug_skip_boss := -1

var debug_music_start_time : float = 0.0

enum GAME_STATE { DIALOGUE, FIGHT }

var game_state : GAME_STATE = GAME_STATE.DIALOGUE

var current_boss_node : Boss

var start_playing_mizuchi_music := false

func _ready() -> void:
	System.boss_manager = self
	
	match section:
		SECTIONS.BOSS_RUSH:
			var start_points : Array[float] = [0.0, CIRNO_START, KOGASA_START, MARISA_START, SANAE_START, MEGUMU_START, YOUMU_START]
			if debug_skip_boss > 0:
				get_tree().paused = true
				debug_music_start_time = start_points[debug_skip_boss]
				#$Music.play(start_points[debug_skip_boss])
				current_boss = debug_skip_boss -1
				next_boss = debug_skip_boss
				dialogue_manager.dialogue_section = debug_skip_boss
		SECTIONS.PRE_DIALOUGE:
			game_state = GAME_STATE.FIGHT
			System.in_dialogue = false
			System.bg.next_section()
			System.bg.stop_scroll()
			pre_dialogue_wait_timer = 0.0
			next_boss = 7
		
		SECTIONS.MIZUCHI_ENTRY:
			game_state = GAME_STATE.FIGHT
			System.in_dialogue = false
			System.bg.next_section()
			System.bg.stop_scroll()
			mizuch_timer = 1
			next_boss = 7
			

func increment_boss() -> void:
	next_boss += 1
	if next_boss < bosses.size():
		System.in_dialogue = true
		dialogue_manager.left_dialogue = true
		Bullets.clear_bullets(Vector2(500, 500), 1000)
	elif next_boss == bosses.size():
		section = SECTIONS.PRE_DIALOUGE
		System.bg.next_section()
		fade_out = true
	else:
		fade_out2 = true
		section = SECTIONS.DIALOGUE3
		System.in_dialogue = true
		dialogue_manager.dialogue_section = 9
		dialogue_manager.left_dialogue = true
		dialogue_manager.dialogue_index = -1
		dialogue_manager.mash_cooldown_timer = 120.0
		dialogue_manager.janky_lock = false
		dialogue_manager.mash_cooldown = 30.0

func _process(delta: float) -> void:
	match section:
		SECTIONS.BOSS_RUSH:
			if debug_music_start_time > 0.0 and not $Music.playing:
				$Music.play(debug_music_start_time)
			if current_boss < next_boss:
				if next_boss < bosses.size():
					current_boss = next_boss
					current_boss_node = bosses[current_boss].instantiate()
					current_boss_node.position = Vector2(randf_range(200, 800), -500)
					current_boss_node.set_destination(current_boss_node.starting_position, 90)
					add_child(current_boss_node)
					if current_boss == 0:
						$Music.play()
					if current_boss == 6:
						System.bg.stop_scroll()
				elif not fade_out:
					fade_out = true
		
		SECTIONS.PRE_DIALOUGE:
			if not $DialogueMusic.playing and not $Music.playing:
				$DialogueMusic.play()
			pre_dialogue_wait_timer -= 1.0
			if pre_dialogue_wait_timer <= 0.0:
				section = SECTIONS.DIALOGUE_1
				dialogue_manager.dialogue_section = 7
				dialogue_manager.left_dialogue = true
				dialogue_manager.dialogue_expire_time = 720
				System.in_dialogue = true
				game_state = GAME_STATE.DIALOGUE
				dialogue_manager.dialogue_index = -1
				dialogue_manager.mash_cooldown_timer = 120.0
				dialogue_manager.mash_cooldown = 30.0
				$FakeEntrance.play("entry")
				var types : Array[System.ATTACK_TYPE] = []
				var names : Array[String] = []
				System.ui.update_boss_data("Yuyuko", types, names)
						
		SECTIONS.DIALOGUE_1:
			if not $DialogueMusic.playing:
				$DialogueMusic.play()
			if not System.in_dialogue:
				section = SECTIONS.MIZUCHI_ENTRY
				#var mizu : Boss = mizuchi.instantiate()
				#current_boss_node = mizu
				#mizu.position = Vector2(800, -500)
				#mizu.set_destination(mizu.starting_position, 90)
				#add_child(mizu)
				System.in_dialogue = true
				dialogue_manager.janky_lock = true
				$FakeEntrance.play("takeover")
				dialogue_music_is_warping = true
				warp_target = 0.9
		
		SECTIONS.MIZUCHI_ENTRY:
			mizuch_timer -= 1
			if mizuch_timer == 0:
				var mizu : Boss = mizuchi.instantiate()
				current_boss_node = mizu
				mizu.position = Vector2(500, 300)
				add_child(mizu)
				dialogue_manager.dialogue_section = 8
				dialogue_manager.left_dialogue = true
				dialogue_manager.dialogue_index = -1
				dialogue_manager.mash_cooldown_timer = 120.0
				dialogue_manager.janky_lock = false
				dialogue_manager.mash_cooldown = 30.0
				start_playing_mizuchi_music = true
				section = SECTIONS.DIALOGUE2
		SECTIONS.DIALOGUE2:
			if not System.in_dialogue:
				section = SECTIONS.FIRST_FIGHT
		
		SECTIONS.FIRST_FIGHT:
			pass
		SECTIONS.DIALOGUE3:
			if not $Yuuma.playing and not $Mizuchi.playing and dialogue_manager.dialogue_index >= 5:
				$Yuuma.play()
	if game_state == GAME_STATE.DIALOGUE:
		if not System.in_dialogue:
			game_state = GAME_STATE.FIGHT
			
	# =============
	# Music
	var current_time : float = $Music.get_playback_position() + AudioServer.get_time_since_last_mix()
	var loop_start : float = loop_points[current_boss][0]
	var loop_end : float = loop_points[current_boss][1]
	
	var current_skip_points : Array = [0.0] if current_boss <= 0 else skip_points[current_boss - 1]
	var current_skip_destinations : Array = [0.0] if current_boss <= 0 else skip_destinations[current_boss - 1]
	# Loop
	if current_time > loop_end:
		$Music.seek(loop_start + AudioServer.get_time_to_next_mix())
	# Skip
	var skipped := false
	for i in current_skip_destinations.size():
		var skip_point : float = current_skip_points[i]
		var skip_destination : float = current_skip_destinations[i]
		if current_time < skip_destination and current_time > prev_time:
			if prev_time < skip_point and current_time > skip_point:
				$Music.seek(skip_destination + AudioServer.get_time_to_next_mix())
				skipped = true
				prev_time = skip_destination + AudioServer.get_time_to_next_mix()
				break
	if not skipped:
		prev_time = current_time
	
	# Panic skip points
	if current_time < panic_skips[current_boss]:
		$Music.seek(panic_skips[current_boss + 1])
	
	# fade out music
	if fade_out:
		music_fade -= delta * 0.25
		$Music.volume_linear = max(0.0, music_fade)
		if music_fade <= 0.0:
			$Music.stop()
			
	if fade_out2:
		music2_fade -= delta * 0.25
		$Mizuchi.volume_linear = max(0.0, music2_fade)
		if music2_fade <= 0.0:
			$Mizuchi.stop()
	
	if dialogue_music_is_warping:
		dialogue_music_warp_value -= delta * 0.25
		$DialogueMusic.volume_linear = max(0.0, dialogue_music_warp_value)
		if dialogue_music_warp_value <= 0.0:
			$DialogueMusic.stop()
	
	if not mizuch_music_started and not $DialogueMusic.playing and start_playing_mizuchi_music:
		$Mizuchi.play()
		mizuch_music_started = true
	
