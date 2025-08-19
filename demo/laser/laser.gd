extends Path2D

@export var texture : Texture2D

const SPEED := 0.04
const CSPEED := 0.1
const CHAIN := 16
const GAP := 6
const SPRITE_COUNT := 2048

var _t := 0.0
var _c := 0.0


func _get_rect(p: Vector2, s: float) -> Rect2:
	return Rect2(p - texture.get_size() * s * 0.5, texture.get_size() * s)


func _physics_process(delta: float) -> void:
	_t = wrapf(_t + SPEED / curve.get_baked_length() * delta, 0.0, 1.0)
	_c = wrapf(_c + CSPEED * delta, 0.0, 1.0)
	queue_redraw()


func _draw() -> void:
	var len := curve.get_baked_length()
	var t := _t * len

	for i in SPRITE_COUNT:
		var j := maxi((i % CHAIN) - GAP, 0)
		if j == 0:
			continue
		var k := smoothstep(1.0, 0.0, float(j) / CHAIN)
		var f := wrapf(t + float(i)/SPRITE_COUNT, 0.0, 1.0)
		var pos := curve.sample_baked(f * len, true)
		draw_texture_rect(texture, _get_rect(pos, 3.0-k), false, Color.from_hsv(_c + f, 1.0, 0.5))

	for i in SPRITE_COUNT * 0:
		var j := maxi((i % CHAIN) - GAP, 0)
		if j == 0:
			continue
		var k := smoothstep(1.0, 0.0, float(j) / CHAIN)
		var f := wrapf(t + float(i)/SPRITE_COUNT, 0.0, 1.0)
		var pos := curve.sample_baked(f * len, true)
		draw_texture_rect(texture, _get_rect(pos, 2.0-k), false, Color.from_hsv(_c + f, k, 1.0))
