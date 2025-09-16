extends Boss


@export var second_attack_type_list : Array[System.ATTACK_TYPE] = []
@export var second_attack_name_list : Array[String] = []

var phase := 0

var knife : PackedFloat64Array
var bullet : PackedFloat64Array
var rain : Array[PackedFloat64Array]
var water : Array[PackedFloat64Array]
var water_top : PackedFloat64Array
var jellybean : PackedFloat64Array

var lightning_data: PackedFloat64Array
var chain_lightning_data: PackedFloat64Array

var red_laser_data: PackedFloat64Array
var blue_laser_data: PackedFloat64Array

var cutter := preload("res://prefab/boss/cutter.tscn")
var bomb := preload("res://prefab/boss/real_bomb.tscn")
var impact_star := preload("res://prefab/boss/marisa_star.tscn")
var kogasa := preload("res://prefab/boss/kogasa_friend.tscn")

var knife_speeds : Array[float] = [5.0, 6.0, 8.0, 9.0, 10.0]
var knife_densities : Array[int] = [2, 1, 4, 3, 2]
var knife_rates : Array[int] = [3, 1, 3, 2, 1]
var knife_sound_rate : Array[int] = [2, 2, 1, 1, 1]

var red_butterfly : PackedFloat64Array
var blue_butterfly : PackedFloat64Array
var pink_butterfly : PackedFloat64Array

var blue_bubble : PackedFloat64Array

var bullet_timer := 0.0
var bullet_speeds : Array[float] = [6.0, 7.0, 8.0, 10.0, 12.0]
var bullet_rates : Array[float] = [0.2, 0.3, 0.5, 0.65, 0.75]
var finale_phase = 0

var death_timer := 0.0

var rain_rates : Array[int] = [9, 6, 4, 3, 2, 1, 1]
var rain_speeds : Array[float] = [6.0, 8.0, 9.0, 10.0, 12.0, 15.0, 18.0]

var GA := PI * (3 - sqrt(5))
var a := 0.0
var a2 := 0.0

var bomb_cycle := 0

var lr1 := 1.0
var lr2 := 1.0
var star_spawn_position : Vector2

var difficulty_raised := false

var debug_low_health := false

var finale_first_laser_shot := false

func _pre_ready() -> void:
	if debug_low_health:
		max_health = 100

func _post_ready() -> void:
	red_butterfly = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BUTTERFLY, BulletConstructor.COLORS_LARGE.RED)
	blue_butterfly = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BUTTERFLY, BulletConstructor.COLORS_LARGE.BLUE)
	pink_butterfly = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BUTTERFLY, BulletConstructor.COLORS_LARGE.PURPLE)
	pink_butterfly[Bullets.DATA_SIZE] *= 1.1
	jellybean = System.get_bullet_data(BulletConstructor.BULLET_TYPE.JELLYBEAN, BulletConstructor.COLORS_LARGE.PURPLE)
	
	blue_bubble = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BUBBLE, BulletConstructor.COLORS_LARGE.BLUE)
	
	knife = System.get_bullet_data(BulletConstructor.BULLET_TYPE.KNIFE, BulletConstructor.COLORS_LARGE.BLUE)
	knife[Bullets.DATA_SIZE] *= 1.5
	
	bullet = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.GREY)
	bullet[Bullets.DATA_SIZE] *= 1.5
	
	rain.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE_LARGE, BulletConstructor.COLORS_LARGE.CYAN))
	rain.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE_LARGE, BulletConstructor.COLORS_LARGE.BLUE))
	rain.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE_LARGE, BulletConstructor.COLORS_LARGE.GREY))
	rain.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE, BulletConstructor.COLORS.CYAN))
	rain.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE, BulletConstructor.COLORS.BLUE))
	rain.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE, BulletConstructor.COLORS.WHITE))
	for i in 3:
		rain[i+3][Bullets.DATA_SIZE] *= 1.5
	
	water.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.BLUE_D))
	water.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL_OUTLINE, BulletConstructor.COLORS.BLUE_D))
	water.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.RICE, BulletConstructor.COLORS.BLUE_D))
	water.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.BACTERIA, BulletConstructor.COLORS.BLUE_D))
	water.append(System.get_bullet_data(BulletConstructor.BULLET_TYPE.MENTOS, BulletConstructor.COLORS_LARGE.BLUE))
	
	for i in 4:
		water[i][Bullets.DATA_SIZE] *= 1.2
	
	water_top = System.get_bullet_data(BulletConstructor.BULLET_TYPE.MENTOS, BulletConstructor.COLORS_LARGE.BLUE)
	
	
	red_laser_data = PackedFloat64Array()
	red_laser_data.resize(16)
	red_laser_data[0] = 128
	red_laser_data[1] = 2560
	red_laser_data[2] = 64
	red_laser_data[3] = 1024
	red_laser_data[4] = 0.25
	red_laser_data[5] = 1					# anim frame, 1 for no animation (integer)
	red_laser_data[6] = 1
	red_laser_data[7] = 128
	red_laser_data[8] = 832
	red_laser_data[9] = 128
	red_laser_data[10] = 128
	red_laser_data[11] = 1
	red_laser_data[12] = 1
	red_laser_data[13] = 1
	red_laser_data[14] = 0				# damage type
	red_laser_data[15] = 0				# damage amount
	
	blue_laser_data = PackedFloat64Array()
	blue_laser_data.resize(16)
	blue_laser_data[0] = 384
	blue_laser_data[1] = 2560
	blue_laser_data[2] = 64
	blue_laser_data[3] = 1024
	blue_laser_data[4] = 0.25
	blue_laser_data[5] = 1					# anim frame, 1 for no animation (integer)
	blue_laser_data[6] = 1
	blue_laser_data[7] = 512 - 128
	blue_laser_data[8] = 832
	blue_laser_data[9] = 128
	blue_laser_data[10] = 128
	blue_laser_data[11] = 1
	blue_laser_data[12] = 1
	blue_laser_data[13] = 1
	blue_laser_data[14] = 0				# damage type
	blue_laser_data[15] = 0				# damage amount
	
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
	
	chain_lightning_data = PackedFloat64Array()
	chain_lightning_data.resize(16)
	chain_lightning_data[0] = 1024
	chain_lightning_data[1] = 2048
	chain_lightning_data[2] = 128
	chain_lightning_data[3] = 1024
	chain_lightning_data[4] = 0.25
	chain_lightning_data[5] = 4					# anim frame, 1 for no animation (integer)
	chain_lightning_data[6] = 1
	chain_lightning_data[7] = 0
	chain_lightning_data[8] = 0
	chain_lightning_data[9] = 0
	chain_lightning_data[10] = 0
	chain_lightning_data[11] = 1
	chain_lightning_data[12] = 1
	chain_lightning_data[13] = 1
	chain_lightning_data[14] = 0				# damage type
	chain_lightning_data[15] = 0				# damage amount
	
	#difficulty = System.DIFFICULTY.OVERDRIVE
	
func _post_process(time_scale: float) -> void:
	if death_timer > 0.0:
		death_timer -= System.time_scale
		next_attack = 10
		_on_death()
	
	if phase == 1 and current_attack == 1:
		if t == 0:
			attack_timer = (45 * 60) if not debug_low_health else 60
		health = 60 * 45 - t
		max_health = 60 * 45 
	if phase == 1 and current_attack == 2 and t == 0:
			attack_timer = 90 * 60
	
	if t == 0:
		System.clear_enemies = false
	
	
	if t >= 0:
		#dream_butterfly()
		#return
		#@warning_ignore("unreachable_code")
		if phase == 0:
			match current_attack:
				0:
					cuts(time_scale)
				1:
					wars(time_scale)
				2:
					weather(time_scale)
		else:
			match current_attack:
				0:
					dbdb()
				1:
					dance()
				2:
					dream_butterfly()

func dance():
	var cycle_factor = [20, 18, 16, 15, 14]
	var bullet_speed = [4, 4, 4, 4, 4]
	var butterfly_count = [2,3,3,4,5]
	var butterfly_reach = [80.0, 80.0, 72.0, 72.0, 69.0]
	var front_margin = [240, 180, 110, 90, 90]
	var back_margin = [300, 270, 240, 180, 170]
	
	var DENSITY = 5
	var CYCLE_TIME = cycle_factor[difficulty] * 60
	
	if t == 0:
		set_destination(Vector2(500, 500), 60)
	var u = t - 30
	
	if u >= 0:
		SFX.play("shoot1")
		var r = max(600 - u*0.75, 380)
		for i in 5:
			var angle = TAU * sin(u * PI / CYCLE_TIME) + i * 0.4 * PI - PI * 0.5
			var p = Vector2(500, 500) + Vector2(r,0).rotated(angle)
			if u % 2 == 0:
				@warning_ignore("integer_division")
				if (u+CYCLE_TIME/2) % (CYCLE_TIME) < CYCLE_TIME - front_margin[difficulty] and (u+CYCLE_TIME/2) % (CYCLE_TIME) > back_margin[difficulty]:
					Bullets.create_bullet_a1(p, bullet_speed[difficulty], angle - PI * 0.5, jellybean, false)
				@warning_ignore("integer_division")
				if (u+CYCLE_TIME/2) % (CYCLE_TIME) < CYCLE_TIME - front_margin[difficulty] && (u+CYCLE_TIME/2) % (CYCLE_TIME) > back_margin[difficulty]:
					Bullets.create_bullet_a1(p, bullet_speed[difficulty], angle + PI * 0.5, jellybean, false)
			#if u % CYCLE_TIME > 60:
			if u % 2 == 0:
				Bullets.create_bullet_a1(p, bullet_speed[difficulty], angle + PI * 1.02, jellybean, false)
		if u >= 300:
			if u % 120 == 0:
				SFX.play("warning")
				lr1 *= -1.0
				var type = red_butterfly if lr1 > 0.0 else blue_butterfly
				var o = position.angle_to_point(System.player.position)
				if lr1 > 0.0:
					o += PI
				for i in DENSITY:
					var aim = o + i * TAU / DENSITY
					for j in range(butterfly_count[difficulty], -1, -1):
						var angle1 = aim + j * PI / butterfly_reach[difficulty]
						var b1 = Bullets.create_bullet_a1(
							position,
							3.0 - 0.1 * j,
							angle1,
							type,
							false
						)
						Bullets.set_layer(b1, Bullets.get_layer(b1) + 1)
						if j != 0:
							var angle2 = aim - j * PI / butterfly_reach[difficulty]
							var b2 = Bullets.create_bullet_a1(
								position,
								3.0 - 0.1 * j,
								angle2,
								type,
								false
							)
							Bullets.set_layer(b2, Bullets.get_layer(b2) + 1)

func dream_butterfly():
	var bubble_density : Array[int] = [9, 11, 12, 13, 14]
	var butterfly_speed = [3, 3.5, 3.8, 4.0, 4.25]
	var main_density = [16, 20, 26, 30, 36]
	var criss_cross_density = [24, 32, 36, 40, 48]
	var trail_length = [0.0175, 0.02, 0.0225, 0.025, 0.0275]
	var main_rate = [30, 27, 24, 20, 16]
	var bubble_rate = [360, 300, 270, 240, 210]
	
	var what_the_fuck := false
	
	# Main Barrage Phase 1
	if t % main_rate[difficulty] == 0:
		lr1 *= -1.0
		SFX.play("shoot1")
		var density : int = main_density[difficulty]
		var offset := randf()*TAU
		var type = red_butterfly if lr1 > 0.0 else blue_butterfly
		for i in density:
			var angle := offset + i * TAU / density
			for j in range(4, -1, -1):
				var b = Bullets.create_bullet_a2(
					position,
					butterfly_speed[difficulty],
					angle,
					0.0,
					0.0,
					lr1 * trail_length[difficulty],
					type,
					false
				)
				Bullets.add_bullet_transform_a2(
					b, 
					Bullets.TRIGGER_TIME,
					60,
					Bullets.NO_CHANGE,
					Bullets.NO_CHANGE,
					-0.1,
					butterfly_speed[difficulty] * 1.5 - (butterfly_speed[difficulty] * 1.5  * 0.2) * j / 5.0,
					0.0)

	# Criss Cross Phase 2
	if health / max_health <= 0.80:
		if finale_phase == 0:
			finale_phase = 1
			Bullets.clear_bullets(Vector2(500, 500), 1000, true)
		if t % 120 == 0 and t >= 120:
			lr2 *= -1.0
			SFX.play("warning")
			a = randf()*TAU
			for i in criss_cross_density[difficulty]:
				var b1 = Bullets.create_bullet_a2(position, butterfly_speed[difficulty], a + i * TAU / criss_cross_density[difficulty], 0.0, 0.0, lr2 * 0.005, pink_butterfly, false)
				Bullets.set_layer(b1, Bullets.get_layer(b1) + 1)
		if t % 120 == 2 and t >= 120:
			for i in criss_cross_density[difficulty]:
				var b2 = Bullets.create_bullet_a2(position, butterfly_speed[difficulty], a + i * TAU / criss_cross_density[difficulty], 0.0, 0.0, -lr2 * 0.005, pink_butterfly, false)
				Bullets.set_layer(b2, Bullets.get_layer(b2) + 1)
	
	# Lasers
	if health / max_health <= 0.55:
		if finale_phase == 1:
			finale_phase = 2
			Bullets.clear_bullets(Vector2(500, 500), 1000, true)
		var laser_density = 4
		var laser_travel_time = 90
		var laser_delay = 120
		@warning_ignore("integer_division")
		var laser_travel_angle = PI * (0.75 + 0.125) 
		
		if t % 180 == laser_delay and finale_first_laser_shot:
			SFX.play("laser")
		if t % 180 == 0:
			finale_first_laser_shot = true
			for i in laser_density:
				var angle = i * TAU / laser_density + PI * 0.5
				var l1 = Bullets.create_straight_laser(
					position, angle, 1000, 64, 0, 0, laser_delay, 120, red_laser_data, true
				)
				var l2 = Bullets.create_straight_laser(
					position, angle, 1000, 64, 0, 0, laser_delay, 120, blue_laser_data, true
				)
				Bullets.set_wvel(l1, laser_travel_angle / laser_travel_time)
				Bullets.set_wvel(l2, -laser_travel_angle / laser_travel_time)
				Bullets.add_bullet_transform_a2(
					l1, Bullets.TRIGGER_TIME, laser_travel_time, 
					Bullets.NO_CHANGE, Bullets.NO_CHANGE, Bullets.NO_CHANGE, Bullets.NO_CHANGE, 0.0
				)
				Bullets.add_bullet_transform_a2(
					l2, Bullets.TRIGGER_TIME, laser_travel_time, 
					Bullets.NO_CHANGE, Bullets.NO_CHANGE, Bullets.NO_CHANGE, Bullets.NO_CHANGE, 0.0
				)
			
	# Bubbles
	if health / max_health <= 0.3:
		if finale_phase == 2:
			finale_phase = 3
			Bullets.clear_bullets(Vector2(500, 500), 1000, true)
			if difficulty == System.DIFFICULTY.OVERDRIVE:
				what_the_fuck = true
				difficulty = System.DIFFICULTY.LUNATIC
		
		var br := 210
		var bd := 14
		
		if not what_the_fuck:
			br = bubble_rate[difficulty]
			bd = bubble_density[difficulty]
		
		if t % br == 150:
			SFX.play("warning")
			var offset = position.angle_to_point(System.player.position)
			for i in bd:
				var angle : float = offset + i * PI / (bd - 1) - PI * 0.5
				for j in 16:
					Bullets.create_bullet_a1(
						position, 
						6 - j * 4.0 / 16.0,
						angle,
						blue_bubble,
						true
					)
			

func dbdb():
	var speed := [8.0, 10.0, 12.0, 13.0, 15.0]
	var second_speed := [2.5, 2.75, 3.0, 3.5, 4.0]
	var second_accel := 0.025
	var wvel := PI / 240.0
	var density := [50, 70, 80, 90, 120]
	var butterlfy_travel_time := [190, 170, 150, 120, 100]
	if t % butterlfy_travel_time[difficulty] == 30 and t >= butterlfy_travel_time[difficulty]:
		SFX.play("warning")
	
	if t % butterlfy_travel_time[difficulty] == 0:
		SFX.play("shoot1")
		for i in density[difficulty]:
			var speed_factor := randf_range(0.1, 1.0)
			@warning_ignore("integer_division")
			var type = red_butterfly if i < density[difficulty] / 2 else blue_butterfly
			@warning_ignore("integer_division")
			var lr = -1.0 if i < density[difficulty] / 2 else 1.0
			var b = Bullets.create_bullet_a2(position, speed[difficulty] * speed_factor, randf()*TAU, -speed[difficulty] * speed_factor / butterlfy_travel_time[difficulty], 0.0, 0.0, type, false)
			Bullets.add_bullet_transform_a2(
				b, 
				Bullets.TRIGGER_TIME, 
				butterlfy_travel_time[difficulty] + 30, 
				Bullets.NO_CHANGE, 
				Bullets.NO_CHANGE, 
				second_accel, 
				second_speed[difficulty], 
				lr * wvel
			)
			Bullets.add_bullet_transform_a2(
				b, 
				Bullets.TRIGGER_TIME, 
				butterlfy_travel_time[difficulty] + 270, 
				Bullets.NO_CHANGE, 
				Bullets.NO_CHANGE, 
				Bullets.NO_CHANGE, 
				Bullets.NO_CHANGE, 
				0.0
			)
			
	if t % 300 == 240:
		var target : float = System.player.position.x + randf_range(-50, 50)
		if target - position.x > 100:
			target = position.x + 100
		elif target - position.x < -100:
			target = position.x - 100
			
		set_destination(
			Vector2(clamp(target, 350, 650), 300),
			120
		)
	
	

func cuts(_time_scale: float) -> void:
	var pa : float = max(0.0, t - 60.0) / 200.0
	var r : float = min(350.0, 200.0 + max(0.0, t - 60.0) * 0.025)
	position = Vector2(500, 500) + Vector2(r, 0).rotated(pa - PI * 0.5)
	
	# Knives
	if t % knife_sound_rate[difficulty] == 0:
		SFX.play("shoot1")
	
	if t % knife_rates[difficulty] == 0:
		for i in knife_densities[difficulty]:
			var pre_travel := knife_speeds[difficulty] * i / knife_densities[difficulty]
			Bullets.create_bullet_a1(
				position + Vector2(48 + pre_travel, 0).rotated(a),
				knife_speeds[difficulty],
				a,
				knife,
				false
			)
		
			a += GA
	
	# Cutters 1
	var cutter_speed := 16.0
	if t % 360 == 30:
		SFX.play("cutter")
		var cut1 : Enemy = cutter.instantiate()
		var cut2 : Enemy = cutter.instantiate()
		var cut3 : Enemy = cutter.instantiate()
		var cut4 : Enemy = cutter.instantiate()
		
		cut1.position = position
		cut2.position = position
		cut3.position = position
		cut4.position = position
		
		cut1.velocity = Vector2(0.0, cutter_speed)
		cut2.velocity = Vector2(0.0, cutter_speed)
		cut3.velocity = Vector2(0.0, -cutter_speed)
		cut4.velocity = Vector2(0.0, -cutter_speed)
		
		cut1.lifespan = 60
		cut2.lifespan = 60
		cut3.lifespan = 60
		cut4.lifespan = 60
		
		cut1.wvel = -TAU / 60
		cut2.wvel = TAU / 60
		cut3.wvel = -TAU / 60
		cut4.wvel = TAU / 60
		
		cut1.spin = -0.5
		cut2.spin = 0.5
		cut3.spin = -0.5
		cut4.spin = 0.5
		
		get_parent().add_child(cut1)
		get_parent().add_child(cut2)
		get_parent().add_child(cut3)
		get_parent().add_child(cut4)

	# Cutters 2
	if t % 360 == 150:
		SFX.play("cutter")
		var cut1 : Enemy = cutter.instantiate()
		var cut2 : Enemy = cutter.instantiate()
		var cut3 : Enemy = cutter.instantiate()
		var cut4 : Enemy = cutter.instantiate()
		
		cut1.position = position
		cut2.position = position
		cut3.position = position
		cut4.position = position
		
		cut1.velocity = Vector2(cutter_speed, 0.0)
		cut2.velocity = Vector2(cutter_speed, 0.0)
		cut3.velocity = Vector2(-cutter_speed, 0.0)
		cut4.velocity = Vector2(-cutter_speed, 0.0)
		
		cut1.lifespan = 60
		cut2.lifespan = 60
		cut3.lifespan = 60
		cut4.lifespan = 60
		
		cut1.wvel = -TAU / 60
		cut2.wvel = TAU / 60
		cut3.wvel = -TAU / 60
		cut4.wvel = TAU / 60
		
		cut1.spin = -0.5
		cut2.spin = 0.5
		cut3.spin = -0.5
		cut4.spin = 0.5
		
		get_parent().add_child(cut1)
		get_parent().add_child(cut2)
		get_parent().add_child(cut3)
		get_parent().add_child(cut4)
	
	# Cutters 3
	if t % 360 == 270:
		a2 = 0.0
		lr1 *= -1.0
	if t % 360 >= 270 and t % 360 < 300:
		if t % 5 == 0:
			SFX.play("cutter")
			for i in 2:
				var cut : Enemy = cutter.instantiate()
				cut.position = position
				cut.velocity = Vector2(cutter_speed, 0.0).rotated(a2 + i * TAU / 2.0)
				cut.lifespan = 60
				cut.wvel = -lr1 * TAU / 60
				cut.spin = -0.5
				get_parent().add_child(cut)
		a2 += lr1 * PI / 30.0 * 2.0

func wars(_time_scale: float) -> void:

	var bomb_speed : Array[float] = 		[15.0, 17.0, 18.0, 19.0, 21.0]
	var bomb_strength : Array[float] = 		[4.5, 5.0, 5.5, 6.0, 7.0]
	var bomb_travel_time : Array[float] =   [112.0, 100.0, 92.5, 90.0, 85.0]
	var bomb_bonus_time : Array[float] =    [30.0, 24.0, 18.0, 15.0, 12.0]
	var bomb_fire_rate : Array[int] = [40, 36, 33, 30, 24]

	if t == 0:
		a = PI * 0.2
	var angle : float
	if t < 120.0:
		a += PI * 0.3 / 120.0
		angle = a
	else:
		angle = position.angle_to_point(System.player.position)
	SFX.play("shoot1")
	bullet_timer += bullet_rates[difficulty]
	while bullet_timer >= 1.0:
		bullet_timer -= 1.0
		for i in 4:
			var pos := position + Vector2(randf()*200.0, 0.0).rotated(randf()*TAU)
			Bullets.create_bullet_a1(pos, randf_range(0.5, 1.0) * bullet_speeds[difficulty], angle + i * TAU / 4, bullet, false)
		
	if t % bomb_fire_rate[difficulty] == 15 and t >= 120:
		SFX.play("warning")
		var grenade : Enemy = bomb.instantiate()
		grenade.position = position
		var aim_position := Vector2(System.player.position.x, -1000.0)
		
		match bomb_cycle % 2:
			0:
				aim_position.x *= -1.0
			1:
				aim_position.x = 2000.0 - aim_position.x
		
		bomb_cycle += 1
		
		var direction := (aim_position - position)
		direction /= -direction.y * randf_range(0.9, 1.0)
		grenade.velocity = direction * bomb_speed[difficulty]
		grenade.acceleration = -direction * bomb_speed[difficulty] / bomb_travel_time[difficulty]
		grenade.explode_timer = bomb_travel_time[difficulty] + bomb_bonus_time[difficulty]
		grenade.spin_direction = sign(direction.x)
		grenade.strength = bomb_strength[difficulty]
		get_parent().add_child(grenade)
	
	if t % 240 == 0 and t > 0:
		random_walk(Vector2(300, 300), Vector2(700, 300), Vector2(150, 0), 60)

func weather(_time_scale: float) -> void:
	if t == 0:
		set_destination(Vector2(500, 200), 60)
	# Hail
	if (t % rain_rates[difficulty] == 0 and t > 120) or (t % (rain_rates[difficulty]*2) == 0 and t > 60) or (t % (rain_rates[difficulty]*3) == 0):
		SFX.play("shoot1")
		Bullets.create_bullet_a1(
			Vector2(randf_range(-100, 1000), -100),
			randf_range(2.0/3.0, 1.0) * rain_speeds[difficulty],
			randf_range(PI * 0.225, PI * 0.275),
			rain[randi()%6],
			false
		)
		Bullets.create_bullet_a1(
			Vector2(-100, randf_range(-100, 1000)),
			randf_range(2.0/3.0, 1.0) * rain_speeds[difficulty],
			randf_range(PI * 0.225, PI * 0.275),
			rain[randi()%6],
			false
		)

	# Flood
	var height : float = clamp(750.0, 1100.0 - t, 1000.0)
	# Under water
	for i in 10:
		var prop := randf()
		var y : float = lerp(height, 1000.0, prop)
		var speed = 6.0 + 6.0 * (1.0 - prop)
		var b = Bullets.create_bullet_a1(
			Vector2(1100, y),
			speed,
			PI * 0.925,
			water[randi()%5],
			false
		)
		Bullets.set_rotation(b, randf()*TAU)
	# Over water
	for i in 5:
		var prop := randf()
		var y : float = lerp(height - 50.0, height + 50.0, prop)
		var speed = 12.0 + 4.0 * (1.0 - prop)
		Bullets.create_bullet_a1(
			Vector2(1100, y),
			speed,
			PI * 0.925,
			water_top,
			true
		)
	
	# Stars
	if t % 60 == 0 and t >= 300:
		# Pickupable stars
		var l_star : Enemy = impact_star.instantiate()
		var r_star : Enemy = impact_star.instantiate()
		l_star.position = star_spawn_position + Vector2(-96, -64).rotated(-PI * 0.075) + Vector2(0, -48)
		r_star.position = star_spawn_position + Vector2(96, -64).rotated(-PI * 0.075) + Vector2(0, -48)
		l_star.lifespan = 90
		r_star.lifespan = 90
		get_parent().add_child(l_star)
		get_parent().add_child(r_star)
	
	# Lightning
	if t % 60 == 0 and t >= 240:
		SFX.play("charge_short")
		if t >= 300:
			SFX.play("explode")
		var x : float = randf_range(0, 1000.0)
		var y := 0.0
		var is_first_strike := true
		var is_last_strike := false
		while not is_last_strike:
			var data := chain_lightning_data
			if is_first_strike:
				is_first_strike = false
				data = lightning_data
			var next_x : float = clamp(x + randf_range(-150, 150), 0, 1000)
			var next_y := y + randf_range(100, 250)
			var the_floor := shore_height(next_x, height) - 16
			if next_y > the_floor:
				is_last_strike = true
				next_y = the_floor
				next_x = x
			var dir := Vector2(next_x - x, next_y - y)
			Bullets.create_straight_laser(
				Vector2(x, y),
				dir.angle(),
				dir.length(),
				128,
				0.1,
				0.1, 
				60,
				30,
				data,
				true
			)
			x = next_x
			y = next_y
		star_spawn_position = Vector2(x, y)
			
	# Movement
	if t % 240 == 30 and t > 30:
		var target : float = System.player.position.x + randf_range(-50, 50)
		if target - position.x > 200:
			target = position.x + 200
		elif target - position.x < -200:
			target = position.x - 200
			
		set_destination(
			Vector2(clamp(target, 350, 650), 200),
			60
		)
	
	# Difficulty spike
	if not difficulty_raised and health <= max_health / 3:
		difficulty_raised = true
		@warning_ignore("int_as_enum_without_cast")
		difficulty += 2
		var kog : Enemy = kogasa.instantiate()
		kog.position = Vector2(-200, 500)
		get_parent().add_child(kog)


func shore_height(x: float, right_height: float) -> float:
	return tan(PI * 0.925) * (x - 1000.0) + right_height

func _pre_death():
	star_damage_multiplier = 1.0
	if phase == 0 and next_attack + 1 >= attack_name_list.size():
		difficulty = System.difficulty # so janky
		System.ui.slide_in_top_bar(true)
		fucking_shit_cunt_t = -1
		attack_timer = 60 * 60
		System.ui.set_timer(60)
		System.ui.fill_healthbar()
		phase = 1
		next_attack = -1
		current_attack = -2
		t = -1
		t_float = -1.0
		attack_type_list = second_attack_type_list
		attack_name_list = second_attack_name_list
		System.ui.update_boss_data(boss_name, attack_type_list, attack_name_list)
		System.in_dialogue = true
		fucking_jank_frame = true
		health = max_health
		Bullets.clear_bullets(Vector2(500, 500), 100000, true)
	elif phase == 1 and next_attack + 1 >= 3:
		$AnimationPlayer.play("splti")
		death_timer = 180.0
		phase = 2
		next_attack = -1
		current_attack = -2
		t = -1000
		t_float = -1000.0
		System.fade_quit = true
		health = max_health

func _post_death():
	in_timeout = false
	modulate = Color.WHITE
	if phase == 0 and next_attack == 2 and not debug_low_health:
		max_health = 1200
	if phase == 1 and not debug_low_health:
		if next_attack == 0:
			max_health = 1200
		if next_attack == 1:
			max_health = 60 * 36
			attack_timer = 60 * 36
			invincibility_timer = 60 * 36
			in_timeout = true
			modulate = Color(0.25, 0.25, 0.25, 1.0)
		if next_attack == 2:
			max_health = 3600
	System.clear_enemies = true
	
