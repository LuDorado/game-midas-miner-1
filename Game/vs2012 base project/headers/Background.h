//background header file

#pragma once
#include "Texture.h"

class Background : public Texture
{
public:

	static const int OFFSET_X = 350;
	static const int OFFSET_Y = 100;

	static const int WIDTH = 800;
	static const int HEIGHT = 600;

	Background(SDL_Renderer *r);
	Background();
	~Background();
};
