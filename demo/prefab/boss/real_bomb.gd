extends Enemy

var bounce_count := 2
var decay_factor := 1.0

var spin_direction := 1.0

var explode_timer := 60
var red_fire : PackedFloat64Array
var orange_fire : PackedFloat64Array
var yellow_fire : PackedFloat64Array

var strength := 12.0

func _post_ready() -> void:
	red_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.RED)
	orange_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.ORANGE)
	yellow_fire = System.get_bullet_data(BulletConstructor.BULLET_TYPE.FIREBALL, BulletConstructor.COLORS_LARGE.YELLOW)


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
		
		for i in 30:
			var br = Bullets.create_bullet_a1(position, randf_range(0.5, 1.0) * strength, randf()*TAU, red_fire, true)
			var bo = Bullets.create_bullet_a1(position, randf_range(0.33, 0.75) * strength, randf()*TAU, orange_fire, true)
			var by = Bullets.create_bullet_a1(position, randf_range(0.0, 0.5) * strength, randf()*TAU, yellow_fire, true)
			Bullets.set_lifespan(br, 42)
			Bullets.set_lifespan(bo, 36)
			Bullets.set_lifespan(by, 30)
			
		_on_death()
