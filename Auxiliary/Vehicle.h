// Despa Diana Alexandra 331CA

#pragma once

#include "..\dependente\glm\glm.hpp"
#include "..\dependente\glew\glew.h"
#include "..\dependente\glm\gtc\type_ptr.hpp"
#include "..\dependente\glm\gtc\matrix_transform.hpp"
#include "..\lab_camera.hpp"
#include "Building.h"

// Clasa ce reprezinta vehiculul - obiectul care se deplaseaza odata cu camera.
class Vehicle
{
private:
	unsigned int vao, vbo, ibo;				// Geometrie vehicul.
	unsigned int num_indices;
	glm::mat4 model_matrix, view_matrix;	// Matrici de modelare si vizualizare.

	void createGeometry();					// Creeaza geometria.
public:
	Vehicle();
	~Vehicle();

	void drawGeometry(unsigned int gl_program_shader, unsigned int texture);	// Deseneaza vehicul.
};