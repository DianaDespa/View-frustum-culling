// Despa Diana Alexandra 331CA

#pragma once
#include "..\dependente\glm\glm.hpp"

// Structura care defineste formatul unui vertex.
struct MyVertexFormat {
	glm::vec3 position, normal, color;
	glm::vec2 texcoords;

	MyVertexFormat() {
		position = color = normal = glm::vec3(0, 0, 0);
		texcoords = glm::vec2(0, 0);
	}
	MyVertexFormat(glm::vec3 position, glm::vec3 normal) {
		this->position = position;
		this->normal = normal;
		color = glm::vec3(0, 0, 0);
		texcoords = glm::vec2(0, 0);
	}
	MyVertexFormat(glm::vec3 position, glm::vec3 normal, glm::vec2 texcoords) {
		this->position = position;
		this->normal = normal;
		this->texcoords = texcoords;
		color = glm::vec3(0, 0, 0);
	}
	MyVertexFormat(glm::vec3 position, glm::vec3 normal, glm::vec3 color) {
		this->position = position;
		this->color = color;
		this->normal = normal;
		texcoords = glm::vec2(0, 0);
	}
};