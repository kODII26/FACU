#include "Enemigo.h"
#include "Objeto.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

Enemigo::Enemigo(): Objeto("NaveEnemiga.png") {
	m_sprite.setScale(0.5,0.5);
	m_sprite.setPosition(150,0);
}

void Enemigo::Actualizar() {
	m_sprite.move(m_speed);
	auto p = m_sprite.getPosition();
	if (p.x<0 || p.x+250>640)
		m_speed.x = -1*m_speed.x;
	if (p.y<0 || p.y+20>640)
		m_speed.x *= -1;
	generarDisparo();
}

bool Enemigo::debeDisparar() {
	if( m_clock.getElapsedTime().asMilliseconds()<400) return false;
	m_clock.restart();
	return true;
}

Disparo Enemigo::generarDisparo() {
	Vector2f p = m_sprite.getPosition();
	Vector2f d(0,1);
	return Disparo(p,d,m_num);
}

