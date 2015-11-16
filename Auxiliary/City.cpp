// Despa Diana Alexandra 331CA

#include "City.h"

City::City(unsigned int no_textures)
{
	float distance = (float)20;	// Distanta dintre cladiri.
	glm::vec3 init_pos(distance / 2, 0, distance / 2); // Pozitia primei cladiri.
	// Creeaza 2500 de cladiri.
	for (int i = 0; i < 50; ++i) {
		for (int j = 0; j < 50; ++j) {
			buildings.push_back(new Building(rand() % no_textures + 1, init_pos + glm::vec3(j * distance, 0, i * distance)));
		}
	}
}

City::~City()
{
}

void City::draw(unsigned int gl_program_shader, bool is_fps, std::vector<glm::vec4> plane_coefs)
{
	int i;
	std::vector<int> visible_buildings, invisible_buildings;
	
	// Determina ce cladiri sunt vizibile.
	for (i = 0; i < buildings.size(); ++i) {
		if (tema::isVisible(buildings[i]->getVertices(), plane_coefs))
			visible_buildings.push_back(i);
		else
			invisible_buildings.push_back(i);
	}
	
	if (is_fps) {
		// Deseneaza cladirile vizibile, in perspectiva FPS.
		glUniform1i(glGetUniformLocation(gl_program_shader, "has_color"), 0);
		for (i = 0; i < visible_buildings.size(); ++i)
			buildings[visible_buildings[i]]->drawGeometryWalls(gl_program_shader);
		glUniform1i(glGetUniformLocation(gl_program_shader, "has_color"), 1);
		for (i = 0; i < visible_buildings.size(); ++i) {
			buildings[visible_buildings[i]]->drawGeometryCeil(gl_program_shader);
		}
	}
	else {
		// Deseneaza toate cladirile, avand culoarea corespunzatoare, in
		// perspectiva TPS.
		glUniform1i(glGetUniformLocation(gl_program_shader, "tps_color"), GREEN);
		for (i = 0; i < visible_buildings.size(); ++i) {
			buildings[visible_buildings[i]]->drawGeometryWalls(gl_program_shader);
			buildings[visible_buildings[i]]->drawGeometryCeil(gl_program_shader);
		}
		glUniform1i(glGetUniformLocation(gl_program_shader, "tps_color"), RED);
		for (i = 0; i < invisible_buildings.size(); ++i) {
			buildings[invisible_buildings[i]]->drawGeometryWalls(gl_program_shader);
			buildings[invisible_buildings[i]]->drawGeometryCeil(gl_program_shader);
		}
	}
}