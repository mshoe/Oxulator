#pragma once
#include "Classes.h"
#include "OscRenderer.h"
#include "InputEngine.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include <chrono>

class CoreManager
{
public:
	CoreManager();
	~CoreManager();

	//State Members
	bool Init();
	int init;
	void CleanUp();

	void Keyboard();
	void IdleUpdate();
	void Render();

	

	//SDL
	// Our SDL_Window ( just like with SDL2 wihout OpenGL)
	SDL_Window *mainWindow;
	int image_width;
	int image_height;

	// Our opengl context handle
	SDL_GLContext mainContext;
	std::string programName = "Augmented Geometry";
	bool SetOpenGLAttributes();
	void PrintSDL_GL_Attributes();
	void CheckSDLError(int line);

	//Engines
	OscRenderer *render;
	InputEngine *input;

	std::chrono::high_resolution_clock::time_point time1;
	std::chrono::high_resolution_clock::time_point time2;
	float deltaTime;
	float totalTime;

	bool looping;
	void RunLoop();
};