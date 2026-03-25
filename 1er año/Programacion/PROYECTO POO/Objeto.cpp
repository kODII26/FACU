#include "Objeto.h"
using namespace sf;


Objeto::Objeto(int num) {
	m_tex_enemy.loadFromFile("Recursos/NaveEnemiga.png");
	m_tex_player.loadFromFile("Recursos/NavePlayer.png");
	if (num==1) {
		m_sprite.setTexture(m_tex_enemy);
	}
	if (num==2) {
		m_sprite.setTexture(m_tex_player);
	}
	
}

void Objeto::Dibujar(RenderWindow &window) {
	window.draw(m_sprite);
}

bool Objeto::CollideWith(const Objeto & o) const {
	auto r1 = this->m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	return r1.intersects(r2);
}
