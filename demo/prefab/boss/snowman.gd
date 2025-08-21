extends Enemy

var snow : PackedFloat64Array

var density := 90.0
var fire_rate : int = 120
var fire_time : int = 35

func _post_ready() -> void:
	snow = System.get_bullet_data(BulletConstructor.BULLET_TYPE.MENTOS, BulletConstructor.COLORS_LARGE.GREY)

func _post_process(_time_scale: float) -> void:
	if t % fire_rate == fire_time and position.y < 800.0 and position.y > 80.0:
		SFX.play("warning")
		@warning_ignore("narrowing_conversion")
		var d : int = density * (1000.0 - position.y) / 1000.0
		var offset := TAU * randf()
		for i in d:
			var a := (TAU * i) / d + offset
			Bullets.create_bullet_a1(position, 4.0, a, snow, true)
