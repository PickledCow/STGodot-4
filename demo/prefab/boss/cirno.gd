extends Boss

var snowmen := preload("res://prefab/boss/snowman.tscn")

var ice : PackedFloat64Array
var ice2 : PackedFloat64Array

var hand_offset := Vector2(-32, -128)

var ice_rate : Array[int] = [12, 9, 7, 6, 3]
var ice_speeds : Array[float] = [5.0, 6.0, 7.0, 8.0, 8.5]
var ice_sway : Array[float] = [24.0, 16.0, 14.0, 12.0, 12.0]
var snowman_densities : Array[float] = [45.0, 52.0, 60.0, 72.0, 90.0]
var snowman_spawn_rate : Array[int] = [150, 140, 130, 120, 95]
var snowman_speeds : Array[float] = [2.25, 2.5, 2.75, 3.0, 3.25]

func _post_ready() -> void:
	ice = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE_LARGE, BulletConstructor.COLORS_LARGE.CYAN)
	ice2 = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE_LARGE, BulletConstructor.COLORS_LARGE.BLUE)

func shoot_ice(angle: float, data: PackedFloat64Array):
	var sway := tan(angle)
	var thold : float = 0.5 * abs(sway)
	
	var pos := randf()
	
	if sway >= 0.0:
		var x := randf_range(0.0, 1048.0) if pos < 1.0 - thold else 1048.0
		var y := randf_range(-48.0, 1000.0) if pos > 1.0 - thold else -48.0
		Bullets.create_bullet_a1(Vector2(x, y), randf_range(0.5, 1.0) * ice_speeds[difficulty], PI * 0.5 + angle, data, false)
	else:
		var x := randf_range(-48.0, 1000.0) if pos > thold else -48.0
		var y := randf_range(-48.0, 1000.0) if pos < thold else -48.0
		Bullets.create_bullet_a1(Vector2(x, y), randf_range(0.5, 1.0) * ice_speeds[difficulty], PI * 0.5 + angle, data, false)
	


func _post_process(_time_scale: float) -> void:
	if t >= 0:
		#Bullets.create_bullet_a1(position, 5, PI * 0.5, ice, false)
		if t % ice_rate[difficulty] == 0:
			var angle := cos(TAU * t / 900.0) * TAU / ice_sway[difficulty]
			shoot_ice(angle, ice)
			Bullets.create_bullet_a1(position + hand_offset, randf_range(7.0, 10.0), PI * randf_range(-0.6, -0.4), ice, false)
		@warning_ignore("integer_division")
		if t % ice_rate[difficulty] == ice_rate[difficulty] / 2:
			var angle := sin(TAU * t / 900.0) * TAU / ice_sway[difficulty]
			shoot_ice(angle, ice2)
			Bullets.create_bullet_a1(position + hand_offset, randf_range(7.0, 10.0), PI * randf_range(-0.6, -0.4), ice2, false)
		
		if t % ice_rate[difficulty] == 0:
			SFX.play("shoot1")
		
		if t % (snowman_spawn_rate[difficulty] * 2) == snowman_spawn_rate[difficulty]:
			#SFX.play("warning")
			
			
			var srl : float = 1.0 if randf() > 0.5 else -1.0
			
			var snowman : Enemy = snowmen.instantiate()
			snowman.position = Vector2(position.x + srl * randf_range(100, 150), -150)
			snowman.velocity = Vector2(0.0, snowman_speeds[difficulty])
			snowman.density = snowman_densities[difficulty]
			@warning_ignore("integer_division")
			snowman.fire_rate = snowman_spawn_rate[difficulty] / 2
			if health <= 500:
				@warning_ignore("integer_division")
				snowman.fire_rate = snowman_spawn_rate[difficulty] / 3
				@warning_ignore("integer_division")
				snowman.fire_time = snowman_spawn_rate[difficulty] / 6
			get_parent().add_child(snowman)
		
		if t > 0 and t % 600 == 0:
			var min_x : float = max(350, position.x - 150)
			var max_x : float = min(750, position.x + 150)
			set_destination(Vector2(randf_range(min_x, max_x), 300), 60)
		
