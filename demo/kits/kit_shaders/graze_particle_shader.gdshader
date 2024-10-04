shader_type canvas_item;
render_mode blend_add;

varying flat vec4 modulate;

float curve(float x) {
	return min(1.0, 3.0 - 3.0 * x);
}

void vertex() {
	modulate = COLOR;
}

void fragment() {
	vec4 tex = texture(TEXTURE, UV);
	tex.a = curve(modulate.a);
	COLOR = tex;
}