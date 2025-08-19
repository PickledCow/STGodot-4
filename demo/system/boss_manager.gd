extends Node2D
class_name BossManager

@export var health_bar_path : NodePath
@onready var health_bar : ProgressBar = get_node(health_bar_path)
@export var health_percent_path : NodePath
@onready var health_percent : Label = get_node(health_percent_path)

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

var prev_time : float = 0.0

var music_fade : float = 1.0
var fade_out : bool = false

# -1 
var debug_skip_boss := 3

var debug_music_start_time : float = 0.0

enum GAME_STATE { DIALOGUE, FIGHT }

var game_state : GAME_STATE = GAME_STATE.FIGHT

func _ready() -> void:
	System.boss_manager = self
	
	var start_points : Array[float] = [0.0, CIRNO_START, KOGASA_START, MARISA_START, SANAE_START, MEGUMU_START, YOUMU_START]
	if debug_skip_boss > 0:
		get_tree().paused = true
		debug_music_start_time = start_points[debug_skip_boss]
		#$Music.play(start_points[debug_skip_boss])
		current_boss = debug_skip_boss -1
		next_boss = debug_skip_boss

func increment_boss() -> void:
	next_boss += 1

func _process(delta: float) -> void:
	if debug_music_start_time > 0.0 and not $Music.playing:
		$Music.play(debug_music_start_time)
	if current_boss < next_boss and game_state == GAME_STATE.FIGHT:
		if next_boss < bosses.size():
			current_boss = next_boss
			if current_boss == 0:
				$Music.play()
			var boss := bosses[current_boss].instantiate()
			boss.position = Vector2(500, 300)
			add_child(boss)
		elif not fade_out:
			fade_out = true
	
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
	
	# fade out music
	if fade_out:
		music_fade -= delta * 0.25
		$Music.volume_linear = max(0.0, music_fade)
	
	
	# Update UI
	if System.current_boss:
		health_bar.value = 0.075 + System.current_boss.health / System.current_boss.max_health * (1.0 - 0.075)
		# 690.0 max-41.0 min
		health_percent.text = str(int(System.current_boss.health / System.current_boss.max_health * 100.0)) + "%"
		health_percent.position.x = -41.0 + (690.0 + 41.0) * System.current_boss.health / System.current_boss.max_health
