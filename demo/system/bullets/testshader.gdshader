shader_type canvas_item;
render_mode blend_add;

varying flat vec4 modulate;

void vertex() {
	modulate = COLOR;
}
void fragment() {
	vec2 uv = vec2((UV.x + floor(COLOR.a * 8.0)) / 8.0, UV.y);
	vec3 c = texture(TEXTURE, uv).rgb;
	c *= modulate.rgb;
	COLOR.rgb = c;
	COLOR.a = 1.0;
}
