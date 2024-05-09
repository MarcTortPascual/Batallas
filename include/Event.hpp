#include <SDL2/SDL.h>
#pragma once

class Event {
	private:
		SDL_Event e;
public:
	void poll() {
		SDL_PollEvent(&this->e);
	}
	Uint32 getType() {
		return this->e.type;
	}
	Uint8 getMouseButon() {
		return this->e.button.button;
	}
	Uint32 getKey() {
		return this->e.key.keysym.sym;
	}
	void getMousePosition(int *x,int *y) {
		*(x) = this->e.motion.x;
		*(y) = this->e.motion.y;
	}
};