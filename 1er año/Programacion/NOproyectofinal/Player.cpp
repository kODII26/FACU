#include "Player.h"
#include "Objeto.h"

Player::Player() : Objeto("NavePlayer.png") {
	m_sprite.setScale(0.3,0.3);
	m_sprite.setPosition(150,400);
	der = Keyboard::Right;
	izq = Keyboard::Left;
	acel = Keyboard::Up;
	fren = Keyboard::Down;
}

Vector2f Player:: verPosicion() {
	Vector2f pos = m_sprite.getPosition();
	pos.x += 50;
	pos.y += 10;
	return pos;
}

void Player::Actualizar(Player &n) {
	Vector2f p = n.verPosicion();
	
	if(Keyboard::isKeyPressed(der) and p.x<640-150)
		m_sprite.move(3,0);
	if(Keyboard::isKeyPressed(izq) and p.x>0+150)
		m_sprite.move(-3,0);
	
	
	if(Keyboard::isKeyPressed(acel) and p.y>0+100) 
		m_sprite.move(0,-3);
	if(Keyboard::isKeyPressed(fren) and p.y<480) 
		m_sprite.move(0,3);
	
}

void Player::CalcularPuntos() {
	m_puntos += 0.1;
}

float* Player::ObtenerPunt() {
	float *puntero_puntos = &m_puntos;
	return puntero_puntos;
}
