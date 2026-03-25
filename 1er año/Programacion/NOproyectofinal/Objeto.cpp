#include "Objeto.h"
using namespace sf;

Objeto::Objeto(std::string fname) {
	m_texture.loadFromFile(fname);
	m_sprite.setTexture(m_texture);
}

void Objeto::Dibujar(RenderWindow &window) {
	window.draw(m_sprite);
}

bool Objeto::CollideWith(const Objeto & o) const {
	auto r1 = this->m_sprite.getGlobalBounds();
	auto r2 = o.m_sprite.getGlobalBounds();
	return r1.intersects(r2);
}
