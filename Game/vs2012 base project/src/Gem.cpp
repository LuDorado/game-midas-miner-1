#include "../headers/Gem.h"

Gem::Gem(SDL_Renderer *r) {
	_mRenderer = r;
}

Gem::Gem() {
	_mRenderer = NULL;
}

Gem::~Gem() {
}

void Gem::SetColor(unsigned short color) {
	;
}

unsigned short Gem::GetColor() {
	return _mColor;
}

void Gem::SetColumn(unsigned short column) {
	_mColumn = column;
}

unsigned short Gem::GetColumn() {
	return _mColumn;
}

void Gem::SetRow(unsigned short row) {
	_mRow = row;
}

unsigned short Gem::GetRow() {
	return _mRow;
}

/*void DrawGem(Texture textura, float x, float y, float rotation = 0.0f) {
	mEngine.Render(King::Engine::TEXTURE_PURPLE, 250.0f, 250.0f);
}*/
