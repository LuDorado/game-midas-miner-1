#include "Texture.h"

Texture::Texture() {
	Renderer = NULL;
	Texture = NULL;

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		Log_Handler::LogError("IMG_Init PNG error");
		SDL_Quit();
	}
}

Texture::~Texture() {
	SDL_DestroyTexture(_mTexture);

	Renderer = NULL;
	Texture = NULL;
}

void Texture::Load(const char* file) {
	Texture = IMG_LoadTexture(_mRenderer, file);

	if (Texture == NULL)
		Log_Handler::LogError("Error loading texture");
}

void Texture::Render() {
	SDL_RenderCopy(Renderer, Texture, NULL, &Pos);
}

void Texture::SetRenderer(SDL_Renderer *r) {
	Renderer = r;
}

void Texture::SetClip(SDL_Rect r) {
	Clip = r;
}

void Texture::SetPos(SDL_Rect r) {
	Pos = r;
}

SDL_Rect Texture::GetPos() const {
	return Pos;
}