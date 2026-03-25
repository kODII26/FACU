#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Escena.h"
#include "Partida.h"
using namespace sf;

class Juego {
public:
	Juego();
	void Jugar();
	void EvaluarEvento();
	void Actualizar();
	void Dibujar();
	void CambiarEscena(Escena *next_esc);
private:
	RenderWindow m_window;
	Escena *m_esc;
	Escena *m_next_esc = nullptr;
	Partida m_part;
};

#endif

