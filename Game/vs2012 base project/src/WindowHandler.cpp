#include "../headers/WindowHandler.h"

WindowHandler::WindowHandler(unsigned short width, unsigned short height) {
	_mWidth = width;
	_mHeight = height;
	_mWindow = NULL;
	_mRenderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		LogHandler::LogError("SDL failed to init");
		SDL_Quit();
	}

	_mWindow = SDL_CreateWindow("Midas Miner", 100, 100, _mWidth, _mHeight, SDL_WINDOW_SHOWN);

	if (_mWindow == NULL) {
		LogHandler::LogError("Error creating window");
		SDL_Quit();
	}

	_mRenderer = SDL_CreateRenderer(_mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (_mRenderer == NULL) {
		SDL_DestroyWindow(_mWindow);
		LogHandler::LogError("SDL_CreateRenderer Error");
		SDL_Quit();
	}
}

WindowHandler::~WindowHandler() {
	SDL_DestroyRenderer(_mRenderer);
	SDL_DestroyWindow(_mWindow);
	SDL_Quit();
}

SDL_Renderer* WindowHandler::GetRenderer() {
	return _mRenderer;
}
