extends Boss

var frog_grenades := preload("res://prefab/boss/frog_grenade.tscn")

var a := 0.0
var lr := 1.0

var a2 := 0.0

var barrage_rate : Array[int] = 		[180,  170,  160,  150,  120]
var barrage_duration : Array[int] = 	[90,   72,   60,   55,   40]
var fire_burst : Array[int] = 			[9,    9,    9,    9,    9]
var frog_speed : Array[float] = 		[15.0, 17.0, 18.0, 19.0, 21.0]
var blue_fire_rate : Array[int] = 		[9,    6,    4,    3,    2]
var blue_fire_density : Array[int] = 	[9,   11,   12,    14,   14]
var blue_speed: Array[float] = 			[2.5,  3.75,  4.5,  5.25,  5.4]
var blue_length : Array[float] = 		[1.0, 1.2, 1.5,   1.6,  1.6]
var frog_strength : Array[float] = 		[6.0, 9.0, 10.0,  12.0, 14.0]
var frog_travel_time : Array[float] =   [130.0, 100.0, 95.0, 90.0, 80.0]
var frog_bonus_time : Array[float] =    [30.0, 24.0, 18.0, 15.0, 12.0]

var blue_ball : PackedFloat64Array

func _post_ready() -> void:
	blue_ball = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.BLUE)
	

func _pre_process(_time_scale: float) -> void:
	if t >= 0:
		# Blue walls
		if t % blue_fire_rate[difficulty] == 0:
			SFX.play("shoot1")
			a2 = TAU * randf_range(-0.2, 0.5 + 0.2)
			
			var parity := 1.0 if randf()>0.5 else -1.0
			var pos := position + Vector2(randf()*100.0, 0.0).rotated(randf()*TAU) * Vector2(2.0, 1.0)
			for i in blue_fire_density[difficulty]:
				var angle := a2 + parity * i * 0.3 / blue_fire_density[difficulty]
				var speed := blue_speed[difficulty] + i * blue_length[difficulty] / blue_fire_density[difficulty]
				
				Bullets.create_bullet_a1(pos, speed, angle, blue_ball, false)
				
			
		# Frog Grenades
		if t >= barrage_rate[difficulty]:
			if t % barrage_rate[difficulty] == 0:
				a = PI * (0.5 + lr * 0.6) + randf_range(-0.1, 0.1)
				lr *= -1.0
			@warning_ignore("integer_division")
			if t % barrage_rate[difficulty] < barrage_duration[difficulty] and t % (barrage_duration[difficulty] / fire_burst[difficulty]) == 0:
				SFX.play("warning")
				var grenade : Enemy = frog_grenades.instantiate()
				grenade.position = position
				var direction := Vector2(1, 0).rotated(a)
				grenade.velocity = direction * frog_speed[difficulty]
				grenade.acceleration = -direction * frog_speed[difficulty] / frog_travel_time[difficulty]
				grenade.explode_timer = frog_travel_time[difficulty] + frog_bonus_time[difficulty]
				grenade.spin_direction = sign(direction.x)
				grenade.strength = frog_strength[difficulty]
				get_parent().add_child(grenade)
				a -= lr * (TAU * (0.5 - 0.2)) / (fire_burst[difficulty] - 1)
		# Movemenmt
		if t % barrage_rate[difficulty] == barrage_duration[difficulty]:
			random_walk(Vector2(300, 300), Vector2(700, 300), Vector2(150, 0), 120)
