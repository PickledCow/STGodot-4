// NOTE: Shader automatically converted from Godot Engine 4.5.beta2's StandardMaterial3D.

shader_type spatial;
render_mode blend_mix, depth_draw_opaque, cull_back, diffuse_burley, specular_schlick_ggx;

uniform float time;

uniform float time_scale : hint_range(0.0, 10.0) = 1.0;
uniform float subdiv : hint_range(0.1, 128.0, 1.0);
uniform float plane_length : hint_range(0.1, 256.0);
uniform float incline : hint_range(0.5, 1.0) = 0.75;
uniform float shadow_strength : hint_range(0.0, 1.0) = 1.0;

uniform vec4 albedo : source_color;
uniform sampler2D texture_albedo : source_color, filter_linear_mipmap, repeat_enable;
uniform ivec2 albedo_texture_size;
uniform float point_size : hint_range(0.1, 128.0, 0.1);

uniform float roughness : hint_range(0.0, 1.0);
uniform sampler2D texture_metallic : hint_default_white, filter_linear_mipmap, repeat_enable;
uniform vec4 metallic_texture_channel;
uniform sampler2D texture_roughness : hint_roughness_r, filter_linear_mipmap, repeat_enable;

uniform float specular : hint_range(0.0, 1.0, 0.01);
uniform float metallic : hint_range(0.0, 1.0, 0.01);

uniform sampler2D texture_normal : hint_roughness_normal, filter_linear_mipmap, repeat_enable;
uniform float normal_scale : hint_range(-16.0, 16.0);

uniform float clearcoat : hint_range(0.0, 1.0, 0.01);
uniform float clearcoat_roughness : hint_range(0.0, 1.0, 0.01);
uniform sampler2D texture_clearcoat : hint_default_white, filter_linear_mipmap, repeat_enable;

uniform vec3 uv1_scale;
uniform vec3 uv1_offset;
uniform vec3 uv2_scale;
uniform vec3 uv2_offset;

void vertex() {
	float step_count = subdiv * 0.5;
	
	float current_floor = floor(UV.x * step_count) / step_count;
	float inwards = step(0.5, mod(UV.x * step_count, 1.0));
	VERTEX.x += inwards / step_count * plane_length * 0.5;
	VERTEX.y += current_floor * plane_length * incline;
	// Baked in AO
	COLOR.rgb *= 1.0 - inwards * shadow_strength;
	
	// Scrolling, loop around
	float vertex_offset = mod(time * time_scale, 1.0);
	VERTEX.x -= vertex_offset / step_count * plane_length;
	VERTEX.y -= vertex_offset / step_count * plane_length * incline;
	// Texture warps each time it loops
	UV.x += mod(floor(time * time_scale) / (step_count + 0.5), 1.0);

}

void fragment() {
	vec2 base_uv = UV * uv1_scale.xy + uv1_offset.xy;

	vec4 albedo_tex = texture(texture_albedo, base_uv);

	// Vertex Color Use as Albedo: Enabled
	albedo_tex *= COLOR;

	ALBEDO = albedo.rgb * albedo_tex.rgb;

	float metallic_tex = dot(texture(texture_metallic, base_uv), metallic_texture_channel);
	METALLIC = metallic_tex * metallic;
	SPECULAR = specular;

	vec4 roughness_texture_channel = vec4(1.0, 0.0, 0.0, 0.0);
	float roughness_tex = dot(texture(texture_roughness, base_uv), roughness_texture_channel);
	ROUGHNESS = roughness_tex * roughness;

	// Normal Map: Enabled
	NORMAL_MAP = texture(texture_normal, base_uv).rgb;
	NORMAL_MAP_DEPTH = normal_scale;

	//// Clearcoat: Enabled
	//vec2 clearcoat_tex = texture(texture_clearcoat, base_uv).xy;
	//CLEARCOAT = clearcoat * clearcoat_tex.x;
	//CLEARCOAT_ROUGHNESS = clearcoat_roughness * clearcoat_tex.y;
}
