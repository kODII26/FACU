#ifndef DISPARO_H
#define DISPARO_H
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

class Disparo {
public:
	Disparo(Vector2f pos,Vector2f dir,int num);
	void Actualizar();
	void Dibujar(RenderWindow &w);
	Vector2f verPosicion();
private:
	Sprite m_sprite;
	CircleShape m_circ;
	Vector2f m_vel;
	int m_num;
};

#endif

