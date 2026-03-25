#include "Intermedio.h"
#include "Partida.h"

using namespace std;

Intermedio::Intermedio(infoPlayer i) {
	m_infoP= i;
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	
	m_t1.setString("NIVEL DOS");
	m_t1.setFillColor ({155,155,155});
	m_t1.setPosition(120,30);
	m_t1.setCharacterSize(50);
	
	m_t2.setString("-presione Space para comenzar a jugar-");
	m_t2.setPosition(90,190);
	m_t2.setCharacterSize(14);
	
	m_t3.setString("Are you ready?");
	m_t3.setPosition(200,140);
	m_t3.setFillColor ({155,155,155});
	m_t3.setCharacterSize(20);
}

void Intermedio::Actualizar (Juego & game) {
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t2.setFillColor({r,g,b});
	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
		game.CambiarEscena(new Partida(m_infoP,2));
	
}

void Intermedio::Dibujar (RenderWindow & window) {
	window.clear({0,0,0});
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	window.display();
}

void Intermedio::EvaluarEvento (Juego & game, Event & event) {
	
}

