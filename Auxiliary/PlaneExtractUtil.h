// Despa Diana Alexandra 331CA

#pragma once
#include "..\dependente\glm\glm.hpp"
#include "MyVertexFormat.h"
#include <vector>

namespace tema
{
	// Verifica daca un obiect dat prin varfurile "vertices" se afla in interiorul
	// frustum-ului definit prin coeficientii planurilor sale.
	bool isVisible(std::vector<MyVertexFormat> vertices, std::vector<glm::vec4> plane_coefs);
}