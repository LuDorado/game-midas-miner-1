#pragma once

#include "../external/include/sdl/SDL.h"
#include "../external/include/sdl/SDL_image.h"
#include "LogHandler.h"

class WindowHandler {
public:
	WindowHandler(unsigned short w, unsigned short h);
	~WindowHandler();
	SDL_Renderer* GetRenderer();

private:
	unsigned short _mWidth;
	unsigned short _mHeight;
	SDL_Window *_mWindow;
	SDL_Renderer *_mRenderer;
};