// Despa Diana Alexandra 331CA

#pragma once
#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glew\glew.h"
#include "..\dependente\glm\gtc\type_ptr.hpp"
#include "MyVertexFormat.h"
#include "PlaneExtractUtil.h"
#include <vector>

// Clasa ce reprezinta quad-ul.
class Quad
{
private:
	unsigned int vao, vbo, ibo;			// Geometrie quad.
	unsigned int size, num_indices;
	glm::mat4 model_matrix;				// Matrice modelare.

	std::vector<MyVertexFormat> vertices;

	void createGeometry();		// Creeaza geometria.

public:
	Quad(unsigned int size);
	~Quad();					// Distruge geometria.

	void drawGeometry(unsigned int gl_program_shader, bool is_fps, std::vector<glm::vec4> plane_coefs);	// Deseneaza quad.
	unsigned int getSize();								// Intoarce dimensiunea quad-ului.
};

