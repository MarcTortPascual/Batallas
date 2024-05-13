#include <Personaje.hpp>
#include <Magias.hpp>
Personaje::Personaje(string nombre, int ataque, int vida)
{
	this->nombre = nombre;
	this->ataque = ataque;
	this->vida = vida;
	this->estado = NORMAL;
}

void Personaje::getPos(int* x, int* y)
{
	*(x) = this->x;
	*(y) = this->y;
}


int Personaje::getAtque()
{
	return this->ataque;
}

int Personaje::getVida()
{
	return this->vida;
}

void Personaje::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

void Personaje::setAtque(int a)
{
	this->ataque = a;
}

void Personaje::setVida(int v)
{
	this->vida = v;
}

void Personaje::operator-(Personaje victima)
{
	switch (this->estado)
	{
	default:
		break;
	}
	
}
