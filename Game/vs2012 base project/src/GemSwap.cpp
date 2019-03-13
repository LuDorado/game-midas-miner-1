#include "GemSwap.h"
//el constructor recibe dos parametros de tipo puntero a la clase Gem 

Swap::Swap(Gem * A, Gem * B)
{
	assert(A && B);
	//asigna las variables con los valores recibidos por parametro punteros
	_mA = A;
	_mB = B;
	//_destA recibe la posicion de _mB
	_destA = _mB->GetPos();//GetPos() es el metodo para obtener la posicion de la Gema importado desde la calse Gem..
	//_destB recibe la posicion de _mA
	_destB = _mA->GetPos();
	//asigna los valores privados
	_mDone = false;
	_mInvalid = false;
}
//definicion del destructor
Swap::~Swap()
{
	_mA = NULL;
	_mB = NULL;
}


void Swap::SetDirection(enum ValidDirection d)
{
	_mDirection = d;
}

bool Swap::Done()
{
	return _mDone;
}

bool Swap::RollingBack()
{
	return _mInvalid;
}

//vuelve las Gemas a su posicion original
void Swap::RollBack()
{
	assert(_mA && _mB);
	//switch
	Gem* aux = _mA;
	_mA = _mB;
	_mB = aux;
	//posiciones
	_destA = _mB->GetPos();
	_destB = _mA->GetPos();
	_mDone = false;
	_mInvalid = true;
}

// WTF!?..no mentira..Si A se mueve a la derecha, B se mueve hacia la izquierda 
//para izquierda y derecha modifica el eje X.
//para arriba y abajo modifica el eje Y.
//toma el 5 como constante independiente por que es la cantidad de gemas.

void Swap::Update()
{
	assert(_mA && _mB);

	if (!_mDone)
	{
		SDL_Rect posA, posB;

		switch (_mDirection)
		{
		case Swap::UP:
			posA = { _mA->GetPos().x, _mA->GetPos().y - 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			posB = { _mA->GetPos().x, _mA->GetPos().y + 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			break;
		case Swap::DOWN:
			posA = { _mA->GetPos().x, _mA->GetPos().y + 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			posB = { _mA->GetPos().x, _mA->GetPos().y - 5, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			break;
		case Swap::LEFT:
			posA = { _mA->GetPos().x - 5, _mA->GetPos().y, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			posB = { _mB->GetPos().x + 5, _mB->GetPos().y, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			break;
		case Swap::RIGHT:
			posA = { _mA->GetPos().x + 5, _mA->GetPos().y, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			posB = { _mB->GetPos().x - 5, _mB->GetPos().y, Gem::GEM_WIDTH, Gem::GEM_HEIGHT };
			break;
		}
		//asigna las posiciones
		_mA->SetPos(posA);
		_mB->SetPos(posB);

		//condicional para asegurar que la gema alcanzó su destino que le corresponde 
		if (_mA->GetPos().x == _destA.x && _mA->GetPos().y == _destA.y)
			_mDone = true;
	}

}




