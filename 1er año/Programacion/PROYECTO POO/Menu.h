#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Escena.h"
#include "InputText.hpp"
#include <SFML/Audio/Music.hpp>
#include "Partida.h"
using namespace sf;

class Menu : public Escena {
public:
	Menu();
	void EvaluarEvento(Juego &game, Event &event) override;
	void Actualizar(Juego &game) override;
	void Dibujar(RenderWindow &window) override;
private:
	Text m_t1, m_t2, m_t3,m_t4;
	InputText m_inputName;
	infoPlayer m_p;
	
};

#endif


