shader_type canvas_item;

uniform vec4 normal_color : source_color;
uniform vec4 max_color : source_color;

const float inv_log10 = 1.0 / log2(10.0);
const float base = 10.0;
const float one = 1.0;

varying flat vec4 modulate;

// Custom colour: (value, fade, max_item, unused)

float log10(float x) {
	return log2(x) * inv_log10;
}

void vertex() {
	modulate = COLOR;
	float digits = floor(log10(modulate.r))+1.0; // Find how many digits are in the number using log10, with +1 being for floating point imprecision compensation
	float fade = modulate.a; // Gets the fade value from the custom colour of the mesh instance
	VERTEX.x *= digits; // Resizes the number, shifting it outwards as more digits are added
	VERTEX.y *= TEXTURE_PIXEL_SIZE.x / TEXTURE_PIXEL_SIZE.y * 10.0; // Resize the height to the required factor
}

// Finds the n'th digit given a number
float get_digit_value(float number, float digit) {
	return floor(mod(number / pow(10.0, digit), base));
}

void fragment() {
	float digits = floor(log10(modulate.r+1.0))+1.0; // Find how many digits are in the number using log10, with +1 being for floating point imprecision compensation
	float digit = floor((1.0 - UV.x) * digits); // Given our current UV, figure out which digit we are on

	vec2 uv = vec2(get_digit_value(modulate.r, digit) * 0.1, 0.0) + vec2(0.1 * mod(UV.x * digits, one), 1.0 * UV.y); // Find what part of the texture to use
	vec4 tex = texture(TEXTURE, uv); // Read from the texture given our coordinates
	COLOR = tex;
	COLOR *= normal_color + (max_color - normal_color) * modulate.b; // If c.b is 1.0, makes the text yellow
	COLOR.a *= (1.0 - modulate.a);
}
