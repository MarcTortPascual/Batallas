#pragma once
#include <string>
using namespace std;
class Personaje
{
	protected:
		int x, y;
		const int maxvida;
		int vida, ataque;
		string nombre;
		int estado;
		bool protegido;
	public:
		Personaje(string nombre, int ataque, int vida);
		void getPos(int* x, int* y);
		int getAtque();
		int getMaxVida();
		int getVida();
		string getNombre();
		int getEstado();
		void setEstado(int estado);
		void setPos(int x, int h);
		void setAtque(int a);
		void setVida(int v);
		void atacar (Personaje *victima);
			

};

