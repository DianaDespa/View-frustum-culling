// Despa Diana Alexandra 331CA

#include "PlaneExtractUtil.h"

namespace tema
{
	// Verifica daca un obiect dat prin varfurile "vertices" se afla in interiorul
	// frustum-ului definit prin coeficientii planurilor sale.
	bool isVisible(std::vector<MyVertexFormat> vertices, std::vector<glm::vec4> plane_coefs)
	{
		int i, j;
		for (i = 0; i < plane_coefs.size(); ++i) {
			for (j = 0; j < vertices.size(); ++j) {
				if (plane_coefs[i][0] * vertices[j].position.x +
					plane_coefs[i][1] * vertices[j].position.y +
					plane_coefs[i][2] * vertices[j].position.z +
					plane_coefs[i][3] > 0)
					// Am gasit un varf in interiorul unui plan, nu mai vefic restul varfurilor.
					break;
			}
			if (j >= vertices.size()) {
				// Nu am gasit niciun varf in interiorul unui plan.
				return false;
			}
		}
		// Cel putin un varf este in interiorul frustum-ului.
		return true;
	}
}