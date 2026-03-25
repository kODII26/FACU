#ifndef ZONAPUNTOS_H
#define ZONAPUNTOS_H
#include "Objeto.h"
#include <SFML/System/Clock.hpp>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace std;

class ZonaPuntos {
public:
	ZonaPuntos();
	void Actualizar();
	bool debeGenerar();
	ZonaPuntos GenerarZona();
	Vector2f verPosicion() { return m_sprite.getPosition(); 
private:
	Objeto m_zona;
};

#endif

