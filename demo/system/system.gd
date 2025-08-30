extends Node
class_name GameSystem
## The default system holding onto most global data that is not part of the 
## STGodot environment.
##
## arshtaoit
## @experimental

#enum ITEM_TYPE { LARGE_POWER, LIFE_FRAGMENT, LIFE, BOMB_FRAGMENT, BOMB, FULL_POWER, POWER, POINT, CLEAR, SIZE }
enum ITEM_TYPE { STAR, DUBIOUS = 4, ICY_POLE, EGGPLANT, SUSHI, TAKOYAKI, RICEBALL, TEA, RANDOM }
enum DAMAGE_TYPE { STAR, STAR_STRONG, SUCK, NORMAL, CRIT, CANOPY, SHOCK, SHOCK_SHIELD, SHARP, CHILL }
enum DIFFICULTY { EASY, NORMAL, HARD, LUNATIC, OVERDRIVE }
enum ATTACK_TYPE { NON, SPELL, TIMEOUT, SUPER, ULTRA }

var player_starting_ability : Player.PLAYER_ABILITY

var master_volume := 1.0
var music_volume := 1.0
var sfx_volume := 0.8

@onready var bullet_constructor : BulletConstructor = $BulletConstructor

##

var player : Player
var current_boss : Boss
var warp_rect : WarpRect
var root : Node2D
var bg : BGHandler
var ui : UIManager

var boss_manager : BossManager

@export var playfield_size := Vector2(1000, 1000)
@export var enemy_active_rect := Rect2(Vector2(-256, -256), Vector2(1512, 1512))

var game_scene = preload("res://Test.tscn")
var main_menu_scene := preload("res://scenes/mainmenu.tscn")
var credits_scene := preload("res://scenes/credits.tscn")

var just_booted := true

## Current graze count.
var graze := 0
## Current value of the point item.
var piv := 1000
## Current game score
var score := 0
## Current game difficulty
var difficulty := DIFFICULTY.LUNATIC

var time_scale : float = 1.0

var bg_scale := 1.0
var in_dialogue := true
var clear_enemies := false

var fade_quit := false

func _ready() -> void:
	set_master_volume(master_volume)
	set_music_volume(music_volume)
	set_sfx_volume(sfx_volume)

#region Registration Functions

func register_player(node: Player) -> void:
	player = node

func register_warp_rect(node: WarpRect) -> void:
	warp_rect = node

#endregion

#region Update  Functions

func increase_graze(amount: int) -> void:
	graze += amount

func collect_piv_items(count: int) -> void:
	piv += count

func collect_point_items(count: int) -> void:
	score += count * piv

#endregion


#region Query Functions

func get_bullet_data(type: int, color: int) -> PackedFloat64Array:
	return bullet_constructor.get_bullet_data(type, color)
	
func get_item_data(type: int) -> PackedFloat64Array:
	return bullet_constructor.get_item_data(type)
	
#endregion

#region Command Functions

func warp_player(pos: Vector2) -> void:
	if warp_rect:
		warp_rect.warp_player(pos)
	
func warp_boss(pos: Vector2) -> void:
	if warp_rect:
		warp_rect.warp_boss(pos)

func shake_screen(intensity: float, duration: float):
	if root:
		root.shake_screen(intensity, duration)

#endregion


func set_master_volume(volume: float) -> void:
	master_volume = volume
	AudioServer.set_bus_volume_linear(AudioServer.get_bus_index("Master"), volume)
	
func set_music_volume(volume: float) -> void:
	music_volume = volume
	AudioServer.set_bus_volume_linear(AudioServer.get_bus_index("Music"), volume)
	
func set_sfx_volume(volume: float) -> void:
	sfx_volume = volume
	AudioServer.set_bus_volume_linear(AudioServer.get_bus_index("SFX"), volume)



#region Garbage



#endregion
