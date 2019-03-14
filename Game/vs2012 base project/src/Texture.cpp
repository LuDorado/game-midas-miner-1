#include "../headers/Texture.h"

Texture::Texture() {
	_mRenderer = NULL;
	_mTexture = NULL;

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
		LogHandler::LogError("IMG_Init PNG error");
		SDL_Quit();
	}
}

Texture::~Texture() {
	SDL_DestroyTexture(_mTexture);

	_mRenderer = NULL;
	_mTexture = NULL;
}

void Texture::Load(const char* file) {
	_mTexture = IMG_LoadTexture(_mRenderer, file);

	if (_mTexture == NULL)
		LogHandler::LogError("Error loading texture");
}

void Texture::Render() {
	SDL_RenderCopy(_mRenderer, _mTexture, NULL, &_mPos);
}

void Texture::SetRenderer(SDL_Renderer *r) {
	_mRenderer = r;
}

void Texture::SetClip(SDL_Rect r) {
	_mClip = r;
}

void Texture::SetPos(SDL_Rect r) {
	_mPos = r;
}

SDL_Rect Texture::GetPos() const {
	return _mPos;
}