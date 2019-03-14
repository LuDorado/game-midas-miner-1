#pragma once

#include "../external/include/sdl/SDL.h"
#include <vector>
#include "Gem.h"

using namespace std;

class GemChain {
public:
	const enum ValidChain { VERTICAL, HORIZONTAL };

	GemChain ();
	~GemChain ();
	void AddGem(Gem* gem);
	vector<Gem*> GetGems() const;
	void SetValidChain(enum ValidChain t);

private:
	vector<Gem*> _mGems;
	unsigned short _mValidChain;
};