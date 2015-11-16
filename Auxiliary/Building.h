// Despa Diana Alexandra 331CA

#pragma once
#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glew\glew.h"
#include "..\dependente\glm\gtc\type_ptr.hpp"
#include "..\dependente\glm\gtc\matrix_transform.hpp"
#include "MyVertexFormat.h"
#include <vector>

// Clasa ce reprezinta o cladire.
class Building
{
private:
	unsigned int vao, vbo, ibo, vao_ceil, vbo_ceil, ibo_ceil;	// Geometrie cladire.
	unsigned int num_indices, size_ceil, num_indices_ceil;
	glm::mat4 model_matrix;										// Matrice modelare.
	unsigned int tex_index;										// Textura cladirii.
	std::vector<MyVertexFormat> vertices;						// Vertecsi unici.

	void createGeometry();										// Creeaza geometria.

public:
	// Dimensiuni maxime si minime ale unei cladiri.
	static const int MAX_HEIGHT = 75;
	static const int MIN_HEIGHT = 50;
	static const int MAX_WIDTH = 10;
	static const int MIN_WIDTH = 8;

	Building(unsigned int tex_index, glm::vec3 position);
	~Building();

	void drawGeometryWalls(unsigned int gl_program_shader);	// Deseneaza pereti cladire.
	void drawGeometryCeil(unsigned int gl_program_shader);	// Deseneaza tavan cladire.
	glm::mat4 getModelMatrix();								// Intoarce matricea de modelare.
	std::vector<MyVertexFormat> getVertices();				// Intoarce varfurile.
};

