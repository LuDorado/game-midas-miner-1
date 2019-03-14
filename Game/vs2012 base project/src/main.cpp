#define GLM_FORCE_RADIANS 

#include <king/Engine.h>
#include <king/Updater.h>

#include "../external/include/sdl/SDL.h"
#include "../headers/Game.h"
#include "../headers/Background.h"
#include "../headers/Gem.h"
#include "../headers/WindowHandler.h"

using namespace std;

int main(int argc, char* args[])
{
	WindowHandler *myWindow = new WindowHandler(800, 600);
	Game *myGame = new Game(myWindow->GetRenderer());
	myGame->SetState(Game::LOADING);
	myGame->LoadGame(1);
	myGame->SetState(Game::IDLE);

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		//Process user input
		while ((myGame->GetGameState() == Game::IDLE ||
			myGame->GetGameState() == Game::FINISHED) &&
			SDL_PollEvent(&event))
		{
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (myGame->GetGameState() == Game::IDLE)
					myGame->OnMouseButtonDown(event.button.x, event.button.y);
				break;
			case SDL_MOUSEBUTTONUP:
				if (myGame->GetGameState() == Game::IDLE)
					myGame->OnMouseButtonUp(event.button.x, event.button.y);
				break;
			}//switch
		}//while SDL_PollEvents

		//Perform animations or update objects positions
		myGame->Update();

		//Draw next frame		
		myGame->Render();
	}//while !quit

	delete myGame;
	delete myWindow;

	return 0;
}

//**********************************************************************

/*class Gem : public King::Updater {
public:
	Gem() {};
	~Gem() {};
	
	void Draw() {
		mEngine.Render(TEXTURE_PURPLE, 200.0f, 100.0f);
	}

private:
	unsigned short _mColor;
};

class ExampleGame : public King::Updater {
public:

	ExampleGame()
		: mEngine("./assets")
		, mRotation(0.0f)
		, mYellowDiamondX(100.0f)
		, mYellowDiamondY(100.0f) {
	}

	void Start() {
		mEngine.Start(*this);
	}

	void Update() {
		mEngine.Render(King::Engine::TEXTURE_GREEN, 650.0f, 100.0f);
		mEngine.Render(King::Engine::TEXTURE_RED, 100.0f, 450.0f);
		mEngine.Render(King::Engine::TEXTURE_BLUE, 650.0f, 450.0f);

		mEngine.Write("Green", 650.0f, 140.0f);
		mEngine.Write("Red", 100.0f, 490.0f);
		mEngine.Write("Blue", 650.0f, 490.0f);

		const char text[] = "This rotates at 5/PI Hz";
		mRotation += mEngine.GetLastFrameSeconds();
		mEngine.Write(text, mEngine.GetWidth() / 2.0f, mEngine.GetHeight() / 2.0f, mRotation * 2.5f);

		/*if (mEngine.GetMouseButtonDown()) {
			mYellowDiamondX = mEngine.GetMouseX();
			mYellowDiamondY = mEngine.GetMouseY();
		}

		mEngine.Render(King::Engine::TEXTURE_YELLOW, mYellowDiamondX, mYellowDiamondY);
		mEngine.Write("Click to", mYellowDiamondX, mYellowDiamondY + 40.0f);
		mEngine.Write("move me!", mYellowDiamondX, mYellowDiamondY + 70.0f

	}

private:
	King::Engine mEngine;
	float mRotation;
	float mYellowDiamondX;
	float mYellowDiamondY;
	float mPurpleDiamondX;
	float mPurpleDiamondY;
};

//**********************************************************************

int main(int argc, char *argv[]) {
	ExampleGame game;
	game.Start();

	return 0;
}*/


