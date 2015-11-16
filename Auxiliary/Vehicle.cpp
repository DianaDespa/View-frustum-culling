// Despa Diana Alexandra 331CA

#include "Vehicle.h"
#include "..\lab_mesh_loader.hpp"

Vehicle::Vehicle()
{
	// Vehiculul are mereu aceeasi pozitie fata de camera.
	model_matrix = glm::translate(glm::mat4(), glm::vec3(0, -3, 4.5));
	model_matrix = glm::scale(model_matrix, glm::vec3(0.01, 0.01, 0.01));
	view_matrix = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 1, 0));
	
	createGeometry();
}

Vehicle::~Vehicle()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Vehicle::createGeometry()
{
	lab::loadObj("resurse\\flying_car.obj", vao, vbo, ibo, num_indices);
}

void Vehicle::drawGeometry(unsigned int gl_program_shader, unsigned int texture_index)
{
	glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "view_matrix"), 1, false, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "model_matrix"), 1, false, glm::value_ptr(model_matrix));
	glUniform1f(glGetUniformLocation(gl_program_shader, "material_kd"), 0); // vehiculul nu este iluminat
	glUniform1f(glGetUniformLocation(gl_program_shader, "material_ks"), 0);
	glUniform1i(glGetUniformLocation(gl_program_shader, "textura"), texture_index);
	glUniform1i(glGetUniformLocation(gl_program_shader, "has_color"), 0);
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
}