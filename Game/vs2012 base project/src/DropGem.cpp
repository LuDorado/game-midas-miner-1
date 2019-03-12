#include "DropGem.h"

DropGem::DropGem(list<Gem*> gems) {
	Gems = gems;
	Done = false;
	Dest = {-1, -1, 0, 0}
}

DropGem::~DropGem() {
}

bool DropGem::Done() {
	return Done;
}

void DropGem::Update() {
	if (!Done) {
		Gem *r = Gems.front();

		if (Dest < 0) {
			Dest.y = Background::OFFSET_Y + (r->GetRow() * Gem::GEM_HEIGHT) + (Gem::PIXEL_SEPARATION * r->GetRow());
			Dest.x = r->GetPos().x;
		}

		SDL_Rect newPos = { Dest.x, r->GetPos().y + 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
		r->SetPos(newPos);

		if (r->GetPos().y >= Dest.y) {
			Dest = -1;
			Gems.pop_front();
		}

		if (Gems.empty())
			Done = true;
	}
}
