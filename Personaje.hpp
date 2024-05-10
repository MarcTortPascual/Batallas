#pragma once
#include <iostream>
#include <string>
#include "Magias.h"
using namespace std;
class Personaje
{
	private:
		int x, y;
		int vida, ataque;
		string nombre;
		int estado;
	public:
		Personaje(string nombre, int ataque, int vida);
		void getPos(int* x, int* y);
		void getEstado(int* efecto, bool* paralizado, int*  danioxturno);
		void setEstado(int efecto, bool paralizado, int danioxturno);
		int getAtque();
		int getVida();
		void setPos(int x, int h);
		void setAtque(int a);
		void setVida(int v);
		void operator - (Personaje victima);
			

};

