// Despa Diana Alexandra 331CA

#include "lab_shader_loader.hpp"
#include "lab_glut.hpp"
#include "lab_texture_loader.hpp"
#include "lab_camera.hpp"
#include "Auxiliary\Quad.h"
#include "Auxiliary\Vehicle.h"
#include "Auxiliary\City.h"
#include <ctime>

class Tema4 : public lab::glut::WindowListener{
private:
	glm::mat4 view_matrix, projection_matrix;	// Matrici 4x4 pt vizualizare proiectie
	unsigned int gl_program_shader;				// ID-ul de opengl al obiectului de tip program shader
	unsigned int screen_width, screen_height;	// Dimensiunile ferestrei

	lab::Camera *view1, *view2;					// Cele doua perspective
	bool is_fps;								// Indica daca perspectiva curenta este FPS

	// Constante pentru iluminare
	unsigned int material_shininess;
	float material_kd;
	float material_ks;

	Quad *quad;
	Vehicle *vehicle;
	City *city;
	std::vector<unsigned int> textures;		// Texturile folosite.

	bool modified;							// Indica daca s-a modificat pozitia/orientarea camerei sau perspectiva.

public:
	
	Tema4() {
		// Setari pentru desenare, clear color seteaza culoarea de clear pentru ecran (format R,G,B,A).
		glClearColor(0.0, 0.0, 0.0, 1);
		glClearDepth(1);			// clear depth si depth test sunt folosite pentru a determina obiectele cele mai apropiate de camera.
		glEnable(GL_DEPTH_TEST);
		
		// Incarca un shader din fisiere si gaseste locatiile matricilor relativ la programul creat.
		gl_program_shader = lab::loadShader("shadere\\shader_vertex.glsl", "shadere\\shader_fragment.glsl");
		
		// Incarca texturi.
		textures.push_back(lab::loadTextureBMP("resurse\\b1.bmp"));
		textures.push_back(lab::loadTextureBMP("resurse\\b2.bmp"));
		textures.push_back(lab::loadTextureBMP("resurse\\b3.bmp"));
		textures.push_back(lab::loadTextureBMP("resurse\\b4.bmp"));
		textures.push_back(lab::loadTextureBMP("resurse\\b5.bmp"));
		textures.push_back(lab::loadTextureBMP("resurse\\flying_car_texture.bmp"));

		for (int i = 0; i < textures.size(); ++i) {
			glActiveTexture(GL_TEXTURE0 + i + 1);
			glBindTexture(GL_TEXTURE_2D, textures[i]);
		}

		srand(time(NULL));

		// Camere
		view1 = new lab::Camera();
		view1->set(glm::vec3(-10, Building::MAX_HEIGHT + 10, 500), glm::vec3(490, Building::MAX_HEIGHT + 10, 500), glm::vec3(0, 1, 0));
		view2 = new lab::Camera();
		view2->set(glm::vec3(500, 750, 500), glm::vec3(500.1, 0, 500.1), glm::vec3(0, 1, 0));
		view2->rotateFPSoX(-45);
		is_fps = true;

		vehicle = new Vehicle();
		quad = new Quad(1000);
		// Folosesc primele 5 texturi pentru cladiri.
		city = new City(textures.size() - 1);

		// Lumina & material
		material_shininess = 10;
		material_kd = 0.4;
		material_ks = 0.1;

		// Desenare solid
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		modified = true;
	}

	~Tema4(){
		glDeleteProgram(gl_program_shader);

		delete vehicle;
		delete quad;
		delete city;
		delete view1;
		delete view2;
		for (int i = 0; i < textures.size(); ++i)
			glDeleteTextures(1, &textures[i]);
	}
	
	// Functii de cadru.

	// Functie chemata inainte de a incepe cadrul de desenare, o folosim ca sa updatam situatia scenei.
	void notifyBeginFrame(){}

	//functia de afisare (lucram cu banda grafica)
	void notifyDisplayFrame() {
		// Deseneaza doar daca s-a modificat pozitia camerei sau perspectiva (a fost apasata o tasta).
		if (modified) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Foloseste shaderul.
			glUseProgram(gl_program_shader);

			// Trimite variabile uniforme la shader.
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "projection_matrix"), 1, false, glm::value_ptr(projection_matrix));
			glUniform1i(glGetUniformLocation(gl_program_shader, "tps_color"), 0);
			glUniform3f(glGetUniformLocation(gl_program_shader, "light_position"),
				view1->getPosition().x, view1->getPosition().y, view1->getPosition().z);
			glUniform3f(glGetUniformLocation(gl_program_shader, "eye_position"),
				view1->getPosition().x, view1->getPosition().y, view1->getPosition().z);
			glUniform3f(glGetUniformLocation(gl_program_shader, "light_direction"),
				view1->getForward().x, view1->getForward().y, view1->getForward().z);
			glUniform1i(glGetUniformLocation(gl_program_shader, "material_shininess"), material_shininess);

			if (is_fps)
				vehicle->drawGeometry(gl_program_shader, textures.size());

			view_matrix = is_fps ? view1->getViewMatrix() : view2->getViewMatrix();
			glUniformMatrix4fv(glGetUniformLocation(gl_program_shader, "view_matrix"), 1, false, glm::value_ptr(view_matrix));
			glUniform1f(glGetUniformLocation(gl_program_shader, "material_kd"), is_fps ? material_kd : 0);
			glUniform1f(glGetUniformLocation(gl_program_shader, "material_ks"), is_fps ? material_ks : 0);

			std::vector<glm::vec4> plane_coefs;
			glm::mat4 pv = projection_matrix * view1->getViewMatrix();

			// Calculeaza coeficientii ecuatiilor pentru planurile frustumului.
			plane_coefs.push_back(glm::vec4(pv[0][3] + pv[0][0], pv[1][3] + pv[1][0], pv[2][3] + pv[2][0], pv[3][3] + pv[3][0])); // left
			plane_coefs.push_back(glm::vec4(pv[0][3] - pv[0][0], pv[1][3] - pv[1][0], pv[2][3] - pv[2][0], pv[3][3] - pv[3][0])); // right
			plane_coefs.push_back(glm::vec4(pv[0][3] + pv[0][1], pv[1][3] + pv[1][1], pv[2][3] + pv[2][1], pv[3][3] + pv[3][1])); // bottom
			plane_coefs.push_back(glm::vec4(pv[0][3] - pv[0][1], pv[1][3] - pv[1][1], pv[2][3] - pv[2][1], pv[3][3] - pv[3][1])); // top
			plane_coefs.push_back(glm::vec4(pv[0][3] + pv[0][2], pv[1][3] + pv[1][2], pv[2][3] + pv[2][2], pv[3][3] + pv[3][2])); // near
			plane_coefs.push_back(glm::vec4(pv[0][3] - pv[0][2], pv[1][3] - pv[1][2], pv[2][3] - pv[2][2], pv[3][3] - pv[3][2])); // far

			quad->drawGeometry(gl_program_shader, is_fps, plane_coefs);
			city->draw(gl_program_shader, is_fps, plane_coefs);
			modified = false;
		}
	}

	// Functie chemata dupa ce am terminat cadrul de desenare.
	void notifyEndFrame(){}

	// Functei care e chemata cand se schimba dimensiunea ferestrei initiale.
	void notifyReshape(int width, int height, int previos_width, int previous_height){
		if (height == 0)
			height = 1;
		float aspect = (float)width / (float)height;
		projection_matrix = glm::perspective(75.0f, aspect, 0.1f, 10000.0f);
	}
	
	// Functii de input output.
	
	void notifyKeyPressed(unsigned char key_pressed, int mouse_x, int mouse_y){
		//ESC inchide glut.
		if (key_pressed == 27) lab::glut::close();
		if (key_pressed == 'W') {
			static bool wire = true;
			wire = !wire;
			glPolygonMode(GL_FRONT_AND_BACK, (wire ? GL_LINE : GL_FILL));
		}
		// Taste pentru deplasarea camerei FPS de sus.
		if (key_pressed == 'w')
			view1->translateForward(1.0f);
		if (key_pressed == 's')
			view1->translateForward(-1.0f);
		if (key_pressed == 'q')
			view1->translateUpword(1.0f);
		if (key_pressed == 'e')
			view1->translateUpword(-1.0f);
		if (key_pressed == 'a')
			view1->translateRight(-1.0f);
		if (key_pressed == 'd')
			view1->translateRight(1.0f);
		if (key_pressed == '1')
			view1->rotateFPSoX(1.0f);
		if (key_pressed == '2')
			view1->rotateFPSoX(-1.0f);
		if (key_pressed == '3')
			view1->rotateFPSoY(1.0f);
		if (key_pressed == '4')
			view1->rotateFPSoY(-1.0f);
		if (key_pressed == '5')
			view1->rotateFPSoZ(1.0f);
		if (key_pressed == '6')
			view1->rotateFPSoZ(-1.0f);
		if (key_pressed == 'c')
			is_fps = !is_fps;
		modified = true;
	}
	void notifyKeyReleased(unsigned char key_released, int mouse_x, int mouse_y){	}
	void notifySpecialKeyPressed(int key_pressed, int mouse_x, int mouse_y){
		if(key_pressed == GLUT_KEY_F1) lab::glut::enterFullscreen();
		if(key_pressed == GLUT_KEY_F2) lab::glut::exitFullscreen();
	}
	void notifySpecialKeyReleased(int key_released, int mouse_x, int mouse_y){}
	void notifyMouseDrag(int mouse_x, int mouse_y){ }
	void notifyMouseMove(int mouse_x, int mouse_y){ }
	void notifyMouseClick(int button, int state, int mouse_x, int mouse_y){ }
	void notifyMouseScroll(int wheel, int direction, int mouse_x, int mouse_y){ }
};

int main(){
	// Initializeaza GLUT (fereastra + input + context OpenGL).
	lab::glut::WindowInfo window(std::string("Tema4 - View Frustum Culling"),700,700,350,0,true);
	lab::glut::ContextInfo context(3,3,false);
	lab::glut::FramebufferInfo framebuffer(true,true,true,true);
	lab::glut::init(window,context, framebuffer);

	// Initializeaza GLEW.
	glewExperimental = true;
	glewInit();
	std::cout<<"GLEW:initializare"<<std::endl;

	// Creem clasa noastra si o punem sa asculte evenimentele de la GLUT.
	// DUPA GLEW!!! ca sa avem functiile de OpenGL incarcate inainte sa ii fie apelat constructorul (care creeaza obiecte OpenGL).
	Tema4 tema;
	lab::glut::setListener(&tema);

	// Taste
	std::cout << "Taste:" << std::endl << "\tESC ... iesire" << std::endl << "\tSPACE ... reincarca shadere" << std::endl << "\tw ... toggle wireframe" << std::endl;

	lab::glut::run();

	return 0;
}