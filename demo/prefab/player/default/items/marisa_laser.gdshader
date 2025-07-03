shader_type canvas_item;
render_mode blend_add;

void vertex() {
	// Called for every vertex the material is visible on.
}

void fragment() {
	vec2 uv = UV;
	uv.x *= 3.0;
	uv.x -= TIME;
	COLOR = texture(TEXTURE, uv);
}

