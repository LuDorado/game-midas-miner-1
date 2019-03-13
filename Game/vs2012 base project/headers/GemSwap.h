#pragma once

#include <SDL.h>
#include <cassert>
#include "Gem.h"

class Swap
{
public:

	static enum ValidDirection { UP, DOWN, LEFT, RIGHT };

	//constructor
	Swap(Gem* A, Gem* B);
	//destructor
	~Swap();
	//metodos
	void SetDirection(enum ValidDirection d);
	void RollBack();
	void Update();
	void RollingBack();
	bool Done();

private:
	//datos
	Gem* _mA;//punteros a gema 
	Gem* _mB;
	SDL_Rect _destA;
	SDL_Rect _destB;
	bool _mDone;
	bool _mInvalid;
	enum ValidDirection _mDirection;
};

