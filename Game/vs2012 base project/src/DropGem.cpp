#include "../headers/DropGem.h"

DropGem::DropGem(list<Gem*> gems) {
	_mGems = gems;
	_mDone = false;
	_mDest = { -1, -1, 0, 0 };
}

DropGem::~DropGem() {
}

bool DropGem::Done() {
	return _mDone;
}

void DropGem::Update() {
	if (!_mDone) {
		Gem *r = _mGems.front();

		if (_mDest.y < 0) {
			_mDest.y = Background::OFFSET_Y + (r->GetRow() * Gem::GEM_HEIGHT) + (Gem::PIXEL_SEP * r->GetRow());
			_mDest.x = r->GetPos().x;
		}

		SDL_Rect newPos = { _mDest.x, r->GetPos().y + 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
		r->SetPos(newPos);

		if (r->GetPos().y >= _mDest.y) {
			_mDest.y = -1;
			_mGems.pop_front();
		}

		if (_mGems.empty())
			_mDone = true;
	}
}
