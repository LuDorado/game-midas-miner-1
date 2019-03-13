#pragma once
#include "Texture.h"


class Gem : public Texture)
{
public:
	static const int GEM_WIDTH = 0;
	static const int GEM_HEIGHT = 0;
	static const int PIXEL_SEP = 0;

	static enum GEM_COLOR { RED, YELLOW, BLUE, GREEN, PURPLE };


	Gem(SDL_Renderer *r);
	Gem();
	~Gem();

	void SetColor(unsigned short cr);
	unsigned short GetColor() const;

	void SetRow(unsigned short r);
	unsigned short GetRow() const;

	void SetColumn(unsigned short c);
	unsigned short GetColumn() const;

private:
	unsigned short _mColor;
	unsigned short _mRow;
	unsigned short _mColumn;
};