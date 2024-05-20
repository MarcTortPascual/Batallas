#include <Personaje.hpp>
#include <Magias.hpp>
Personaje::Personaje(string nombre, int ataque, int vida):maxvida(vida)
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

int Personaje::getMaxVida()
{
	return this->maxvida;
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
int Personaje::getEstado() { return this->estado; }
void Personaje::setEstado(int estado) {
	this->estado = estado;
}
void Personaje::operator-(Personaje victima)
{
	if (victima.getEstado() & NORMAL) {
		victima.setVida(victima.getVida() - this->ataque);
	}
	if (victima.getEstado() & QUEMADO) {
		//dañado por fuego
		victima.setVida(victima.getVida() - 3);
		//daño normal
		victima.setVida(victima.getVida() - this->ataque);
	}
	if (victima.getEstado() & CONFUSO) {
		//daño x confusión
		victima.setVida(victima.getVida() - victima.getAtque());
	}
}
