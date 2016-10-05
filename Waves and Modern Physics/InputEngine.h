#pragma once
#include "Classes.h"
#include "CoreManager.h"
#include "camera.h"

#include <SDL2/SDL.h>

class InputEngine
{
public:
	InputEngine(CoreManager *core);
	void Keyboard();
	CoreManager *core;
};