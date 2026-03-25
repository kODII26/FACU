#ifndef ESCENA_H
#define ESCENA_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Juego;

class Escena {
public:
	Escena();
	virtual void EvaluarEvento(Juego &game, Event &event) {} 
	virtual void Actualizar(Juego &game) = 0;
	virtual void Dibujar(RenderWindow &window) = 0;
protected:
	Font m_font, m_font2;
};

#endif


