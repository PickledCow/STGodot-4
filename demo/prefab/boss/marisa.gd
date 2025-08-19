extends Boss

var impact_star := preload("res://prefab/boss/marisa_star.tscn")

var lightning_data: PackedFloat64Array
var stars : Array[PackedFloat64Array]

var exhausts : Array[PackedFloat64Array]

var lighting_cycle : Array[int] = [180]

var strike_time : Array[int] = [180, 170, 160, 150, 135]
var strike_star_count : Array[int] = [60, 90, 120, 150, 180]
var curve_laser_count : Array[int] = [7, 9, 12, 16, 24]
var strike_count := 3

var charging_at_player := false
var crash_star_count : Array[int] = [30, 60, 90, 135, 180]
var charge_speed : Array[float] = [12.0, 16.0, 20.0, 25.0, 30.0]
var crash_duration := 360
var crash_star_speed : Array[float] = [4.0, 5.0, 7.0, 8.0, 9.0]

var star_spacing : Array[float] = [192.0, 150.0, 128.0, 102.0, 96.0]

var crashed_wall := 0
var crashed_time := -1
var crash_position := Vector2()

var exhaust_rate : Array[int] = [1, 2, 2, 2, 3]
var exhaust_spread : Array[float] = [1.0, 1.0, 1.0, 1.1, 1.5]


func _post_ready() -> void:
	lightning_data = PackedFloat64Array()
	lightning_data.resize(16)
	lightning_data[0] = 1024
	lightning_data[1] = 2048
	lightning_data[2] = 128
	lightning_data[3] = 1024
	lightning_data[4] = 0.25
	lightning_data[5] = 4					# anim frame, 1 for no animation (integer)
	lightning_data[6] = 1
	lightning_data[7] = 512 - 128
	lightning_data[8] = 832
	lightning_data[9] = 128
	lightning_data[10] = 128
	lightning_data[11] = 1
	lightning_data[12] = 1
	lightning_data[13] = 1
	lightning_data[14] = 0				# damage type
	lightning_data[15] = 0				# damage amount
	
	stars.resize(7)
	
	stars[0] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.RED)
	stars[1] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.ORANGE)
	stars[2] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.YELLOW)
	stars[3] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.GREEN)
	stars[4] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.CYAN)
	stars[5] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.BLUE)
	stars[6] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR_LARGE, BulletConstructor.COLORS_LARGE.PURPLE)
	
	
	exhausts.resize(7)
	
	exhausts[0] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.RED)
	exhausts[1] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.ORANGE)
	exhausts[2] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.YELLOW)
	exhausts[3] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.GREEN)
	exhausts[4] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.CYAN)
	exhausts[5] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.BLUE)
	exhausts[6] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.PURPLE)	
	
	t = -30
	t_float = -30.0
		
func _pre_process(_time_scale: float) -> void:
	#if t % 10 == 0:
		#Bullets.create_bullet_a1(position, 4.0, PI * 0.5, stars[0], false)
	#
	#return
	if t >= 0:
		# Three strikes
		if t % (crash_duration + strike_time[difficulty] * strike_count) < strike_time[difficulty] * strike_count:
			var u := t % (crash_duration + strike_time[difficulty] * strike_count)
			# Strikes
			if u % strike_time[difficulty] == 0:
				SFX.play("charge_short")
				Bullets.create_straight_laser(position + Vector2(0, 64), PI * 0.5, 1500, 256, 0, 0, 60, 45, lightning_data, true)
				Bullets.create_straight_laser(position + Vector2(-8, 64), PI * 0.51, 1500, 192, 0, 0, 60, 45, lightning_data, true)
				Bullets.create_straight_laser(position + Vector2(8, 64), PI * 0.49, 1500, 192, 0, 0, 60, 45, lightning_data, true)
			# Strike hits
			if u % strike_time[difficulty] == 60:
				SFX.play("explode")
				System.shake_screen(30, 15)
				
				# Stars
				for i in strike_star_count[difficulty]:
					var v := Vector2(randf_range(1.0, 16.0), 0.0).rotated(TAU / 8.0 + randf()*TAU / 4.0 + TAU * 0.5) + Vector2(0.0, -8.0)
					var b = Bullets.create_bullet_b1(
						Vector2(position.x, 1100.0), 
						v, 
						Vector2(0.0, 0.2),
						Vector2(0.0, 10.0),
						false,
						stars[randi()%7],
						false
					)
					Bullets.set_spin(b, 0.1 if v.x > 0.0 else -0.1)
					Bullets.set_rotation(b, randf()*TAU)
				var a := randf()*TAU
				var lr := 1.0 if System.player.position.x > position.x else -1.0
				
				# Curve lasers
				for i in curve_laser_count[difficulty]:
					var b = Bullets.create_curve_laser(position, 12.0, a + i * TAU / curve_laser_count[difficulty], 45, 64, 8, 8, lightning_data, true)
					Bullets.set_wvel(b, lr * 0.02)
				
				# Pickupable stars
				var l_star : Enemy = impact_star.instantiate()
				var r_star : Enemy = impact_star.instantiate()
				l_star.position = Vector2(position.x - 128, 925)
				r_star.position = Vector2(position.x + 128, 925)
				l_star.lifespan = 120
				r_star.lifespan = 120
				get_parent().add_child(l_star)
				get_parent().add_child(r_star)
			
			# Movement
			if u % strike_time[difficulty] == 60 + 45:
				if u < strike_time[difficulty] * (strike_count - 1):
					set_destination(Vector2(clamp(System.player.position.x, 100.0, 900.0), 300.0), 45.0)
				else:
					set_destination(Vector2(500, 200), 60.0)
	
	#if t % 120 == 0:
		#var a := randf()*TAU
		#for i in 10:
			#var b = Bullets.create_curve_laser(position, 8.0, a + i * TAU / 10.0, 60, 64.0, 8, 8, lightning_data, true)
			#Bullets.set_wvel(b, 0.01)
	#if t % 120 == 60:
		#var a := randf()*TAU
		#for i in 10:
			#var b = Bullets.create_curve_laser(position, 8.0, a + i * TAU / 10.0, 60, 64.0, 8, 8, lightning_data, true)
			#Bullets.set_wvel(b, -0.01)
		
		# Charge attack
		else:
			var u := t % (crash_duration + strike_time[difficulty] * strike_count) - strike_time[difficulty] * strike_count
			if u == 0:
				crashed_time = -1
				SFX.play("charge_long")
				set_destination(Vector2(500, 150), 125)
				$aim.show()
			if u <= 120:
				$aim.rotation = (System.player.position - position).angle()
			if u == 120:
				var direction : Vector2 = (System.player.position - position).normalized()
				velocity = direction * charge_speed[difficulty]
				charging_at_player = true
				SFX.play("spark")
				$aim.hide()
			if charging_at_player:
				SFX.play("shoot1")
				for j in exhaust_rate[difficulty]:
					for i in 7:
						var a := velocity.angle() + randf_range(-1.0, 1.0) * exhaust_spread[difficulty]
						Bullets.create_bullet_a1(position, randf_range(3.0, 6.0), a + PI, exhausts[i], true)
				
				if position.x < 0.0 or position.x > 1000.0 or position.y < 0.0 or position.y > 1000.0:
					charging_at_player = false
					velocity = Vector2()
					if position.x < 0.0:
						crashed_wall = 0
						position.x = 0.0
					elif position.x > 1000.0:
						crashed_wall = 1
						position.x = 1000.0
					elif position.y < 0.0:
						crashed_wall = 2
						position.y = 0.0
					elif position.y > 1000.0:
						crashed_wall = 3
						position.y = 1000.0
						
					crashed_time = u
					
					SFX.play("explode")
					System.shake_screen(30, 30)
					SFX.stop("spark", 1.0)
					crash_position = position
					set_destination(
						Vector2(clamp(System.player.position.x, 100.0, 900.0), 300), 
						120
					)
					
					# Star fragment
					for i in crash_star_count[difficulty]:
						var v := Vector2(randf_range(0.0, crash_star_speed[difficulty]), 0.0).rotated(randf()*TAU)
						v += (Vector2(500, 500) - position).normalized() * 6.0 * Vector2(1.0, 2.0)
						var b = Bullets.create_bullet_b1(
							position, 
							v, 
							Vector2(0.0, 0.2),
							Vector2(0.0, 30.0),
							false,
							stars[randi()%7],
							false
						)
						Bullets.set_spin(b, 0.1 if v.x > 0.0 else -0.1)
			
			if crashed_time > 0 and (u - crashed_time) % 10 == 0 and (u - crashed_time) < 10 * 2:
				var i := float(u - crashed_time) / 10.0
				var l_star : Enemy = impact_star.instantiate()
				var r_star : Enemy = impact_star.instantiate()
				var l_offset = Vector2(-128.0 - i * star_spacing[difficulty], -75.0)
				var r_offset = Vector2(128.0 + i * star_spacing[difficulty], -75.0)
				if crashed_wall == 0:
					l_offset = l_offset.rotated(PI * 0.5)
					r_offset = r_offset.rotated(PI * 0.5)
				elif crashed_wall == 1:
					l_offset = l_offset.rotated(-PI * 0.5)
					r_offset = r_offset.rotated(-PI * 0.5)
				elif crashed_wall == 2:
					l_offset = l_offset.rotated(PI)
					r_offset = r_offset.rotated(PI)
				
				
				l_star.position = crash_position + l_offset
				r_star.position = crash_position + r_offset
				l_star.lifespan = 210
				r_star.lifespan = 210
				get_parent().add_child(l_star)
				get_parent().add_child(r_star)
					
			if u == crash_duration - 60:
				set_destination(
					Vector2(clamp(System.player.position.x, 100.0, 900.0), 300), 
					60
				)
