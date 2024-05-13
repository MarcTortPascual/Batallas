#pragma once
#include <string>
using namespace std;
class Personaje
{
	private:
		int x, y;
		int vida, ataque,maxvida;
		string nombre;
		int estado;
		bool protegido;
	public:
		Personaje(string nombre, int ataque, int vida);
		void getPos(int* x, int* y);
		int getAtque();
		int getVida();
		string getNombre();
		void setPos(int x, int h);
		void setAtque(int a);
		void setVida(int v);
		void operator - (Personaje victima);
			

};

