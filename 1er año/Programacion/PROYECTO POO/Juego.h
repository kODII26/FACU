#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Escena.h"
#include "Partida.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
using namespace sf;

class Juego {
public:
	Juego();
	void Jugar();
	void EvaluarEvento();
	void Actualizar();
	void Dibujar();
	void CambiarEscena(Escena *next_esc);
	void Salir();
private:
	RenderWindow m_window;
	Escena *m_esc;
	Escena *m_next_esc = nullptr;	Music m_music;
	
};

#endif

