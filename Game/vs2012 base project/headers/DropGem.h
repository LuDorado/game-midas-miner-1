#pragma once

#include <SDL.h>
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
	bool Done;
	SDL_Rect Dest;
	list<Gem*> Gems;

	<
};
