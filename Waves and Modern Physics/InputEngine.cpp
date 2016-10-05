#include "InputEngine.h"

InputEngine::InputEngine(CoreManager * core)
{
}

void InputEngine::Keyboard()
{
	SDL_Event event;
	/* Poll for events. SDL_PollEvent() returns 0 when there are no  */
	/* more events on the event queue, our while loop will exit when */
	/* that occurs.                                                  */
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
			default:
				break;
			}
		case SDL_MOUSEMOTION:
			//if (glm::abs(event.motion.xrel) < 100 && glm::abs(event.motion.yrel < 100) && !stop_camera_direction)
			break;
		default:
			break;
		}
	}	
}
