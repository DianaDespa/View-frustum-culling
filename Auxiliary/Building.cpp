// Despa Diana Alexandra 331CA

#include "Building.h"

Building::Building(unsigned int tex_index, glm::vec3 position)
{
	model_matrix = glm::mat4();
	model_matrix = glm::translate(model_matrix, position);
	this->tex_index = tex_index;
	createGeometry();
}

Building::~Building()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
	glDeleteVertexArrays(1, &vao_ceil);
	glDeleteBuffers(1, &vbo_ceil);
	glDeleteBuffers(1, &ibo_ceil);
}

void Building::createGeometry()
{
	std::vector<MyVertexFormat> vertices_walls;
	std::vector<unsigned int> indices_walls;

	std::vector<MyVertexFormat> vertices_ceil;
	std::vector<unsigned int> indices_ceil;

	// Genereaza dimensiuni aleatorii intre limitele precizate in aceasta clasa.
	float size_x = MIN_WIDTH + rand() % (MAX_WIDTH - MIN_WIDTH),
		size_z = MIN_WIDTH + rand() % (MAX_WIDTH - MIN_WIDTH);
	float height = MIN_HEIGHT + rand() % (MAX_HEIGHT - MIN_HEIGHT);

	float half_size_x = size_x / 2,
		half_size_z = size_z / 2;
	
	glm::vec3 color(1, 1, 1);

	// 4 fete verticale
	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, 0, half_size_z), glm::vec3(0, 0, 1), glm::vec2(0, 0)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, 0, half_size_z), glm::vec3(0, 0, 1), glm::vec2(0, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, height, half_size_z), glm::vec3(0, 0, 1), glm::vec2(2, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, height, half_size_z), glm::vec3(0, 0, 1), glm::vec2(2, 0)));
	indices_walls.push_back(0);
	indices_walls.push_back(1);
	indices_walls.push_back(2);
	indices_walls.push_back(0);
	indices_walls.push_back(2);
	indices_walls.push_back(3);

	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, 0, half_size_z), glm::vec3(-1, 0, 0), glm::vec2(0, 0)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, 0, -half_size_z), glm::vec3(-1, 0, 0), glm::vec2(0, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, height, -half_size_z), glm::vec3(-1, 0, 0), glm::vec2(2, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, height, half_size_z), glm::vec3(-1, 0, 0), glm::vec2(2, 0)));
	indices_walls.push_back(4);
	indices_walls.push_back(5);
	indices_walls.push_back(6);
	indices_walls.push_back(4);
	indices_walls.push_back(6);
	indices_walls.push_back(7);

	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, 0, -half_size_z), glm::vec3(0, 0, -1), glm::vec2(0, 0)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, 0, -half_size_z), glm::vec3(0, 0, -1), glm::vec2(0, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, height, -half_size_z), glm::vec3(0, 0, -1), glm::vec2(2, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(-half_size_x, height, -half_size_z), glm::vec3(0, 0, -1), glm::vec2(2, 0)));
	indices_walls.push_back(8);
	indices_walls.push_back(9);
	indices_walls.push_back(10);
	indices_walls.push_back(8);
	indices_walls.push_back(10);
	indices_walls.push_back(11);

	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, 0, -half_size_z), glm::vec3(1, 0, 0), glm::vec2(0, 0)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, 0, half_size_z), glm::vec3(1, 0, 0), glm::vec2(0, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, height, half_size_z), glm::vec3(1, 0, 0), glm::vec2(2, 1)));
	vertices_walls.push_back(MyVertexFormat(glm::vec3(half_size_x, height, -half_size_z), glm::vec3(1, 0, 0), glm::vec2(2, 0)));
	indices_walls.push_back(12);
	indices_walls.push_back(13);
	indices_walls.push_back(14);
	indices_walls.push_back(12);
	indices_walls.push_back(14);
	indices_walls.push_back(15);

	// Fata de sus/tavan.
	vertices_ceil.push_back(MyVertexFormat(glm::vec3(-half_size_x, height, -half_size_z), glm::vec3(0, 1, 0), glm::vec3(0.1, 0.1, 0.1)));
	vertices_ceil.push_back(MyVertexFormat(glm::vec3(half_size_x, height, -half_size_z), glm::vec3(0, 1, 0), glm::vec3(0.1, 0.1, 0.1)));
	vertices_ceil.push_back(MyVertexFormat(glm::vec3(half_size_x, height, half_size_z), glm::vec3(0, 1, 0), glm::vec3(0.1, 0.1, 0.1)));
	vertices_ceil.push_back(MyVertexFormat(glm::vec3(-half_size_x, height, half_size_z), glm::vec3(0, 1, 0), glm::vec3(0.1, 0.1, 0.1)));
	indices_ceil.push_back(0);
	indices_ceil.push_back(1);
	indices_ceil.push_back(2);
	indices_ceil.push_back(0);
	indices_ceil.push_back(2);
	indices_ceil.push_back(3);
	
	num_indices = indices_walls.size();
	num_indices_ceil = indices_ceil.size();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*(vertices_walls.size()), &vertices_walls[0], GL_STATIC_DRAW);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * num_indices, &indices_walls[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 9));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 6));

	glGenVertexArrays(1, &vao_ceil);
	glBindVertexArray(vao_ceil);
	glGenBuffers(1, &vbo_ceil);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_ceil);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*(vertices_ceil.size()), &vertices_ceil[0], GL_STATIC_DRAW);
	glGenBuffers(1, &ibo_ceil);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_ceil);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * num_indices_ceil, &indices_ceil[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 9));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 6));

	vertices.push_back(vertices_walls[0]);
	vertices.push_back(vertices_walls[1]);
	vertices.push_back(vertices_walls[2]);
	vertices.push_back(vertices_walls[3]);
	vertices.push_back(vertices_walls[8]);
	vertices.push_back(vertices_walls[9]);
	vertices.push_back(vertices_walls[10]);
	vertices.push_back(vertices_walls[11]);
	glm::vec4 temp;
	// Salvez pozitiile translatate ale vertecsilor, conform matricei de adiacenta.
	for (int i = 0; i < vertices.size(); ++i) {
		temp = model_matrix * glm::vec4(vertices[i].position, 1);
		vertices[i].position = glm::vec3(temp.x, temp.y, temp.z);
	}
}

void Building::drawGeometryWalls(unsigned int gl_program_shader)
{
	glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix));
	glUniform1i(glGetUniformLocation(gl_program_shader, "textura"), tex_index);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}

void Building::drawGeometryCeil(unsigned int gl_program_shader)
{
	glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix));
	glBindVertexArray(vao_ceil);
	glDrawElements(GL_TRIANGLES, num_indices_ceil, GL_UNSIGNED_INT, 0);
}

glm::mat4 Building::getModelMatrix()
{
	return model_matrix;
}

 std::vector<MyVertexFormat> Building::getVertices()
{
	return vertices;
}