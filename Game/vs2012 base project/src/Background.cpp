// Background implementation

#include "Background.h"

Background::Background(SDL_Renderer *r) {
	Renderer = r;
}

Background::Background() {
	Renderer = NULL;
}

Background::~Background() {
}
