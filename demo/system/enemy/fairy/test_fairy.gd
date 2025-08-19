extends Enemy

var data
var data2
var item_data

func _post_ready() -> void:
	data = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.BLUE)
	data2 = System.get_bullet_data(BulletConstructor.BULLET_TYPE.BALL, BulletConstructor.COLORS.RED)
	item_data = System.get_item_data(0)

func _post_process(_time_scale: float) -> void:
	return
	#if t % 30 == 0 and t < 120:
		#var a := position.angle_to_point(System.player.position) + randf_range(-0.1, 0.1) * 0.0
		#Bullets.create_bullet_a1(position,  randf_range(5.0, 10.0), a, data, false)
		#SFX.play("shoot1")

func _custom_on_death() -> void:
	pass
	#if despawned:
		#return
	#for i in 5:
		#Bullets.create_item(position, 10.0, randf_range(0, TAU), 120.0, item_data, false)
	#var dist = (position - System.player.position).length_squared()
	#if dist >= 200 * 200:
		#var a := position.angle_to_point(System.player.position) + randf()*TAU * 0.0
		#for i in 5:
			#Bullets.create_bullet_a1(position, 6.0, a + i / 5.0 * TAU, data2, false)
		#
