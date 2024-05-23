#include <Enemigo.hpp>
#include <Magias.hpp>
#include <iostream>
EnemigoFinal::EnemigoFinal(string nombre, int ataque, int vida) :Personaje(nombre, ataque, vida) {
	this->hechizos = 1 + rand() % 5;
}

void EnemigoFinal::hechizar(int magia, Personaje victima) {
	if (this->hechizos > 5) {
		if (victima.getEstado() == NORMAL) {
			victima.setEstado(NORMAL);
			
		}
		victima.setEstado(magia);
		victima.setEstado(magia );
		
		this->hechizos--;
	}
	else {
		std::cout << "No tengo hechizos" << endl;
	}
}



