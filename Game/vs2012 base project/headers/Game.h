#pragma once

#include "../external/include/sdl/SDL.h"
#include <cassert>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include "Background.h"
#include "Gem.h"
#include "GemChain.h"
#include "GemSwap.h"
#include "TextHandler.h"
#include "WindowHandler.h"

using namespace std;

class Game {
public:
	static const unsigned short ROWS = 8;
	static const unsigned short COLS = 8;

	//static const
		enum GameState {LOADING, IDLE, SWAPPING, ROLLING_BACK, PROCESSING, END_PROCESSING, FINISHED};
	//static const 
		enum ScoreSystem { CHAIN3 = 30, CHAIN4 = 40, CHAIN5 = 100};

	Game(SDL_Renderer *r);
	~Game();
	unsigned short GetGameState() const;
	void Render() const;
	void LoadGame(unsigned short gameNumber);
	void SetState(unsigned short state);
	void OnMouseButtonDown(int x, int y);
	void OnMouseButtonUp(int x, int y);
	void Update();

private:
	unsigned short GetRandomColor(int col, int row) const;
	const char* GetColorFile(unsigned short color) const;
	void GetGridCoords(int x, int y, int &row, int &col) const;
	void SwapGems(int originCol, int originRow, int destCol, int destRow);
	bool IsValidChain(int col, int row) const;
	void RemoveGemChains();
	void FindVerticalChains();
	void FindHorizontalChains();
	void FillRemovedChainsHoles();
	void FillTableTop();
	void AnimateFallingGems();
	void AnimateNewGems();
	void UpdateScore(unsigned int count);

	Background *_mBackground;
	Gem *_mGems[ROWS][COLS];
	SDL_Renderer *_mRenderer;
	unsigned short _mGameNumber;
	unsigned short _mGameState;
	unsigned int _mScore;
	char _mScoreString[10];
	int _mSwapOriginCol;
	int _mSwapOriginRow;
	int _mSwapDestCol;
	int _mSwapDestRow;
	bool _mCompleted;
	bool _mSwipe;
	bool _mHasHoles;
	bool _mRefillTop;
	vector<GemChain> _mGemChains;
	vector<Gem*> _mFallingGems;
	vector<Gem*> _mNewGems;
	Swap *_mSwap;
	TextHandler *_mTextHandler;
};