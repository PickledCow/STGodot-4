extends Node2D

var data: PackedFloat64Array
var data2: PackedFloat64Array

var laser_data: PackedFloat64Array

var red_butterfly: PackedFloat64Array
var blue_butterfly: PackedFloat64Array

var amulets : Array[PackedFloat64Array]

var item_data: PackedFloat64Array

var t := 0

@export var texture : Texture2D
@export var mat : Material

var enemy := preload("res://system/enemy/fairy/test_fairy.tscn")

var pos := Vector2()

var debug_shoot := true

# Called when the node enters the scene tree for the first time.
func _ready():
	Bullets.init(self)
	
	data = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.BLUE)
	#data = System.get_bullet_data(BulletConstructor.BULLET_TYPE.KNIFE, BulletConstructor.COLORS_LARGE.BLUE)
	#data2 = System.get_bullet_data(BulletConstructor.BULLET_TYPE.KNIFE, BulletConstructor.COLORS_LARGE.RED)
	
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.BLUE))
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.CYAN))
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.PURPLE))
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.YELLOW))
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.RED))
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.GREEN))
	amulets.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.AMULET, BulletConstructor.COLORS.ORANGE))
	
	item_data = System.get_item_data(7)
	
	laser_data = PackedFloat64Array()
	laser_data.resize(16)
	laser_data[0] = 1024
	laser_data[1] = 2048
	laser_data[2] = 128
	laser_data[3] = 1024
	laser_data[4] = 0.25
	laser_data[5] = 4					# anim frame, 1 for no animation (integer)
	laser_data[6] = 1
	laser_data[7] = 512 - 128
	laser_data[8] = 832
	laser_data[9] = 128
	laser_data[10] = 128
	laser_data[11] = 1
	laser_data[12] = 1
	laser_data[13] = 1
	laser_data[14] = 0				# damage type
	laser_data[15] = 0				# damage amount



func _process(_delta):
	#return
	#@warning_ignore("unreachable_code")
	
	if Input.is_action_just_pressed("debug_toggle"):
		t = 0
		debug_shoot = !debug_shoot
	if !debug_shoot:
		return
	if true:
		if t % 300 == 0:
			pass
			Bullets.create_curve_laser(Vector2(500, 300), 5.0, PI/2, 120, 64, 16, 16, laser_data, false)
	
	if false:
		
		for i in 0:
			Bullets.create_item(Vector2(randf_range(0, 1000), -200), randf_range(2.0, 20.0), randf()*TAU, 60.0, item_data, false)
		var shoot_pos= Vector2(1000, 1000*0.5) * 0.5
		var g := 3
		if t % g == 0 and t % 1500 < 1500 - 60:
			SFX.play("shoot1")
			var rate := 0.01 / g
			var u := t % 1500
			
			var cs = 7
			
			for i in cs:
				var r = 200 - 10 * i
				var lr = 1
				var x = cos(13 * lr * u * rate)
				var y = sin(7 * lr * u * rate)
				var a = TAU * i / float(cs) - u / 91.0 * 21.0 / g
				var s = 3 + i * 0.666
				for j in range(2, 0, -1):
					Bullets.create_bullet_a2(shoot_pos + Vector2(x, y).rotated(TAU * i / float(cs)) * r, 1, a + j*0.015, 0.1, s, 0.0, amulets[i], false)
					Bullets.create_bullet_a2(shoot_pos + Vector2(x, y).rotated(TAU * i / float(cs)) * r, 1, a - j*0.015, 0.1, s, 0.0, amulets[i], false)
				Bullets.create_bullet_a2(shoot_pos + Vector2(x, y).rotated(TAU * i / float(cs)) * r, 1, a, 0.1, s, 0.0, amulets[i], false)
					
		
		
		if t % 120 == 120:
			for i in 120:
				var _s := randf_range(2.0, 8.0)
				#Bullets.create_shot_a2(bullet_kit, shoot_pos, s, randf()*TAU, -s / 120.0, 0.0, red_butterfly, true)
		
		
		if t % 5 == 5:
			SFX.play("shoot1")
			for i in 30:
				#var ang = pos.angle_to_point(shoot_pos) + randf_range(-0.1, 0.1) + PI
				#var ang := t * 0.01  + randf_range(-0.3, 0.3) + PI
				var ang = randf()*TAU
				var s = randf_range(1.8, 4.0)
				Bullets.create_bullet_a1(shoot_pos + Vector2(randf()*128, 0).rotated(randf()*TAU), s, ang, data, false)
				#var rot = randf_range(0.001, 0.002)
				#Bullets.create_bullet_a2(shoot_pos, s, randf()*TAU, 0.0, 0.0, rot * s, data, false)
				#Bullets.create_bullet_a2(shoot_pos, s, randf()*TAU, 0.0, 0.0, -rot * s, data2, false)
				#if id[0] == -1:
					#break
	if false:
		
		var p := 240
		if t % p == 0:
			for i in 10:
				var a := TAU * i * 0.1
				Bullets.create_straight_laser(Vector2(500, 500) + Vector2(128, 0).rotated(a), a, 500, 128, 0.075, 0.125, 60, 120, laser_data, true)
				
			#@warning_ignore("integer_division")
			#var lr = ((t / p) % 2) * 2 - 1
			#
			#var new_enemy := enemy.instantiate()
			#new_enemy.position = Vector2(500 + lr * randf_range(100, 400), -100)
			#new_enemy.velocity = Vector2(0, 5)
			#new_enemy.acceleration = Vector2(-0.05 * lr, 0.0)
			#new_enemy.max_health = 20
			#get_parent().add_child(new_enemy)
		#
		
		#for i in 1:
			#Bullets.create_item(Vector2(1000 * 0.5, -200), randf_range(2.0, 20.0), randf()*TAU, 60.0, item_data, false)
		
		
	
	if t % 60 == 0:
		pass
	t += 1
	
	
