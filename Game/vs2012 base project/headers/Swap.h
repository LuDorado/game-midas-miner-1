#pragma once

#include <SDL.h>
#include <cassert>
#include "Gem.h"

class Swap
{
public:
	 
	static enum Direccion
	{
		IZQUIERDA, 
		DERECHA,
		ARRIBA,
		ABAJO
	};
	//constructor
	Swap(Gem* A, Gem* B);
	//destructor
	~Swap();
	//metodos
	void SetDireccion(enum Direccion d);
	void RollBack();
	void Update();
	void RollingBack();
	bool Done();

private:
	//datos
	Gem* _mA;//puntros a gema 
	Gem* _mB;
	SDL_Rect _destA; 
	SDL_Rect _destB;
	bool _mDone;
	bool _mInvalid;
	enum Direccion _mDireccion;
};

