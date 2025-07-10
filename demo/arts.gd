extends Node2D

var data: PackedFloat64Array

var laser_data: PackedFloat64Array

var red_butterfly: PackedFloat64Array
var blue_butterfly: PackedFloat64Array

var item_data: PackedFloat64Array

var t := 0

@export var texture : Texture2D
@export var mat : Material

var enemy := preload("res://system/enemy/fairy/test_fairy.tscn")

var pos := Vector2()

# Called when the node enters the scene tree for the first time.
func _ready():
	Bullets.init(self)
	
	data = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.BLUE)
	
	item_data = System.get_item_data(7)
	
	laser_data = PackedFloat64Array()
	laser_data.resize(15)
	laser_data[0] = 128
	laser_data[1] = 0
	laser_data[2] = 64
	laser_data[3] = 1024
	laser_data[4] = 64.0				# bullet size [0, inf)
	laser_data[5] = 0.5
	laser_data[6] = 0
	laser_data[7] = 1					# anim frame, 1 for no animation (integer)
	laser_data[8] = 0					# spin
	laser_data[9] = 1
	laser_data[10] = 1
	laser_data[11] = 1
	laser_data[12] = 1
	laser_data[13] = 0				# damage type
	laser_data[14] = 0				# damage amount

func _process(_delta):
	
	if false:
		var shoot_pos = Vector2(1000, 1000*0.5) * 0.5
		if t % 120 == 120:
			for i in 120:
				var _s := randf_range(2.0, 8.0)
				#Bullets.create_shot_a2(bullet_kit, shoot_pos, s, randf()*TAU, -s / 120.0, 0.0, red_butterfly, true)
		
		
		if t % 1 == 0:
			SFX.play("shoot1")
			for i in 5:
				#var ang = pos.angle_to_point(shoot_pos) + randf_range(-0.1, 0.1) + PI
				#var ang := t * 0.01  + randf_range(-0.3, 0.3) + PI
				var ang = randf()*TAU
				Bullets.create_bullet_a1(shoot_pos, randf_range(4.0, 8.0), ang, data, false)
				#if id[0] == -1:
					#break
	else:
		if t == 0:
			for i in 10:
				Bullets.create_straight_laser(Vector2(500, 500), TAU * i * 0.1, 800, 64, 0, 60, 120, laser_data, true)
		
		var p := 20
		if t % p == p:
			@warning_ignore("integer_division")
			var lr = ((t / p) % 2) * 2 - 1
			
			var new_enemy := enemy.instantiate()
			new_enemy.position = Vector2(500 + lr * randf_range(100, 400), -100)
			new_enemy.velocity = Vector2(0, 5)
			new_enemy.acceleration = Vector2(-0.05 * lr, 0.0)
			new_enemy.max_health = 20
			get_parent().add_child(new_enemy)
		
		
		#for i in 1:
			#Bullets.create_item(Vector2(1000 * 0.5, -200), randf_range(2.0, 20.0), randf()*TAU, 60.0, item_data, false)
		
		
	
	if t % 60 == 0:
		pass
	t += 1
	
	
