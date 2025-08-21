extends Boss

var red_ball : PackedFloat64Array
var red_snow : PackedFloat64Array
var red_mentos : PackedFloat64Array

var purple_ball : PackedFloat64Array
var purple_snow : PackedFloat64Array
var purple_mentos : PackedFloat64Array

var blue_bubble : PackedFloat64Array

var lightning_data: Array[PackedFloat64Array]
var ud := 1.0
var lr := 1.0
var lr2 := 1.0

var a := 0.0

var slash_x_positions : Array[float]

var bubble_cycle_time := 120
var slash_cycle_offset := 150
var bubble_pop_offset := 30
var bubble_rate : Array[int] = [15, 13, 11, 9, 7]

var pop_positions : Array[Vector2] = []

var impact_star := preload("res://prefab/boss/marisa_star.tscn")

var bubble_fast := 5.0
var bubble_slow := 2.5

var pop_fast : Array[float] = [5.25, 5.5, 5.75, 6.0, 6.25]
var pop_slow : Array[float] = [4.0, 4.0, 4.0, 4.0, 4.0]

var pop_density : Array[int] = [4, 5, 7, 8, 9]

func _post_ready() -> void:

	blue_bubble = 		System.get_bullet_data(BulletConstructor.BULLET_TYPE.BUBBLE, BulletConstructor.COLORS_LARGE.BLUE)
	
	lightning_data.resize(4)
	for i in 4:
		lightning_data[i] = PackedFloat64Array()
		lightning_data[i].resize(16)
		lightning_data[i][0] = 1024 + 128 * i
		lightning_data[i][1] = 2048
		lightning_data[i][2] = 128
		lightning_data[i][3] = 1024
		lightning_data[i][4] = 0.25
		lightning_data[i][5] = 1					# anim frame, 1 for no animation (integer)
		lightning_data[i][6] = 1
		lightning_data[i][7] = 0.0
		lightning_data[i][8] = 0.0
		lightning_data[i][9] = 0.0
		lightning_data[i][10] = 0.0
		lightning_data[i][11] = 1
		lightning_data[i][12] = 1
		lightning_data[i][13] = 1
		lightning_data[i][14] = 0				# damage type
		lightning_data[i][15] = 0				# damage amount

	red_ball = 		System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.RED)
	red_snow = 		System.get_bullet_data(BulletConstructor.BULLET_TYPE.SNOWBALL, BulletConstructor.COLORS.RED)
	red_mentos = 	System.get_bullet_data(BulletConstructor.BULLET_TYPE.MENTOS, BulletConstructor.COLORS_LARGE.RED)
	
	purple_ball = 	System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.PURPLE)
	purple_snow = 	System.get_bullet_data(BulletConstructor.BULLET_TYPE.SNOWBALL, BulletConstructor.COLORS.PURPLE)
	purple_mentos = System.get_bullet_data(BulletConstructor.BULLET_TYPE.MENTOS, BulletConstructor.COLORS_LARGE.PURPLE)




func _pre_process(_time_scale: float) -> void:
	if t >= 0:
		
		if t == 0:
			set_destination(Vector2(100, 500), 60)
		
		if t % bubble_cycle_time == 0:
			lr *= -1.0
			a = PI * (0.5 + lr * lr2 * 0.5)
		
		# Shoot bubbles
		if t % bubble_rate[difficulty] == 0:
			var time_to_pop : float = bubble_cycle_time * 2 - (t - slash_cycle_offset - bubble_pop_offset) % (bubble_cycle_time * 2)

			SFX.play("shoot1")
			var b1 = Bullets.create_bullet_a1(
				Vector2(500, 0),
				bubble_fast,
				a,
				blue_bubble,
				true
			)
			if t >= bubble_cycle_time:
				Bullets.set_lifespan(b1, time_to_pop)
				pop_positions.append(Vector2(500, 0) + Vector2(bubble_fast * time_to_pop, 0.0).rotated(a))
			if t >= bubble_cycle_time:
				var b2 = Bullets.create_bullet_a1(
					Vector2(500, 0),
					bubble_slow,
					a,
					blue_bubble,
					true
				)
				Bullets.set_lifespan(b2, time_to_pop)
				pop_positions.append(Vector2(500, 0) + Vector2(bubble_slow * time_to_pop, 0.0).rotated(a))
			a -= lr * lr2 * PI * bubble_rate[difficulty] / bubble_cycle_time
		
		# Windup 
		if t % (bubble_cycle_time * 2) == 60 and t >= bubble_cycle_time * 2:
			SFX.play("charge_long")
			Bullets.set_time_scale(1.0 / 3.0)
			System.time_scale = 1.0 / 3.0
			$Suck.emitting = true
			$Suck.position = Vector2()
		
		# Slash
		if t % (bubble_cycle_time * 2) == slash_cycle_offset and t >= bubble_cycle_time * 2:
			SFX.play("explode")
			Bullets.set_time_scale(1.0)
			System.time_scale = 1.0
			position = Vector2(500 + lr2 * 400, 500)
			lr2 *= -1.0
			
			# Slash lines
			for i in 5:
				var y : float = 150 + 100 * i
				Bullets.create_straight_laser(Vector2(50, y), 0.0, 900, 32, 0.0, 0.0, 0.0, 60, lightning_data[randi()%4], true)
			
			# Impact star
			for i in 6:
				var y : float = 100 + 100 * i
				var star : Enemy = impact_star.instantiate()
				star.position = Vector2(500 - lr2 * 400, y)
				star.lifespan = 180
				get_parent().add_child(star)

		# Pop
		if t % (bubble_cycle_time * 2) == slash_cycle_offset + bubble_pop_offset and t >= bubble_cycle_time * 2:
			SFX.play("warning")
			for pos in pop_positions:
				#Bullets.create_bullet_a1(pos, 4.0, PI * 0.5, blue_rice, false)
				if pos.y < 800.0:
					var threshold := 400.0
					var ball := purple_ball if pos.y < threshold else red_ball
					var snow := purple_snow if pos.y < threshold else red_snow
					var mentos := purple_mentos if pos.y < threshold else red_mentos
					for bullet in [ball, snow, mentos]:
						for i in pop_density[difficulty]:
							var s := randf_range(pop_slow[difficulty], pop_fast[difficulty])
							Bullets.create_bullet_a2(pos + Vector2(randf()*16, 0).rotated(randf()*TAU), 0.0, randf()*TAU, 0.0075 * s, s, 0.0, bullet, false)
				
			
			pop_positions.clear()
			#@warning_ignore("integer_division")
			#for i in (bubble_cycle_time * 2) / bubble_rate:
				#var angle = PI * (0.5 - lr2 * 0.5) + lr2 * PI * i * bubble_rate / bubble_cycle_time
				#for speed in [2.0, 6.0]:
					#var dist : float = speed * (slash_cycle_offset + bubble_pop_offset - i * bubble_rate)
					#var pos := Vector2(dist, 0.0).rotated(angle)
					#for j in 1:
						#Bullets.create_bullet_a1(Vector2(500, 0) + pos, 4.0, PI * 0.5, blue_rice, false)
			#
		#

func _post_death():
	System.time_scale = 1.0
	Bullets.set_time_scale(1.0)
