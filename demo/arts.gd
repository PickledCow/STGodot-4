extends Node2D

@export var bullet_kit : BasicBulletKit
@export var item_kit : BasicItemKit
@export var graze_kit : BasicParticleKit
@export var item_text_kit : BasicParticleKit

var data: PackedFloat64Array

var red_butterfly: PackedFloat64Array
var blue_butterfly: PackedFloat64Array

var item_data: PackedFloat64Array

var t := 0

var pos := Vector2()

# Called when the node enters the scene tree for the first time.
func _ready():
	data = PackedFloat64Array()
	data.resize(15)
	data[0] = 64 * 8			# source x (integer) # (16+8*(c/4))
	data[1] = 64 * 3			# source y (integer) # (24+2*(c%4))
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
	
	red_butterfly = PackedFloat64Array()
	red_butterfly.resize(15)
	red_butterfly[0] = 128 * 9			# source x (integer) # (16+8*(c/4))
	red_butterfly[1] = 128 * 2			# source y (integer) # (24+2*(c%4))
	red_butterfly[2] = 128				# source width (integer)
	red_butterfly[3] = 128				# source height (integer)
	red_butterfly[4] = 64.0				# bullet size [0, inf)
	red_butterfly[5] = 0.1 	# hitbox ratio [0, 1]
	red_butterfly[6] = 0					# Sprite offset y (integer)
	red_butterfly[7] = 1					# anim frame, 1 for no animation (integer)
	red_butterfly[8] = 0					# spin
	red_butterfly[9] = 3 # layer
	red_butterfly[10] = 1.0	# rgb
	red_butterfly[11] = 0.0
	red_butterfly[12] = 0.0
	red_butterfly[13] = 0				# damage type
	red_butterfly[14] = 0				# damage amount

	blue_butterfly = PackedFloat64Array()
	blue_butterfly.resize(15)
	blue_butterfly[0] = 128 * 11			# source x (integer) # (16+8*(c/4))
	blue_butterfly[1] = 128 * 2			# source y (integer) # (24+2*(c%4))
	blue_butterfly[2] = 128				# source width (integer)
	blue_butterfly[3] = 128				# source height (integer)
	blue_butterfly[4] = 64.0				# bullet size [0, inf)
	blue_butterfly[5] = 0.1 	# hitbox ratio [0, 1]
	blue_butterfly[6] = 0					# Sprite offset y (integer)
	blue_butterfly[7] = 1					# anim frame, 1 for no animation (integer)
	blue_butterfly[8] = 0					# spin
	blue_butterfly[9] = 3 # layer
	blue_butterfly[10] = 0.0	# rgb
	blue_butterfly[11] = 0.0
	blue_butterfly[12] = 1.0
	blue_butterfly[13] = 0				# damage type
	blue_butterfly[14] = 0				# damage amount



	item_data = System.get_item_data(0)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass	

func _physics_process(_delta):
	if true:
		var shoot_pos = Vector2(1280, 720*0.5) * 0.5
		if t % 120 == 120:
			for i in 120:
				var s := randf_range(2.0, 8.0)
				Bullets.create_shot_a2(bullet_kit, shoot_pos, s, randf()*TAU, -s / 120.0, 0.0, red_butterfly, true)
		
		
		if t % 20 == 0:
			SFX.play("shoot1")
			for i in 90: # 90
				#var ang = pos.angle_to_point(shoot_pos) + randf_range(-0.1, 0.1) + PI
				var ang := t * 0.01  + randf_range(-0.3, 0.3) + PI
				#var ang = randf()*TAU
				var id : PackedInt64Array = Bullets.create_shot_a1(bullet_kit, shoot_pos, randf_range(.33, 8.0), ang, data, true)
				if id[0] == -1:
					break
	else:
		if t % 2 == 3:
			Bullets.create_item(item_kit, Vector2(randf_range(0, 1280), -100), 0.0, randf()*TAU, 0.0, item_data)
			#Bullets.set_damage()
		
		for i in 1:
			Bullets.create_item(item_kit, Vector2(1280 * 0.5, 720 * 0.25), randf_range(2.0, 20.0), randf()*TAU, 60.0, item_data)
	#print(Bullets.get_total_active_bullets())
		
	
	if t % 60 == 0:
		pass
		#print(get_viewport_rect().size)
		#print("Bullets: ", Bullets.get_total_active_bullets(), "; FPS: ", Engine.get_frames_per_second())
		#print("Collisions: ", collisions[0].size(), "; Grazes: ", collisions[1].size())

	t += 1
	
	
