#pragma once

#include "../external/include/sdl/SDL.h"
#include "../external/include/sdl/SDL_ttf.h"
#include "LogHandler.h"

class TextHandler {
public:
	TextHandler(SDL_Renderer *r, unsigned short fontSize = 12);
	~TextHandler();

	void SetFontColor(SDL_Color color);
	void Render(const char *msg, SDL_Rect pos);

private:
	SDL_Renderer *_mRenderer;
	SDL_Surface *_mSurface;
	SDL_Texture *_mTexture;
	TTF_Font *_mFont;
	unsigned short _mFontSize;
	SDL_Color _mColor;
};