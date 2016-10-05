#include "CoreManager.h"

CoreManager::CoreManager()
{
}

CoreManager::~CoreManager()
{
	CleanUp();
}

bool CoreManager::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Failed to init SDL\n";
		return false;
	}

	image_width = 800;
	image_height = 600;

	mainWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		image_width, image_height, SDL_WINDOW_OPENGL);

	// Check that everything worked out okay
	if (!mainWindow)
	{
		std::cout << "Unable to create window\n";
		CheckSDLError(__LINE__);
		return false;
	}

	mainContext = SDL_GL_CreateContext(mainWindow);

	SetOpenGLAttributes();

	SDL_GL_SetSwapInterval(1);

#ifndef __APPLE__
	glewExperimental = GL_TRUE;
	glewInit();
#endif
	
	looping = true;

	render = new OscRenderer(this);
	input = new InputEngine(this);

	return true;
}

void CoreManager::CleanUp()
{
	SDL_GL_DeleteContext(mainContext);
	SDL_DestroyWindow(mainWindow);
	SDL_Quit();
}

void CoreManager::Keyboard()
{
	input->Keyboard();
}

void CoreManager::IdleUpdate()
{
}

void CoreManager::Render()
{
	render->Render();
}

bool CoreManager::SetOpenGLAttributes()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	return true;
}

void CoreManager::PrintSDL_GL_Attributes()
{
	int value = 0;
	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

	SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
	std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}

void CoreManager::CheckSDLError(int line)
{
	std::string error = SDL_GetError();

	if (error != "")
	{
		std::cout << "SLD Error : " << error << std::endl;

		if (line != -1)
			std::cout << "\nLine : " << line << std::endl;

		SDL_ClearError();
	}
}

void CoreManager::RunLoop()
{
	deltaTime = 0;
	totalTime = 0;
	while (looping)
	{
		time1 = std::chrono::high_resolution_clock::now();
		Keyboard();
		Render();
		time2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(time2 - time1);
		
		deltaTime = time_span.count();
		totalTime += deltaTime;
	}
}
