// Despa Diana Alexandra 331CA

#pragma once
#include "Building.h"
#include "PlaneExtractUtil.h"

// Clasa ce reprezinta multimea de cladiri.
class City
{
private:
	std::vector<Building *> buildings;	// Multimea de cladiri.

public:
	static const int RED = 1;
	static const int GREEN = 2;
	
	City(unsigned int no_textures);
	~City();

	// Deseneaza cladirile din interiorul frustum-ului.
	void draw(unsigned int gl_program_shader, bool is_fps, std::vector<glm::vec4> plane_coefs);
};

