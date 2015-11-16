#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;			
layout(location = 2) in vec2 in_texcoord;
layout(location = 3) in vec3 in_color;

uniform mat4 model_matrix, view_matrix, projection_matrix;
uniform int tps_color;

out vec2 texcoord;
out vec3 world_pos;
out vec3 world_normal;
out vec3 vertex_to_fragment_color;

void main(){

	texcoord = in_texcoord;
	if (tps_color == 1)
		vertex_to_fragment_color = vec3(1, 0, 0);
	else if (tps_color == 2)
		vertex_to_fragment_color = vec3(0, 1, 0);
	else
		vertex_to_fragment_color = in_color;
	
	world_pos = (model_matrix * vec4(in_position, 1)).xyz;
	world_normal = normalize(mat3(model_matrix) * in_normal);

	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_position, 1); 
}
