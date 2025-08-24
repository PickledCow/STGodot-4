extends Boss


@export var second_attack_type_list : Array[System.ATTACK_TYPE] = []
@export var second_attack_name_list : Array[String] = []

var phase := 0

var knife : PackedFloat64Array
var bullet : PackedFloat64Array
var rain : Array[PackedFloat64Array]
var water : Array[PackedFloat64Array]
var water_top : PackedFloat64Array

var lightning_data: PackedFloat64Array
var chain_lightning_data: PackedFloat64Array

var cutter := preload("res://prefab/boss/cutter.tscn")
var bomb := preload("res://prefab/boss/real_bomb.tscn")
var impact_star := preload("res://prefab/boss/marisa_star.tscn")
var kogasa := preload("res://prefab/boss/kogasa_friend.tscn")

var knife_speeds : Array[float] = [5.0, 6.0, 8.0, 9.0, 10.0]
var knife_densities : Array[int] = [2, 1, 4, 2, 3]
var knife_rates : Array[int] = [3, 1, 3, 1, 1]
var knife_sound_rate : Array[int] = [2, 2, 1, 1, 1]


var bullet_timer := 0.0
var bullet_speeds : Array[float] = [6.0, 7.0, 8.0, 12.0, 14.0]
var bullet_rates : Array[float] = [0.2, 0.3, 0.5, 0.75, 1.0]

var bomb_speed : Array[float] = 		[15.0, 17.0, 18.0, 19.0, 21.0]
var bomb_strength : Array[float] = 		[5.0, 8.0, 10.0,  12.0, 14.0]
var bomb_travel_time : Array[float] =   [120.0, 100.0, 95.0, 90.0, 85.0]
var bomb_bonus_time : Array[float] =    [30.0, 24.0, 18.0, 15.0, 12.0]
var bomb_fire_rate : Array[int] = [40, 36, 33, 30, 24]


var rain_rates : Array[int] = [9, 6, 4, 3, 2, 1, 1]
var rain_speeds : Array[float] = [6.0, 8.0, 9.0, 10.0, 12.0, 15.0, 18.0]

var GA := PI * (3 - sqrt(5))
var a := 0.0
var a2 := 0.0

var bomb_cycle := 0

var lr1 := 1.0
var star_spawn_position : Vector2

var difficulty_raised := false

var debug_low_health := true

func _pre_ready() -> void:
	if debug_low_health:
		max_health = 1

func _post_ready() -> void:
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
	if t == 0:
		System.clear_enemies = false
	if t >= 0:
		#weather(time_scale)
		#return
		#@warning_ignore("unreachable_code")
		match current_attack:
			0:
				cuts(time_scale)
			1:
				wars(time_scale)
			2:
				weather(time_scale)


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
		
		match bomb_cycle % 4:
			1:
				aim_position.x *= -1.0
			3:
				aim_position.x = 2000.0 - aim_position.x
		
		bomb_cycle += 1
		
		var direction := (aim_position - position)
		direction /= -direction.y * randf_range(0.9, 1.0)
		grenade.velocity = direction * bomb_speed[difficulty]
		grenade.acceleration = -direction * bomb_speed[difficulty] / bomb_travel_time[difficulty]
		grenade.explode_timer = bomb_travel_time[difficulty] + bomb_bonus_time[difficulty]
		grenade.spin_direction = sign(direction.x)
		grenade.strength = 6.0
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
	if phase == 0 and next_attack + 1 >= attack_name_list.size():
		phase = 1
		attack_type_list = second_attack_type_list
		attack_name_list = second_attack_name_list
		System.ui.update_boss_data(boss_name, attack_type_list, attack_name_list)
		

func _post_death():
	if next_attack == 2 and not debug_low_health:
		max_health = 1600
	System.clear_enemies = true
	
