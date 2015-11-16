#version 330
layout(location = 0) out vec4 out_color;

uniform sampler2D textura;
uniform int has_color;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform vec3 light_direction;
uniform int material_shininess;
uniform float material_kd;
uniform float material_ks;

in vec2 texcoord;
in vec3 world_pos;
in vec3 world_normal;
in vec3 vertex_to_fragment_color;

void main() {

	vec3 tex = texture(textura, texcoord).xyz;

	float light = 0.0f;
	float Ca = -0.25f;
	float Cd, Cs;
	float cutoff = 0.4f;

	vec3 L = normalize(light_position - world_pos),
		V = normalize(eye_position - world_pos),
		R = reflect(-L, world_normal),
		H = normalize(L + V);
	Cd = material_kd * max(dot(world_normal, L), 0);
	Cs = material_ks * pow(max(dot(world_normal, H), 0), material_shininess);

	if (material_kd != 0 || material_ks != 0)
		light = Ca;
	if (cos(cutoff) <= dot(L, light_direction))
		light += Cd + Cs;

	if (has_color > 0)
		out_color = vec4(vertex_to_fragment_color + vec3(light, light, light), 1);
	else
		out_color = vec4(tex + vec3(light, light, light), 1);
}