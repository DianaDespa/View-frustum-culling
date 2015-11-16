// Despa Diana Alexandra 331CA

#include "Quad.h"

Quad::Quad(unsigned int size)
{
	this->size = size;
	model_matrix = glm::mat4();
	createGeometry();
}

Quad::~Quad()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

unsigned int Quad::getSize()
{
	return size;
}

void Quad::createGeometry()
{
	std::vector<unsigned int> indices;
	glm::vec3 color = glm::vec3(0.1, 0.1, 0.1);
	vertices.push_back(MyVertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), color));
	vertices.push_back(MyVertexFormat(glm::vec3(0, 0, size), glm::vec3(0, 1, 0), color));
	vertices.push_back(MyVertexFormat(glm::vec3(size, 0, size), glm::vec3(0, 1, 0), color));
	vertices.push_back(MyVertexFormat(glm::vec3(size, 0, 0), glm::vec3(0, 1, 0), color));

	indices.push_back(0); 
	indices.push_back(1); 
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);
	num_indices = indices.size();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MyVertexFormat)*(vertices.size()), &vertices[0], GL_STATIC_DRAW);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * num_indices, &indices[0], GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertexFormat), (void*)(sizeof(float) * 6));
}

void Quad::drawGeometry(unsigned int gl_program_shader, bool is_fps, std::vector<glm::vec4> plane_coefs)
{
	// Daca quad-ul nu este vizibil, nu il desenez.
	if (!tema::isVisible(vertices, plane_coefs))
		return;
	glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix));
	glUniform1i(glGetUniformLocation(gl_program_shader, "has_color"), 1);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}