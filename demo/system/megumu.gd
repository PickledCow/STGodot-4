extends Boss

var bullet_enemy := preload("res://prefab/boss/megumu_bullet.tscn")

var bullets : Array[PackedFloat64Array] = []
var lasers : Array[PackedFloat64Array] = []
var arrowheads : Array[PackedFloat64Array] = []

var stars : Array[PackedFloat64Array] = []

var barrel_offset := Vector2(-120, -12)

var c := 0

var a := 0.0

var laser_pos : Array[Vector2]
var laser_angles : Array[float]

var density := 8*3
var fire_rate := 2
var fire_delay := 90
var fire_cycle := 240

var target : Vector2

var bullet_density : Array[int] = [6, 7, 8, 10, 12]
var bullet_spacing : Array[int] = [4, 6, 9, 12, 15]

var bullet_max : Array[float] = [8.0, 9.0, 10.0, 12.0, 15.0]
var bullet_min : Array[float] = [3.0, 2.5, 2.2, 2.0, 1.8]

var bullet_rates : Array[int] = [20, 12, 10, 8, 6]
var shrapnel_speeds : Array[float] = [1.5, 2.5, 4.0, 5.0, 5.5]

var spread_speed_min : Array[float] = [1.5, 1.25, 1.1, 1.0, 0.9]
var spread_speed_max : Array[float] = [3.0, 4.0, 4.5, 5.0, 5.5]

var collision_time : int = -1

var star_spawn_pos : Vector2

func _post_ready() -> void:
	stars.resize(8)
	
	stars[0] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.RED)
	stars[1] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.ORANGE)
	stars[2] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.YELLOW)
	stars[3] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.GREEN)
	stars[4] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.TEAL)
	stars[5] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.CYAN)
	stars[6] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.BLUE)
	stars[7] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.STAR, BulletConstructor.COLORS.PURPLE)
	
	bullets.resize(8)
	
	bullets[0] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.RED)
	bullets[1] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.ORANGE)
	bullets[2] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.YELLOW)
	bullets[3] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.GREEN)
	bullets[4] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.TEAL)
	bullets[5] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.CYAN)
	bullets[6] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.BLUE)
	bullets[7] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BULLET, BulletConstructor.COLORS.PURPLE)
		
	arrowheads.resize(8)
	
	arrowheads[0] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.RED)
	arrowheads[1] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.ORANGE)
	arrowheads[2] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.YELLOW)
	arrowheads[3] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.GREEN)
	arrowheads[4] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.TEAL)
	arrowheads[5] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.CYAN)
	arrowheads[6] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.BLUE)
	arrowheads[7] = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ARROWHEAD, BulletConstructor.COLORS.PURPLE)
	
	
	var laser_offsets : Array[float] = [2, 14, 13, 11, 10, 8, 6, 4]
	var spawn_offsets : Array[float] = [1, 7, 6, 5, 5, 4, 3, 2]
	
	lasers.resize(8)
	
	for i in 8:
		lasers[i] = PackedFloat64Array()
		lasers[i].resize(16)
		lasers[i][0] = 64*laser_offsets[i]
		lasers[i][1] = 0
		lasers[i][2] = 64
		lasers[i][3] = 64
		lasers[i][4] = 0.25
		lasers[i][5] = 1					# anim frame, 1 for no animation (integer)
		lasers[i][6] = 1
		lasers[i][7] = spawn_offsets[i] * 128
		lasers[i][8] = 832
		lasers[i][9] = 128
		lasers[i][10] = 128
		lasers[i][11] = 1
		lasers[i][12] = 1
		lasers[i][13] = 1
		lasers[i][14] = 0				# damage type
		lasers[i][15] = 0				# damage amount

	
	

func _pre_process(_time_scale: float) -> void:
	$Scope.position = target - position
	
	if t >= 0:
		if t % 180 <= 60:
			target = System.player.position
		
		if t % 180 == 0:
			$Scope.show()
			random_walk(Vector2(300, 150), Vector2(700, 200), Vector2(150, 50), 60)
			
		if t % 180 == 60:
			SFX.play("charge_short")
			
			var ang_raw : float = position.angle_to_point(target) - PI * 0.5
			for i in bullet_density[difficulty]:
				var pos : Vector2 = position + (Vector2(128, 0.0).rotated(i * PI / (bullet_density[difficulty] - 1)) * Vector2(2.0, 1.5)).rotated(ang_raw)
			
				var angle : float = pos.angle_to_point(target)
				Bullets.create_straight_laser(
					pos,
					angle, 
					1500.0,
					32.0,
					0.0,
					0.0, 
					60,
					15,
					lasers[c % 8],
					true
				)
			c += 1
		if t % 180 == 120:
			SFX.play("explode")
			System.shake_screen(10, 10)
			#SFX.play("laser")
			$Scope.hide()
			
			
			var ang_raw : float = position.angle_to_point(target) - PI * 0.5
			for i in bullet_density[difficulty]:
				var pos : Vector2 = position + (Vector2(128, 0.0).rotated(i * PI / (bullet_density[difficulty] - 1)) * Vector2(2.0, 1.5)).rotated(ang_raw)
			
				# Bullet trail
				var angle : float = pos.angle_to_point(target)
				for j in bullet_spacing[difficulty]:
					var speed : float = bullet_min[difficulty] + j * (bullet_max[difficulty] - bullet_min[difficulty]) / bullet_spacing[difficulty]
				
					Bullets.create_bullet_a1(
						pos,
						speed,
						angle,
						arrowheads[(c-1) % 8],
						false
					)
				
				# Edible bullet
				var bullet : Enemy = bullet_enemy.instantiate()
				bullet.position = pos
				bullet.velocity = Vector2(bullet_max[difficulty] + 1.0, 0).rotated(angle)
				bullet.rotation = angle
				get_parent().add_child(bullet)
				
			# Calculate collision time when the quarter bullets hit each other
			var shoot_pos : Vector2 = position + (Vector2(128, 0.0).rotated((bullet_density[difficulty] * 0.25) * PI / (bullet_density[difficulty] - 1)) * Vector2(2.0, 1.5)).rotated(ang_raw)
			var distance := (shoot_pos - target).length()
			var bullet_travel_time = distance / (bullet_max[difficulty] + 1.0)
			collision_time = t + int(bullet_travel_time)
			star_spawn_pos = target
				
		
		# Star shrapnel
		if t == collision_time and false:
			SFX.play("warning")
			collision_time = -1
			# Stars
			for i in 8:
				for j in 12:
					var b = Bullets.create_bullet_a1(
						star_spawn_pos,
						randf_range(0.2, 1.0) * shrapnel_speeds[difficulty],
						randf()*TAU,
						stars[i],
						false
					)
					Bullets.set_spin(b, 0.1 if randf() > 0.5 else -0.1)
					Bullets.set_lifespan(b, 30)
		
		# Spray
		if (t % 180 < 60 or t % 180 >= 120) and t % bullet_rates[difficulty] == 0:
			SFX.play("shoot1")
			var pos := position + barrel_offset
			for i in 8:
				var angle : float = pos.angle_to_point(System.player.position) + randf_range(-PI * 0.33, PI * 0.33)
				Bullets.create_bullet_a1(
					pos + Vector2(16.0, 0.0).rotated(angle),
					randf_range(spread_speed_min[difficulty], spread_speed_max[difficulty]),
					angle + randf_range(-0.1, 0.1)*PI,
					bullets[i],
					false
				)
