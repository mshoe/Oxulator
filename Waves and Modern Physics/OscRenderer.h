#pragma once
#include "Classes.h"
#include "CoreManager.h"
#include "Camera.h"
#include "Shader.h"
#include "SHO.h"

#include <GL/glew.h>
#include <GL/GL.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

class OscRenderer
{
public:
	OscRenderer(CoreManager *core);
	~OscRenderer();

	void Init();
	void Cleanup();

	//SHO
	SHO *sho;
	void buildSHO(SHO *sho);
	void renderSHO();

	void Render();

	void rotate3(float, float, float, float);

	CoreManager *core = NULL;
	int resolution;

	// Shaders
	Shader *ourShader = NULL;

	// Coordinate Systems
	glm::mat4 *model = NULL;

	//Camera
	Camera *camera = NULL;
	/*void moveCameraPosition(Camera_Movement direction, GLfloat deltaTime);
	void moveCameraDirection(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch);*/

	//Shapes
	std::vector<GLfloat> cubeVerts();
	std::vector<GLuint> cubeInds();
	
	//
	GLuint VAO, VBO, EBO;
};