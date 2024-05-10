#pragma once
#include "Personaje.hpp"
enum magias { QUEMADO=1,PARALIZADO,CONFUNDIDO };
class EnemigoFinal: public Personaje
{
private:
	int hechizos;
	Magias confusion;
	Magias paralizar;
	Magias quemar;
public:
	EnemigoFinal(string nombre, int ataque, int vida) :Personaje(nombre, ataque, vida);
	void operator>> (Personaje victima);
};

