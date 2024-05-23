#pragma once
#include "Personaje.hpp"
class EnemigoFinal: public Personaje
{
private:
	int hechizos;
	
public:
	EnemigoFinal(string nombre, int ataque, int vida);
	void hechizar(int magia, Personaje victima);
	int getHechizos();
};

