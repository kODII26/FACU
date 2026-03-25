#include <SFML/Graphics.hpp>
#include "Juego.h"
#include "Menu.h"
using namespace sf;

Juego::Juego() : m_window(VideoMode(640,480),"Juego_Nave Espacial") {
	m_window.setFramerateLimit(60);
	
	m_esc = new Menu();
}

void Juego::Jugar() {
	while(m_window.isOpen()) {
		EvaluarEvento();
		Actualizar();
		Dibujar();	
		if (m_next_esc != nullptr) {
			delete m_esc;
			m_esc = m_next_esc;
			m_next_esc = nullptr;
		}
	}
}

void Juego::Actualizar() {
	m_esc-> Actualizar(*this);
}

void Juego::Dibujar() {
	m_esc->Dibujar(m_window);
}


void Juego::EvaluarEvento() {
	Event e;
	while(m_window.pollEvent(e)) {
		if(e.type == Event::Closed){
			m_window.close();	
		}
		
	}
}

void Juego::CambiarEscena (Escena * next_esc) {
	m_next_esc = next_esc;
}

