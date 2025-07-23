extends Node
class_name GameSystem
## The default system holding onto most global data that is not part of the 
## STGodot environment.
##
## arshtaoit
## @experimental

enum ITEM_TYPE { LARGE_POWER, LIFE_FRAGMENT, LIFE, BOMB_FRAGMENT, BOMB, FULL_POWER, POWER, POINT, CLEAR, SIZE }

@onready var bullet_constructor : BulletConstructor = $BulletConstructor

##

var player : Player
var warp_rect : WarpRect


@export var playfield_size := Vector2(1000, 1000)
@export var enemy_active_rect := Rect2(Vector2(-128, -128), Vector2(1256, 1256))

## Current graze count.
var graze := 0
## Current value of the point item.
var piv := 1000
## Current game score
var score := 0

var time_scale := 1.0

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

#endregion
