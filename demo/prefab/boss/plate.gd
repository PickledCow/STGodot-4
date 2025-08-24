extends Enemy

var decay_factor := 0.8
var density := 6

var lr := 1.0

var shards : PackedFloat64Array
var dark_shards : PackedFloat64Array
var large_shard : PackedFloat64Array

var launch_direction := Vector2.ZERO

var skip_shards := false

func _post_ready() -> void:
	shards = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE, BulletConstructor.COLORS.WHITE)
	dark_shards = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE, BulletConstructor.COLORS.BLUE)
	large_shard = System.get_bullet_data(BulletConstructor.BULLET_TYPE.ICE_LARGE, BulletConstructor.COLORS_LARGE.GREY)

func _post_process(_time_scale: float) -> void:
	var hit_wall := false
	rotation += 0.075 * lr
	if position.x < -32:
		position.x = 0.0
		hit_wall = true
		launch_direction = Vector2.RIGHT
	if position.x > 1032.0:
		position.x = 1000.0
		velocity.x *= -decay_factor
		hit_wall = true
		launch_direction = Vector2.LEFT
	if position.y < -32:
		launch_direction = Vector2.DOWN
		position.y = 0.0
		velocity.y *= -decay_factor
		hit_wall = true
	if hit_wall:
		how_i_died = DEATH_TYPE.NORMAL
		skip_shards = false
		_on_death()

func _post_death():
	if (how_i_died != DEATH_TYPE.DESPAWNED and how_i_died != DEATH_TYPE.SUCKED) and not skip_shards and position.y < 1000.0:
		SFX.play("warning")
		Bullets.create_bullet_b1(
			position,
			(launch_direction * randf_range(0.5, 2.0)).rotated(randf_range(-0.5, 0.5)) + Vector2(randf_range(-0.5, 0.5), randf_range(-4.0, -2.0)),
			Vector2(0.0, 0.02),
			Vector2(0.0, 10.0),
			true,
			large_shard,
			false
		)
		for i in density:
			var type := shards if randf() > 0.4 else dark_shards
			# create_bullet_b1(position: Vector2, velocity: Vector2, accel: Vector2, max_velocity: Vector2, rotation_follows_movement: bool, shot_data: PackedFloat64Array, glow: bool)

			Bullets.create_bullet_b1(
				position,
				(launch_direction * randf_range(0.5, 2.0)).rotated(randf_range(-0.5, 0.5)) + Vector2(randf_range(-0.5, 0.5), randf_range(-4.0, -2.0)),
				Vector2(0.0, 0.02),
				Vector2(0.0, 10.0),
				true,
				type,
				false
			)
