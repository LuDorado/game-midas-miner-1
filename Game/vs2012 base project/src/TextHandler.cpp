#include "../headers/TextHandler.h"

TextHandler::TextHandler(SDL_Renderer *r, unsigned short fontSize)
{
	_mRenderer = r;
	_mFontSize = fontSize;
	_mColor = { 255, 255, 255, 255 }; //white color

	//Initialize TTF SDL engine
	if (TTF_Init() != 0)
	{
		LogHandler::LogError("TTF_Init error");
		SDL_Quit();
		return;
	}

	//Try to open the font
	_mFont = TTF_OpenFont("assets/font.ttf", _mFontSize);
	if (_mFont == NULL)
	{
		LogHandler::LogError("Error opening TTF Font");
		SDL_Quit();
		return;
	}
}

TextHandler::~TextHandler()
{
	TTF_CloseFont(_mFont);
	SDL_FreeSurface(_mSurface);
	SDL_DestroyTexture(_mTexture);
}

void TextHandler::SetFontColor(SDL_Color color)
{
	_mColor = color;
}

void TextHandler::Render(const char *msg, SDL_Rect pos)
{
	_mSurface = TTF_RenderText_Blended(_mFont, msg, _mColor);

	if (_mSurface == NULL)
	{
		TTF_CloseFont(_mFont);
		LogHandler::LogError("Error rendering TTF text");
		return;
	}

	_mTexture = SDL_CreateTextureFromSurface(_mRenderer, _mSurface);
	if (_mTexture == NULL)
	{
		LogHandler::LogError("Error creating TTF texture");
		return;
	}

	SDL_QueryTexture(_mTexture, NULL, NULL, &pos.w, &pos.h);
	SDL_RenderCopy(_mRenderer, _mTexture, NULL, &pos);
}