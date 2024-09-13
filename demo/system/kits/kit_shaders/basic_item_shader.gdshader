shader_type canvas_item;
// advert your eyes pls

// speed at which the animated bullets should change sprites at
uniform float animation_speed = 8.0;

varying flat vec4 modulate;

void vertex() {
	modulate = COLOR;
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
	uv.y += size.y * texPixel.y * modulate.b;
	
	vec4 tex = texture(TEXTURE, uv);
	
	COLOR = tex;
}
