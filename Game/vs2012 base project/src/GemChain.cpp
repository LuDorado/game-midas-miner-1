#include "../headers/GemChain.h"

GemChain::GemChain(){
}

GemChain ::~GemChain(){
}

void GemChain::AddGem(Gem* gem) {
	_mGems.push_back(gem);
}

vector<Gem*> GemChain::GetGems() const {
	return _mGems;
}

void GemChain::SetValidChain(enum ValidChain vd) {
	_mValidChain = vd;
}