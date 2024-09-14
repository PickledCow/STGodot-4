extends Node2D

@export var bullet_kit : BasicBulletKit
@export var item_kit : BasicItemKit
@export var graze_kit : BasicParticleKit
@export var item_text_kit : BasicParticleKit

var data: PackedFloat64Array

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

	item_data.resize(11)
	item_data[0] = 128 * 6.5			# source x (integer) # (16+8*(c/4))
	item_data[1] = 0		# source y (integer) # (24+2*(c%4))
	item_data[2] = 64				# source width (integer)
	item_data[3] = 64				# source height (integer)
	item_data[4] = 32.0				# bullet size [0, inf)
	item_data[5] = 0.5				# hitbox ratio [0, 1]
	item_data[6] = 0					# Sprite offset y (integer)
	item_data[7] = 0					# anim frame, 1 for no animation (integer)
	item_data[8] = 0					# layer
	item_data[9] = 1					# type
	item_data[10] = 0					# value,

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass	

func _physics_process(_delta):
	
	t += 1
	if false:
		var shoot_pos = Vector2(1280, 720) * 0.5
		for i in 50: # 90
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
		
	var new_pos := get_global_mouse_position()
	if new_pos:
		pos = new_pos
	var r = 24
	var r2 = 64
	
	position = pos
	
	var collisions = Bullets.collide_and_graze(bullet_kit, pos, r, r2)
	var items = Bullets.collect_and_magnet(item_kit, pos, self, 1.0, 256)
	
	for i in collisions[1].size():
		var bullet_id : PackedInt64Array = collisions[1][i]
		var bullet_pos : Vector2 = Bullets.get_position(bullet_id)
		
		var drift : Vector2 = (pos - bullet_pos).normalized() * 2.0 + Vector2(randf_range(3.0, 6.0), 0.0).rotated(randf()*TAU)
		#var drift : Vector2 = (pos - bullet_pos).normalized() * 10.0
		#var drift : Vector2 = Vector2(randf_range(0.2, 0.5), 0.0).rotated((randf()*TAU))
		
		var color : Color = Color.WHITE
		color.a = 0.0
		
		Bullets.create_particle(graze_kit, pos, drift, randf()*TAU, 16.0, color)
	
	if pos.y < 200:
		Bullets.collect_all(item_kit, self);
	
	for i in items.size():
		var item_id : PackedInt64Array = items[i]
		
		var y1 := 1.0
		var y2 := 0.5
		var x1 := 300.0
		var x2 := 600
		var m := (y2-y1) / (x2-x1)
		
		var max_value := 1000.0
		var value : float = max_value if Bullets.get_is_auto_collected(item_id) \
									  else max_value * clamp(m * (pos.y - x1) + y1, 0.5, 1.0)
		
		
		var color : Color = Color(floor(value) * 10, 0, 1 if value == max_value else 0, 0);
		
		var item_pos : Vector2 = Bullets.get_position(item_id)
		
		Bullets.create_particle(item_text_kit, item_pos, Vector2(0, -0.5), 0.0, 16, color)
		
	
	if t % 60 == 0:
		pass
		print("Bullets: ", Bullets.get_total_active_bullets(), "; FPS: ", Engine.get_frames_per_second())
		print("Collisions: ", collisions[0].size(), "; Grazes: ", collisions[1].size())
