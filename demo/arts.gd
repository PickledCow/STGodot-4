extends Node2D

@export var bullet_kit : BulletKit

var data: PackedFloat64Array

var t := 0

var pos := Vector2()

# Called when the node enters the scene tree for the first time.
func _ready():
	data = PackedFloat64Array()
	data.resize(15)
	data[0] = 64 * 8			# source x (integer) # (16+8*(c/4))
	data[1] = 64 * 2			# source y (integer) # (24+2*(c%4))
	data[2] = 64				# source width (integer)
	data[3] = 64				# source height (integer)
	data[4] = 32.0				# bullet size [0, inf)
	data[5] = 0.5 	# hitbox ratio [0, 1]
	data[6] = 0					# Sprite offset y (integer)
	data[7] = 1					# anim frame, 1 for no animation (integer)
	data[8] = 0					# spin
	data[9] = 3 # layer
	data[10] = 1.0	# rgb
	data[11] = 1.0
	data[12] = 1.0
	data[13] = 0				# damage type
	data[14] = 0				# damage amount


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass

func _physics_process(d_elta):
	t += 1
	if t:
		for i in 130:
			Bullets.create_shot_a1(bullet_kit, Vector2(1280, 720) * 0.5, 4.0, randf()*TAU, data, true)
	#print(Bullets.get_total_active_bullets())
	if t % 10 == 0:
		print("Bullets: ", Bullets.get_total_active_bullets(), "; FPS: ", Engine.get_frames_per_second())
		
	var new_pos := get_local_mouse_position()
	if new_pos:
		pos = new_pos
	var r = 24
	var r2 = 64
	
	Bullets.collide_and_graze(bullet_kit, pos, r, r2)
