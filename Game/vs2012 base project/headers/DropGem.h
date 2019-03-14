#pragma once

#include "../external/include/sdl/SDL.h"
#include <cassert>
#include <list>

#include "Background.h"
#include "Gem.h"

using namespace std;

class DropGem {

public:
	DropGem(list<Gem*> gems);
	~DropGem();

	void Update();
	bool Done();

private:
	bool _mDone;
	SDL_Rect _mDest;
	list<Gem*> _mGems;

};
