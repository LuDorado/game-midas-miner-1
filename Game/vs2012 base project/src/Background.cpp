// Background implementation

#include "../headers/Background.h"

Background::Background(SDL_Renderer *r) {
	_mRenderer = r;
}

Background::Background() {
	_mRenderer = NULL;
}

Background::~Background() {
}
