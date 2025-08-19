extends Boss

var parasols := preload("res://prefab/boss/parasol.tscn")
var raindrops : Array[PackedFloat64Array]
var mentos : PackedFloat64Array


var para_offset := Vector2(-90, -43)

var a := 0.0
var a2 := 0.0
var step : Array[float] = 			[0.2,   0.14,  0.122,  0.1,   0.075]
var step2 : Array[float] = 			[1.0,   2.0,   2.0,   2.0,   2.0]
var offset : Array[float] = 		[0.015, 0.004, 0.0045, 0.0055, 0.00675]
var rate : Array[int] = 			[4,     2,     2,     2,     2]
var way : Array[int] = 				[2,     2,     3,     4,     5]
var speed : Array[float] =			[5.0,   6.0,   6.5,   7.0,   8.0]
var umbrella_count : Array[int] = 	[3,     4,     5,     6,     8]
var umbrella_speed : Array[float] = [5.0,   5.3,   5.6,   6.0,   6.25]

func _post_ready() -> void:
	#t = -120
	#t_float = -120.0
	raindrops.resize(8)
	raindrops[0] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.RED)
	raindrops[1] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.ORANGE)
	raindrops[2] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.YELLOW)
	raindrops[3] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.GREEN)
	raindrops[4] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.TEAL)
	raindrops[5] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.CYAN)
	raindrops[6] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.BLUE)
	raindrops[7] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.DROPLET, BulletConstructor.COLORS.PURPLE)

	mentos = System.get_bullet_data(BulletConstructor.BULLET_TYPE.MENTOS, BulletConstructor.COLORS_LARGE.CYAN)
	
	
func _pre_process(_time_scale: float) -> void:
	if t >= 0:
		
		if t % 2 == 0:
			if System.player.position.y < position.y:
				var angle := randf()*TAU
				for i in 0:
					Bullets.create_bullet_a1(position, 15.0, angle + i * TAU / 60.0, mentos, true)
		
		if t % 210 < 150 and t % rate[difficulty] == 0:
			SFX.play("shoot1")
			a += step[difficulty]
			for i in 8:
				for j in way[difficulty]:
					var angle := a + i * ((step[difficulty] - offset[difficulty]) * step2[difficulty]) + j * TAU / way[difficulty]
					Bullets.create_bullet_a1(position + para_offset + Vector2(32, 0).rotated(angle), speed[difficulty], angle, raindrops[7-i], false)
		
		if t % 210 == 150:
			random_walk(Vector2(300, 300), Vector2(700, 300), Vector2(200, 0), 60)
		
		if t % 210 == 180:
			SFX.play("warning")
			var off := randf()*TAU
			for i in umbrella_count[difficulty]:
				var angle := off + i * TAU / umbrella_count[difficulty]
				var parasol : Enemy = parasols.instantiate()
				parasol.position = position
				parasol.velocity = Vector2(umbrella_speed[difficulty], 0.0).rotated(angle)
				parasol.acceleration = Vector2(0.0, 0.05)
				get_parent().add_child(parasol)
				
