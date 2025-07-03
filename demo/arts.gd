extends Node2D

var data: PackedFloat64Array

var red_butterfly: PackedFloat64Array
var blue_butterfly: PackedFloat64Array

var item_data: PackedFloat64Array

var t := 0

@export var texture : Texture2D
@export var mat : Material

var pos := Vector2()

# Called when the node enters the scene tree for the first time.
func _ready():
	Bullets.init(self)
	
	data = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.BLUE)
	
	item_data = System.get_item_data(7)
	

func _process(_delta):
	
	if false:
		var shoot_pos = Vector2(1280, 720*0.5) * 0.5
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
		pass
		#if t % 2 == 3:
			#Bullets.create_item(item_kit, Vector2(randf_range(0, 1280), -100), 0.0, randf()*TAU, 0.0, item_data)
			##Bullets.set_damage()
		#
		for i in 1:
			Bullets.create_item(Vector2(1280 * 0.5, -200), randf_range(2.0, 20.0), randf()*TAU, 60.0, item_data, false)
	##print(Bullets.get_total_active_bullets())
		
	
	if t % 60 == 0:
		pass
		#print(get_viewport_rect().size)
		#print("Bullets: ", Bullets.get_total_active_bullets(), "; FPS: ", Engine.get_frames_per_second())
		#print("Collisions: ", collisions[0].size(), "; Grazes: ", collisions[1].size())
	
	t += 1
	
	
