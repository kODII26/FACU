#include "ZonaPuntos.h"
#include <SFML/Graphics/Texture.hpp>
using namespace sf;

ZonaPuntos::ZonaPuntos(Texture &text) : Objeto(-1) {
	m_s.setTexture(text);
	m_s.setScale(0.01,0.01);
	int aleatorio = 150+rand()%(490-150+1);
	m_s.setPosition(aleatorio,0);
}

void ZonaPuntos::Actualizar() {
	m_s.move(0,1);
}


void ZonaPuntos::Dibujar (RenderWindow & window) {
	window.draw(m_s);
}

bool ZonaPuntos::CollideWith ( Objeto o) const {
	auto r1 = m_s.getGlobalBounds();
	auto r2 = o.verSprite().getGlobalBounds();
	return r1.intersects(r2);
}

