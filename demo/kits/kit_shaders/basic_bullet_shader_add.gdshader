shader_type canvas_item;
render_mode blend_add;
// advert your eyes pls

// speed at which the animated bullets should change sprites at
uniform float animation_speed = 8.0;
const float FACTOR = 2.61799387799;

varying flat vec4 modulate;

float fade(float x) {
	return 2.0 * sin(FACTOR * sqrt(min(x, 1.0)));
}

void vertex() {
	modulate = COLOR;
	VERTEX.y += floor(abs(modulate.b)) / floor(modulate.g);
	VERTEX *= fade(1.0 - fract(max(0.0, modulate.b)));
}

void fragment() {
	vec2 texSize = vec2(textureSize(TEXTURE, 0));
	vec2 texPixel = vec2(1.0, 1.0 / texSize.y);

	vec2 position = vec2(fract(modulate.r), floor(modulate.r));
	vec2 size = vec2(fract(modulate.g),floor(modulate.g));
	vec2 uv = texPixel * position + texPixel * size * UV;

	float frame_count = max(1.0, floor(modulate.a));
	float frame = mod(floor(animation_speed * TIME + fract(modulate.a) * frame_count), frame_count);
	uv.x += size.x * frame;

	vec4 tex = texture(TEXTURE, uv);

	float alpha = 1.0 - fract(abs(modulate.b));
	tex.a *= alpha;

	COLOR = tex;
}
