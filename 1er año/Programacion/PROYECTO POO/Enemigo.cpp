#include "Enemigo.h"
#include "Objeto.h"
#include <SFML/Graphics/Sprite.hpp>
using namespace sf;

Enemigo::Enemigo(): Objeto(1) {
	m_sprite.setScale(0.5,0.5);
	m_sprite.setPosition(150,0);
}

void Enemigo::Actualizar(int n_actual) {
	if (n_actual==1){
		m_sprite.move(m_speed);
		auto p = m_sprite.getPosition();
		if (p.x<0 || p.x+250>640)
			m_speed.x = -1*m_speed.x;
		if (p.y<0 || p.y+20>640)
			m_speed.x *= -1;
		generarDisparo();
	}
	if (n_actual==2){
		m_sprite.move(m_speed2);
		auto p = m_sprite.getPosition();
		if (p.x<0 || p.x+250>640)
			m_speed2.x = -1*m_speed2.x;
		if (p.y<0 || p.y+20>640)
			m_speed2.x *= -1;
		generarDisparo();
	}
}

bool Enemigo::debeDisparar(int n_actual) {
	if( m_clock.getElapsedTime().asMilliseconds()<400/(n_actual*0.8)) return false;
	m_clock.restart();
	return true;
}

Disparo Enemigo::generarDisparo() {
	Vector2f p = m_sprite.getPosition();
	Vector2f d(0,1);
	return Disparo(p,d,m_num);
}

