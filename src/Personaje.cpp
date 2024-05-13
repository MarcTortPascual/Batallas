#include <Personaje.hpp>
#include <Magias.hpp>
#include <iostream>
Personaje::Personaje(string nombre, int ataque, int vida)
{
	this->nombre = nombre;
	this->ataque = ataque;
	this->vida = vida;
	this->maxvida = vida;
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

string Personaje::getNombre()
{
	return this->nombre;
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
	if (this->estado & NORMAL ) {
		victima.setVida(victima.getVida() - this->ataque);
	}
	if (this->estado & QUEMADO) {
		//dañado por fuego
		victima.setVida(victima.getVida() - 3);
		//daño normal
		victima.setVida(victima.getVida() - this->ataque);
	}
	if (this->estado & CONFUSO) {
		//daño x confusión
		victima.setVida(victima.getVida() - victima.getAtque());
	}
}
