#include "../headers/Game.h"

Game::Game(SDL_Renderer *r) {
	_mGameNumber = 0;
	_mScore = 0;
	_mScoreString[0] = '0';
	_mGameState = 0;
	_mSwapOriginCol = -1;
	_mSwapOriginRow = -1;
	_mSwapDestCol = -1;
	_mSwapDestRow = -1;
	_mCompleted = false;
	_mSwipe = false;
	_mHasHoles = false;
	_mRefillTop = false;
	_mRenderer = r;
	_mSwap = NULL;

	_mBackground = new Background(_mRenderer);
	//_mTextHandler = new TextHandler(_mRenderer, 30);
	//_mTextHandler->SetFontColor({ 255, 250, 0, 255 });

	for (int r = 0; r < Game::ROWS; r++) {
		for (int c = 0; c < Game::COLS; c++) {
			_mGems[r][c] = NULL;
		}
	}
}

Game::~Game() {
	_mRenderer = NULL;

	if (_mBackground)
		delete _mBackground;
	_mBackground = NULL;

	for (int r = 0; r < Game::ROWS; r++) {
		for (int c = 0; Game::COLS; c++) {
			delete _mGems[r][c];
		}
	}
}

unsigned short Game::GetRandomColor(int col, int row) const {

	unsigned short color;

	do {
		color = Gem::YELLOW + (rand() % 5);
	} while (
		(col >= 2 &&
		_mGems[row][col - 1]->GetColor() == color &&
		_mGems[row][col - 2]->GetColor() == color)
		||
		(row >= 2 &&
			_mGems[row - 1][col]->GetColor() == color &&
			_mGems[row - 2][col]->GetColor() == color));

	return color;
}

const char* Game::GetColorFile(unsigned short color) const {
	const char *colorFile = "";

	switch (color) {
	case Gem::RED:
		colorFile = "../bin/assets/Red.png";
		break;
	case Gem::BLUE:
		colorFile = "../assets/Blue.png";
		break;
	case Gem::YELLOW:
		colorFile = "../assets/Yellow.png";
		break;
	case Gem::GREEN:
		colorFile = "../assets/Green.png";
		break;
	case Gem::PURPLE:
		colorFile = "../assets/Purple.png";
		break;
	default:
		colorFile = "../assets/Yellow.png";
		break;
	}

	return colorFile;
}

void Game::LoadGame(unsigned short gameNumber) {
	SDL_Rect clip = { 0, 0, 0, 0 };
	SDL_Rect pos = { 0, 0, 0, 0 };
	_mGameNumber = gameNumber;
	//_mTimer->SetTime(60); //60 seconds to beat, this could be set when loading the level from file

	unsigned short layout[8][8] = {
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};

	//Load background, it could change according to level number
	pos.x = pos.y = 0;
	pos.w = Background::WIDTH;
	pos.h = Background::HEIGHT;
	_mBackground->SetPos(pos);
	_mBackground->Load("assets/background.jpg");

	//Load rocks, randomize their colors
	pos.w = Gem::GEM_WIDTH;
	pos.h = Gem::GEM_HEIGHT;

	srand((unsigned int)time(NULL));
	for (int row = 0; row < Game::ROWS; row++)
	{
		for (int col = 0; col < Game::COLS; col++)
		{
			//Ensure that at loading time we don't have combos
			unsigned short color = GetRandomColor(col, row);
			const char *colorFile = GetColorFile(color);

			//Position changes dinamically based on x/y position, we add the BG offset and pixel separation
			pos.x = Background::OFFSET_X + (col * Gem::GEM_WIDTH) + (Gem::PIXEL_SEP * col);
			pos.y = Background::OFFSET_Y + (row * Gem::GEM_HEIGHT) + (Gem::PIXEL_SEP * row);

			if (layout[row][col] == 1)
			{
				_mGems[row][col] = new Gem();
				_mGems[row][col]->SetColor(color);
				_mGems[row][col]->SetRenderer(_mRenderer);
				_mGems[row][col]->SetPos(pos);
				_mGems[row][col]->SetRow(row);
				_mGems[row][col]->SetColumn(col);
				_mGems[row][col]->Load(colorFile);
			}
		}
	}
}

void Game::Render() const {
	SDL_RenderClear(_mRenderer);

	//Render background and each visible rock
	_mBackground->Render();

	for (int row = 0; row < Game::ROWS; row++) {
		for (int col = 0; col < Game::COLS; col++) {
			if (_mGems[row][col] != NULL)
				_mGems[row][col]->Render();
		}
	}

	/*_mTextHandler->Render("Score: ", { 10, 100, 0, 0 });
	_mTextHandler->Render(_mScoreString, { 120, 100, 0, 0 });
	_mTextHandler->Render("Time left: ", { 10, 150, 0, 0 });
	_mTextHandler->Render(_mTimer->GetTimeStr(), { 180, 150, 0, 0 });
	*/
	//if (_mState == Level::FINISHED)
		/*_mTextHandler->Render("GAME OVER", { 400, 50, 0, 0 });
		*/
	SDL_RenderPresent(_mRenderer);
}

unsigned short Game::GetGameState() const {
	return _mGameState;
}

void Game::SetState(unsigned short state) {
	_mGameState = state;
}

void Game::Update() {
	switch (_mGameState) {
	case Game::LOADING:
		//_mTimer->Start();
		break;

	case Game::IDLE:
		//_mTimer->Update();
		//if (_mTimer->Finished())
			//_mState = Level::FINISHED;

		if (!_mGemChains.empty() || !_mFallingGems.empty() || !_mNewGems.empty()) {
			_mGameState = Game::PROCESSING;
		}
		break;

	case Game::SWAPPING:
		assert(_mSwap);

		//_mTimer->Update();
		_mSwap->Update();
		if (_mSwap->Done())
		{
			//position animation finished, now swap the actual objects
			SwapGems(_mSwapOriginCol, _mSwapOriginRow, _mSwapDestCol, _mSwapDestRow);

			//Check whether is a valid move (i.e. forms a chain)
			if (IsValidChain(_mSwapOriginCol, _mSwapOriginRow) || IsValidChain(_mSwapDestCol, _mSwapDestRow))
			{
				delete _mSwap;
				_mSwapOriginCol = _mSwapDestCol = -1;
				_mSwapOriginRow = _mSwapDestRow = -1;

				FindHorizontalChains();
				FindVerticalChains();

				_mGameState = Game::PROCESSING;
			}
			else
			{
				_mSwap->RollBack();
				_mGameState = Game::ROLLING_BACK;
			}
		}
		break;

	case Game::ROLLING_BACK:
		assert(_mSwap);

		//_mTimer->Update();
		_mSwap->Update();
		if (_mSwap->Done())
		{
			//position animation finished, now swap the actual objects
			SwapGems(_mSwapOriginCol, _mSwapOriginRow, _mSwapDestCol, _mSwapDestRow);

			delete _mSwap;
			_mSwapOriginCol = _mSwapOriginCol = -1;
			_mSwapDestRow = _mSwapDestRow = -1;

			_mGameState = Game::IDLE;
		}
		break;

	case Game::PROCESSING:
		//_mTimer->Update();
		RemoveGemChains();
		FillRemovedChainsHoles();
		AnimateFallingGems();
		FillTableTop();
		AnimateNewGems();

		if (_mGemChains.empty() && _mFallingGems.empty() && _mNewGems.empty()) {
			_mGameState = END_PROCESSING;
		}
		break;

	case Game::END_PROCESSING:
		//_mTimer->Update();
		//Check if moving rocs produced more chains
		FindHorizontalChains();
		FindVerticalChains();

		//go back to IDLE... 
		//if any chains were created, this state will take care of them
		_mGameState = Game::IDLE;
		break;

	case Game::FINISHED:
		//TODO display final score, load nother texture etc
		//_mTextHandler->SetFontColor({ 200, 0, 0, 255 });
		break;
	}
}

void Game::GetGridCoords(int x, int y, int &row, int &col) const {
	assert(x >= 0 && y >= 0);

	//convert window position into ROW/COL coordinates in our grid
	row = (y - Background::OFFSET_Y) / (Gem::GEM_HEIGHT + Gem::PIXEL_SEP);
	col = (x - Background::OFFSET_X) / (Gem::GEM_WIDTH + Gem::PIXEL_SEP);
}

void Game::OnMouseButtonDown(int x, int y) {
	//On button DOWN we only track swapTo positions
	//we also start a swipe event, later on buttonUp, 
	//we check whether it was a swipe or just a click
	if (_mSwapOriginCol >= 0)
		return;

	_mSwipe = true;

	int row, col;
	GetGridCoords(x, y, row, col);
	if (row >= 0 && row < Game::ROWS && col >= 0 && col < Game::COLS)
	{
		_mSwapOriginCol = col;
		_mSwapOriginRow = row;
	}
}

void Game::OnMouseButtonUp(int x, int y) {
	//On button UP we track swapTo position, 
	//this allows to swap rocks either by clicking or swiping	
	GetGridCoords(x, y, _mSwapDestRow, _mSwapDestCol);

	if (_mSwapDestRow >= 0 && _mSwapDestRow < Game::ROWS && _mSwapDestCol >= 0 && _mSwapDestCol < Game::COLS)
	{
		if (_mGems[_mSwapDestRow][_mSwapDestCol] == NULL || _mGems[_mSwapOriginRow][_mSwapOriginCol] == NULL)
		{
			//empty cell, invalid move
			_mSwapOriginCol = _mSwapOriginRow = -1;
			_mSwapDestCol = _mSwapDestRow = -1;
			_mSwipe = false;
			return;
		}

		//if this is not set, it means previous click was at some invalid position
		if (_mSwapOriginCol >= 0)
		{
			//check that we're not clicking on the same rock as previously clicked
			if (_mSwapOriginCol == _mSwapDestCol && _mSwapOriginRow == _mSwapDestRow)
			{
				//Since we released the mouse in the same position, we're NOT swiping
				_mSwipe = false;
				return;
			}

			//If we're clicking, check that final grid position is valid (+/- 1)
			//If we're swiping, use deltas, it doesn't matter on what position we release the mouse
			//this improves user experience on a touch screen
			int deltaX = _mSwapDestCol - _mSwapOriginCol; //(+) right, (-) left
			int deltaY = _mSwapDestRow- _mSwapOriginRow; //(+) up, (-) down
			int direction = 0;

			if (deltaX != 0 && deltaY != 0)
			{
				//invalid move... 
				_mSwapOriginCol = _mSwapOriginRow = -1;
				_mSwapDestCol = _mSwapDestRow = -1;
				_mSwipe = false;
				return;
			}

			if (deltaY < 0) {
				_mSwapDestRow = _mSwapOriginRow - 1;
				direction = Swap::UP;
			}
			if (deltaY > 0) {
				_mSwapDestRow = _mSwapOriginRow + 1;
				direction = Swap::DOWN;
			}
			if (deltaX < 0) {
				_mSwapDestCol = _mSwapOriginCol - 1;
				direction = Swap::LEFT;
			}
			if (deltaX > 0) {
				_mSwapDestCol = _mSwapOriginCol + 1;
				direction = Swap::RIGHT;
			}

			//Try to swap the gems
			_mGameState = Game::SWAPPING;
			_mSwap = new Swap(_mGems[_mSwapOriginRow][_mSwapOriginCol], _mGems[_mSwapDestRow][_mSwapDestCol]);
			_mSwap->SetDirection((Swap::ValidDirection)direction);
			_mSwipe = false;
		}
	}
	else
	{
		//invalid position, reset swap flags
		_mSwapOriginCol = _mSwapOriginRow = -1;
		_mSwapDestCol = _mSwapDestRow = -1;
		_mSwipe = false;
	}
}

bool Game::IsValidChain(int col, int row) const {
	assert(col >= 0 && row >= 0);

	unsigned short color = _mGems[row][col]->GetColor();
	int hLen = 1;
	int vLen = 1;

	//check for horizontal chains
	//while gem is not null and its color is equal to matching color, increment hLen or vLen
	for (int i = col - 1; i >= 0 && _mGems[row][i] && _mGems[row][i]->GetColor() == color; i--, hLen++);
	for (int i = col + 1; i < Game::COLS && _mGems[row][i] && _mGems[row][i]->GetColor() == color; i++, hLen++);
	if (hLen >= 3) return true;

	//check for vertical chains
	for (int i = row - 1; i >= 0 && _mGems[i][col] && _mGems[i][col] && _mGems[i][col]->GetColor() == color; i--, vLen++);
	for (int i = row + 1; i < Game::ROWS && _mGems[i][col] && _mGems[i][col]->GetColor() == color; i++, vLen++);
	return (vLen >= 3);
}

void Game::SwapGems(int fromX, int fromY, int toX, int toY) {
	assert(fromX >= 0 && fromY >= 0);
	assert(toX >= 0 && toY >= 0);

	//Change rock's row/col pairs
	_mGems[fromY][fromX]->SetColumn(toX);
	_mGems[fromY][fromX]->SetRow(toY);
	_mGems[toY][toX]->SetColumn(fromX);
	_mGems[toY][toX]->SetRow(fromY);

	//Now, update our grid, since we have moved rock objects around
	Gem* rockOrigin = _mGems[fromY][fromX];
	Gem* rockDest = _mGems[toY][toX];
	_mGems[fromY][fromX] = rockDest;
	_mGems[toY][toX] = rockOrigin;
}

void Game::RemoveGemChains() {
	for (size_t chain = 0; chain < _mGemChains.size(); chain++)
	{
		_mHasHoles = true;
		vector<Gem*> gemsArr = _mGemChains[chain].GetGems();

		for (size_t i = 0; i < gemsArr.size(); i++) {
			_mGems[gemsArr[i]->GetRow()][gemsArr[i]->GetColumn()] = NULL;
		}
	}

	if (!_mGemChains.empty())
		_mGemChains.clear();
}

void Game::FillRemovedChainsHoles() {
	if (!_mHasHoles)
		return;

	//since we're filling holes, we're going to have to push new rocks on top
	_mRefillTop = true;

	for (int col = 0; col < Game::COLS; col++)
	{
		//scan bottom-up for holes
		for (int row = Game::ROWS - 1; row >= 0; row--)
		{
			if (_mGems[row][col] == NULL)
			{
				//found a hole, lookup the next gem upwards
				for (int lookup = row - 1; lookup >= 0; lookup--)
				{
					Gem *gem = _mGems[lookup][col];
					if (gem != NULL)
					{
						//push down the rock
						gem->SetRow(row);
						_mGems[lookup][col] = NULL;
						_mGems[row][col] = gem;
						//add to an array that will be used for animation later
						_mFallingGems.push_back(gem);
						break;
					}
				}
			}
		}
	}

	_mHasHoles = false;
}

void Game::AnimateFallingGems() {
	for (size_t i = 0; i < _mFallingGems.size(); i++) {
		//get each rock in the array and calclate its new position
		//update their positions by 5 pixels, when a rock reaches
		//its destination, delete it from the array
		Gem *gem = _mFallingGems[i];
		int finalY = Background::OFFSET_Y + (gem->GetRow() * Gem::GEM_HEIGHT) + (Gem::PIXEL_SEP * gem->GetRow());

		SDL_Rect pos = { gem->GetPos().x, gem->GetPos().y + 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
		gem->SetPos(pos);

		if (gem->GetPos().y == finalY)
			_mFallingGems.erase(_mFallingGems.begin() + i);
	}
}

void Game::FillTableTop() {
	if (!_mRefillTop)
		return;

	for (int col = 0; col < Game::COLS; col++) {
		for (int row = 0; row < Game::ROWS && _mGems[row][col] == NULL; row++) {
			int x = Background::OFFSET_X + (col * Gem::GEM_HEIGHT) + (Gem::PIXEL_SEP * col);
			SDL_Rect pos = { x, 0, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };

			unsigned short color = GetRandomColor(col, row);
			const char *colorFile = GetColorFile(color);

			Gem* gem = new Gem();
			gem->SetColor(color);
			gem->SetColumn(col);
			gem->SetRow(row);
			gem->SetPos(pos);
			gem->SetRenderer(_mRenderer);
			gem->Load(colorFile);
			_mGems[row][col] = gem;
			_mNewGems.push_back(gem);
		}
	}

	_mRefillTop = false;
}

void Game::AnimateNewGems() {
	for (size_t i = 0; i < _mNewGems.size(); i++) {
		//get each gem in the array and calclate its new position
		//update their positions by 5 pixels, when a rock reaches
		//its destination, delete it from the array
		Gem *gem = _mNewGems[i];
		int finalY = Background::OFFSET_Y + (gem->GetRow() * Gem::GEM_HEIGHT) + (Gem::PIXEL_SEP * gem->GetRow());

		SDL_Rect pos = { gem->GetPos().x, gem->GetPos().y + 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
		gem->SetPos(pos);

		if (gem->GetPos().y == finalY)
			_mNewGems.erase(_mNewGems.begin() + i);
	}
}

void Game::FindHorizontalChains() {
	for (int row = 0; row < Game::ROWS; row++) {
		//Don't need to check the last 2 columns, we could get out of bounds
		for (int col = 0; col < Game::COLS - 2;) {
			//check that coordinate has a valid rock
			if (_mGems[row][col] != NULL) {
				//get current rock color to match neighbors' color
				unsigned short matchColor = _mGems[row][col]->GetColor();

				if (_mGems[row][col + 1] &&
					_mGems[row][col + 1]->GetColor() == matchColor &&
					_mGems[row][col + 2] &&
					_mGems[row][col + 2]->GetColor() == matchColor) {
					//So we have at least 3 with the same color
					//create a chain object and fill it with Rocks
					GemChain chain;
					chain.SetValidChain(GemChain::HORIZONTAL);

					unsigned int count = 0;
					do {
						chain.AddGem(_mGems[row][col]);
						col++;
						count++;
					} while (col < Game::COLS && _mGems[row][col] && _mGems[row][col]->GetColor() == matchColor);

					UpdateScore(count);
					_mGemChains.push_back(chain);
				}
			}
			col++;
		}
	}
}

void Game::FindVerticalChains() {
	for (int col = 0; col < Game::COLS; col++) {
		//Don't need to check the last 2 rows, we could get out of bounds
		for (int row = 0; row < Game::ROWS - 2;) {
			//check that coordinate has a valid rock
			if (_mGems[row][col] != NULL) {
				//get current rock color to match neighbors' color
				unsigned short matchColor = _mGems[row][col]->GetColor();

				if (_mGems[row + 1][col] &&
					_mGems[row + 1][col]->GetColor() == matchColor &&
					_mGems[row + 2][col] &&
					_mGems[row + 2][col]->GetColor() == matchColor) {
					//So we have at least 3 with the same color
					//create a chain object and fill it with Rocks
					GemChain chain;
					chain.SetValidChain(GemChain::VERTICAL);

					unsigned int count = 0;
					do {
						chain.AddGem(_mGems[row][col]);
						row++;
						count++;
					} while (row < Game::ROWS && _mGems[row][col] && _mGems[row][col]->GetColor() == matchColor);

					UpdateScore(count);
					_mGemChains.push_back(chain);
				}
			}
			row++;
		}
	}
}

void Game::UpdateScore(unsigned int count) {
	if (count == 3)
		_mScore += Game::CHAIN3;
	else if (count == 4)
		_mScore += Game::CHAIN4;
	else if (count >= 5)
		_mScore += Game::CHAIN5+

	_itoa_s(_mScore, _mScoreString, 10, 10);
}