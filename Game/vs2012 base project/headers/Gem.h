#pragma once
#include "Texture.h"


class Gem : public Texture {
public:
	static const int GEM_WIDTH = 35;
	static const int GEM_HEIGHT = 35;
	static const int PIXEL_SEP = 10;

	enum GemColor { RED, YELLOW, BLUE, GREEN, PURPLE };


	Gem(SDL_Renderer *r);
	Gem();
	~Gem();

	void SetColor(unsigned short cr);
	unsigned short GetColor();

	void SetRow(unsigned short r);
	unsigned short GetRow();

	void SetColumn(unsigned short c);
	unsigned short GetColumn();

private:
	unsigned short _mColor;
	unsigned short _mRow;
	unsigned short _mColumn;
};