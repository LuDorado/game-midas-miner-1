// LogHandler implementation

#pragma once
#include "../external/include/sdl/SDL.h"
#include <iostream>

using namespace std;

class LogHandler
{
public:
	LogHandler();
	~LogHandler();

	static void LogError(const char* msg) {
		cout << msg << ": " << SDL_GetError() << endl;
	}

};