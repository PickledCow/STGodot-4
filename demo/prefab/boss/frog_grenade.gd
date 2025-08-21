extends Enemy

var bounce_count := 2
var decay_factor := 1.0

var spin_direction := 1.0

var explode_timer := 60
var green_bullet : PackedFloat64Array
var white_bullet : PackedFloat64Array
var eye_bullet : PackedFloat64Array

var chin_density := 20
var scalp_density := 4
var mouth_density := 10
var eye_density := 10

var strength := 12.0

func _post_ready() -> void:
	green_bullet = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.GREEN)
	white_bullet = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.GREY)
	eye_bullet = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ORB, BulletConstructor.COLORS_LARGE.RED)
	
	t = -30
	t_float = -30.0

func create_frog(pos: Vector2, speed: float, duration: float, angle: float):
	var decel := -speed / (duration + 24.0)
	# ""Chin""
	for i in chin_density:
		var p := Vector2(
					sin(i * TAU / chin_density * 0.34), 
			-0.75 * cos(i * TAU / chin_density * 0.34) - 0.2
		)
		var a := p.angle() + PI
		var s := p.length()
		@warning_ignore("confusable_local_declaration")
		var b1 = Bullets.create_bullet_a2(pos, s * speed, a + angle, s * decel, 0.0, 0.0, green_bullet, true)
		Bullets.set_lifespan(b1, duration)
		@warning_ignore("confusable_local_declaration")
		var b2 = Bullets.create_bullet_a2(pos, s * speed, PI - a + angle, s * decel, 0.0, 0.0, green_bullet, true)
		Bullets.set_lifespan(b2, duration)
	# Scalp
	for i in scalp_density:
		var p := Vector2(
				   sin(i * TAU / scalp_density * 0.05), 
			0.75 * cos(i * TAU / scalp_density * 0.05) - 0.2
		)
		var a := p.angle() + PI
		var s := p.length()
		@warning_ignore("confusable_local_declaration")
		var b1 = Bullets.create_bullet_a2(pos, s * speed, a + angle, s * decel, 0.0, 0.0, green_bullet, true)
		@warning_ignore("confusable_local_declaration")
		var b2 = Bullets.create_bullet_a2(pos, s * speed, PI - a + angle, s * decel, 0.0, 0.0, green_bullet, true)
		Bullets.set_lifespan(b1, duration)
		Bullets.set_lifespan(b2, duration)
	# Eye outline
	for i in eye_density + 1:
		var p := Vector2(
			0.3 * cos(i * TAU / eye_density * 0.55 + 0.4) - 0.6, 
			0.3 * sin(i * TAU / eye_density * 0.55 + 0.4) + 0.6 - 0.2
		)
		var a := p.angle() + PI
		var s := p.length()
		@warning_ignore("confusable_local_declaration")
		var b1 = Bullets.create_bullet_a2(pos, s * speed, a + angle, s * decel, 0.0, 0.0, green_bullet, true)
		Bullets.set_lifespan(b1, duration)
		@warning_ignore("confusable_local_declaration")
		var b2 = Bullets.create_bullet_a2(pos, s * speed, PI - a + angle, s * decel, 0.0, 0.0, green_bullet, true)
		Bullets.set_lifespan(b2, duration)
	# Mouth
	for i in mouth_density:
		var p := Vector2(
			0.92 * i / mouth_density, 
			0.15 * cos(i * TAU / mouth_density * 0.66) - 0.2 - 0.2
		)
		var a := p.angle() + PI
		var s := p.length()
		@warning_ignore("confusable_local_declaration")
		var b1 = Bullets.create_bullet_a2(pos, s * speed, a + angle, s * decel, 0.0, 0.0, white_bullet, true)
		Bullets.set_lifespan(b1, duration)
		@warning_ignore("confusable_local_declaration")
		var b2 = Bullets.create_bullet_a2(pos, s * speed, PI - a + angle, s * decel, 0.0, 0.0, white_bullet, true)
		Bullets.set_lifespan(b2, duration)
	# Eyes
	var ep := Vector2(-0.6, 0.6 - 0.2)
	var ea := ep.angle() + PI
	var es := ep.length()
	var b1 = Bullets.create_bullet_a2(pos, es * speed, ea + angle, es * decel, 0.0, 0.0, eye_bullet, true)
	var b2 = Bullets.create_bullet_a2(pos, es * speed, PI - ea + angle, es * decel, 0.0, 0.0, eye_bullet, true)
	Bullets.set_lifespan(b1, duration)
	Bullets.set_lifespan(b2, duration)
	

func _post_process(_time_scale: float) -> void:
	if bounce_count > 0:
		if position.x < 0.0:
			position.x *= -1.0
			bounce_count -= 1
			velocity.x *= -decay_factor
			acceleration.x *= -1.0
		if position.x > 1000.0:
			position.x = 2000.0 - position.x
			bounce_count -= 1
			velocity.x *= -decay_factor
			acceleration.x *= -1.0
		if position.y < 0.0:
			position.y *= -1.0
			bounce_count -= 1
			velocity.y *= -decay_factor
			acceleration.y *= -1.0
	
	if sign(velocity.x) == sign(acceleration.x):
		velocity.x = 0.0
		acceleration.x = 0.0
	if sign(velocity.y) == sign(acceleration.y):
		velocity.y = 0.0
		acceleration.y = 0.0 
	
	rotation += 0.05 * spin_direction
	
	explode_timer -= 1
	if explode_timer <= 0:
		SFX.play("explode")
		create_frog(position, strength, 45, randf()*TAU)
		_on_death()
