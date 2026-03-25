#ifndef NIVELES_H
#define NIVELES_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Player.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;
class Niveles {
public:
	Niveles();
	void cargarNivel(int n);
	void dibujarNivel(RenderWindow &win,Player j, int n);
private:
	Texture m_fondo;
	Sprite m_s_fondo;
	Texture m_fondo2;
};

#endif

