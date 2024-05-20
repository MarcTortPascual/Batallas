objects = $(shell ls ./*.o)
Include = -I../include 
lib = -lSDL2 -lSDL2_image -lSDL2_ttf 
Boton.o:../src/Boton.cpp
	g++ -c ../src/Boton.cpp $(Include)
main.o:../src/main.cpp
	g++ -c ../src/main.cpp $(Include)
Personaje.o:../src/Personaje.cpp
	g++ -c ../src/Personaje.cpp $(Include)
Enemigo.o:../src/Enemigo.cpp
	g++ -c ../src/Enemigo.cpp $(Include)
all:Boton.o main.o Personaje.o Enemigo.o 
	g++ -o ../release/Batalla.out $(objects) $(lib)
clear:
	rm -r $(objects)
