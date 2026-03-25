#include "Disparo.h"
#include <SFML/System/Vector2.hpp>

Disparo::Disparo(Vector2f pos,Vector2f dir, int num) {
	pos.x += 120;
	pos.y += 90;
	m_circ.setPosition(pos);
	m_circ.setRadius(4);
	m_circ.setOrigin(2,2);
	m_circ.setFillColor({225,0,0});
	m_vel = dir*3.f;//3 pixeles por frame
}

void Disparo::Actualizar () {
	m_circ.move(m_vel);	
}

void Disparo::Dibujar(RenderWindow &w) {
	w.draw(m_circ);
}

Vector2f Disparo::verPosicion(){
	Vector2f pos = m_circ.getPosition(); 
	return pos;
}
