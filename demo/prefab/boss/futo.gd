extends Boss

var plates := preload("res://prefab/boss/plate.tscn")

var a := 0.0
var a2 := PI * 0.5
var a3 := PI * 0.5
var lr := 1.0
var lr2 := 1.0

var arrow_a := 0.0
var arrow_a2 := 0.0

var red_fire : PackedFloat64Array
var orange_fire : PackedFloat64Array
var arrow : PackedFloat64Array

var rates := [4, 3, 2, 1]

var shard_density : Array[int] = [3, 4, 6, 8, 10]
var plate_rate : Array[int] = [8, 6, 5, 4, 3]
var plate_speed : Array[float] = [4.5, 5.0, 5.5, 6.0, 6.5]
var plate_init_speed : Array[float] = [16.0, 16.0, 16.0, 16.0, 16.0]
var plate_accel : Array[float] = [0.5, 0.5, 0.5, 0.5, 0.5]
var arrow_density : Array[int] = [60, 85, 95, 120, 150]
var arrow_accel : Array[float] = [0.002, 0.002, 0.0025, 0.003, 0.003]

func _post_ready() -> void:
	red_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.RED)
	orange_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.ORANGE)
	arrow = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROW, BulletConstructor.COLORS_LARGE.BLUE)

	#difficulty = System.DIFFICULTY.OVERDRIVE

func _pre_process(_time_scale: float) -> void:
	
	
	if t > 0:
		if t % 240 == 0 and t > 0:
			var min_x : float = max(300, position.x - 200)
			var max_x : float = min(700, position.x + 200)
			set_destination(Vector2(randf_range(min_x, max_x), 300), 60)
			
		# Arrows
		if t < 120 and t % 12 == 0:
			arrow_a2 += arrow_accel[difficulty]
			arrow_a += arrow_a2
			SFX.play("shoot1")
			for i in arrow_density[difficulty]:
				var ang := arrow_a + i * TAU / arrow_density[difficulty]
				Bullets.create_bullet_a2(position, 12.0, ang, -0.15, 3.0, 0.0, arrow, false)
			
		# Plates
		if t % 240 == 120:
			a = PI * 0.5 + PI * 0.6 * lr + PI
			lr *= -1.0
		if t % 240 < 210 and t % 240 >= 120 and t % plate_rate[difficulty] == 0:
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
		if t % 240 < 210 and t % 240 >= 120:
			a += lr * TAU / 90.0 * 1.2
	
