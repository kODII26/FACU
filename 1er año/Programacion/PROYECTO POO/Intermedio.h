#ifndef INTERMEDIO_H
#define INTERMEDIO_H
#include "Juego.h"
#include "Escena.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Partida.h"

class Intermedio : public Escena{
public:
	Intermedio(infoPlayer i);
	void EvaluarEvento(Juego &game, Event &event) override;
	void Actualizar(Juego &game) override;
	void Dibujar(RenderWindow &window) override;
private:
	Text m_t1, m_t2, m_t3;
	infoPlayer m_infoP;
};

#endif

