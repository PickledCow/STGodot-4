extends Boss

var plates := preload("res://prefab/boss/plate.tscn")

var a := 0.0
var a2 := PI * 0.5
var a3 := PI * 0.5
var lr := 1.0
var lr2 := 1.0

var red_fire : PackedFloat64Array
var orange_fire : PackedFloat64Array

var rates := [4, 3, 2, 1]

var shard_density : Array[int] = [3, 4, 6, 8, 10]
var plate_rate : Array[int] = [8, 6, 5, 4, 3]
var plate_speed : Array[float] = [4.5, 5.0, 5.5, 6.0, 6.5]
var plate_init_speed : Array[float] = [16.0, 16.0, 16.0, 16.0, 16.0]
var plate_accel : Array[float] = [0.5, 0.5, 0.5, 0.5, 0.5]

func _post_ready() -> void:
	red_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.RED)
	orange_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.ORANGE)
	#difficulty = System.DIFFICULTY.OVERDRIVE

func _pre_process(_time_scale: float) -> void:
	if t > 120:
		if t % 240 == 120:
			var min_x : float = max(300, position.x - 200)
			var max_x : float = min(700, position.x + 200)
			set_destination(Vector2(randf_range(min_x, max_x), 300), 60)
	
	# Plates
	if t > 0:
		if t % 240 == 0:
			a = PI * 0.5 + PI * 0.6 * lr + PI
			lr *= -1.0
		if t % 240 < 90 and t % plate_rate[difficulty] == 0:
			#SFX.play("shoot1")
			var plate : Enemy = plates.instantiate()
			var rng := randf_range(-0.1, 0.1) * 0.0
			plate.position = position + Vector2(32, 0).rotated(a + rng)
			plate.velocity = Vector2(-plate_init_speed[difficulty], 0.0).rotated(a + rng)
			plate.acceleration = Vector2(plate_accel[difficulty], 0.0).rotated(a + rng)
			plate.max_velocity = Vector2(plate_speed[difficulty], 0.0).rotated(a + rng)
			plate.apply_max_velocity = true
			plate.density = shard_density[difficulty]
			plate.lr = lr
			get_parent().add_child(plate)
			SFX.play("shoot1")
		if t % 240 < 90:
			a += lr * TAU / 90.0 * 1.2
	
	# Fire
	if t % 4 == 4:
		a2 += 0.1 * 1.25
		a3 -= 0.1 * 1.25
		for i in 4:
			var dev := TAU * i / 4.0
			Bullets.create_bullet_a1(position + Vector2(96, 0).rotated(a2 + dev), 5.0, a2 + dev, red_fire, true)
		for i in 6:
			var dev := TAU * i / 6.0
			Bullets.create_bullet_a1(position + Vector2(96, 0).rotated(a3 + dev), 5.0, a3 + dev, orange_fire, true)
			#for i in 2:
				#var f := randf_range(0.5, 1.0)
				#var ang := PI * 0.5 - lr2 * PI * 0.5 + randf_range(-1, 1) * PI * 0.5
				#var b = Bullets.create_bullet_a1(position, 5.0 * f, ang, red_fire if lr2 > 0.0 else orange_fire, true)
				#Bullets.set_wvel(b, lr2 * 0.005 * f)
				#lr2 *= -1.0
	#if t % 2 == 0:
		#SFX.play("shoot1")
