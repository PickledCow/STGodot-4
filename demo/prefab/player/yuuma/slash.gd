extends Node2D

var lifespan := 8.0
var lifetime := 0.0
var damage := 8.0

func _ready() -> void:
	
	var slash = PackedFloat64Array()
	slash.resize(15)
	slash[0] = 0 # source x (integer)
	slash[1] = 0 # source y (integer)
	slash[2] = 0 				# source width (integer)
	slash[3] = 0				# source height (integer)
	slash[4] = 128				# bullet size [0, inf)
	slash[5] = 1 				# hitbox ratio [0, 1]
	slash[6] = 0					# Sprite offset y (integer)
	slash[7] = 1					# anim frame, 1 for no animation (integer)
	slash[8] = 0					# spin
	slash[9] = 1	# layer
	slash[10] = 1	# rgb
	slash[11] = 1
	slash[12] = 1
	slash[13] = System.DAMAGE_TYPE.SHARP				# damage type
	slash[14] = damage				# damage amount
	
	var b = Bullets.create_shot_a1(position, 0, 0, slash, false)
	Bullets.set_lifespan(b, lifespan)
	
func _process(_delta: float) -> void:
	
	$Sprite2D.frame = int(lifetime / lifespan * 8.0)
	
	lifetime += System.time_scale
	if lifetime >= lifespan:
		queue_free()
