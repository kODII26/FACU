#ifndef ZONAPUNTOS_H
#define ZONAPUNTOS_H
#include "Objeto.h"
#include <SFML/System/Clock.hpp>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
using namespace std;

class ZonaPuntos : public Objeto {
public:
	ZonaPuntos(Texture &text);
	void Actualizar();
	Vector2f verPosicion() { return m_s.getPosition(); }
	void Dibujar(RenderWindow &window);
	bool CollideWith(Objeto o) const;
private:
	Clock m_clock;
	Sprite m_s;
};

#endif

