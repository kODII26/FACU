#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Escena.h"
using namespace sf;

class Menu : public Escena {
public:
	Menu();
	void Actualizar(Juego &game) override;
	void Dibujar(RenderWindow &window) override;
private:
	Font m_font;
	Text m_t1, m_t2;
};

#endif


