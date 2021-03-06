#pragma once
#include "../external/include/sdl/SDL.h"
#include "../external/include/sdl/SDL_image.h"
#include "../headers/LogHandler.h"

class Texture {
public:
	Texture();
	~Texture();

	void Load(const char* FILE);
	void SetClip(SDL_Rect r);
	void SetPos(SDL_Rect r);
	SDL_Rect GetPos() const;
	void SetRenderer(SDL_Renderer *r);
	void Render();

protected:
	SDL_Renderer *_mRenderer;
	SDL_Texture *_mTexture;
	SDL_Rect _mClip;
	SDL_Rect _mPos;
};