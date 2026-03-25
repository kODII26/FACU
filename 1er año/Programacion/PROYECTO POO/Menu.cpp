#include "Menu.h"
#include "Juego.h"
#include <SFML/Window/Keyboard.hpp>
#include "Partida.h"
#include <iostream>

using namespace std;
using namespace sf;

Menu::Menu() {
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font2);
	m_t4.setFont(m_font);
	
	m_t1.setString("Nave Espacial!!!");
	m_t1.setPosition(65,30);
	m_t1.setCharacterSize(43);
	
	m_t2.setString("-presione Space para comenzar a jugar-");
	m_t2.setPosition(90,100);
	m_t2.setCharacterSize(14);
	
	m_t4.setString("-presione ESC para salir-");
	m_t4.setPosition(160,120);
	m_t4.setCharacterSize(14);
	
	m_t3.setString("Ingrese su nombre:");
	m_t3.setFillColor({150,150,150});
	m_t3.setPosition(30,400);
	m_t3.setCharacterSize(20);
	
	m_inputName.setFont(m_font2);
	m_inputName.setFillColor({150,150,150});
	m_inputName.setPosition(340,400); 
	m_inputName.setCharacterSize(20);
	m_inputName.setMaxChars(10);
	

}

void Menu::Actualizar (Juego &game) {
	m_inputName.update();
	m_p.nombre=m_inputName.getValue();
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t1.setFillColor({r,g,b});
	m_t2.setFillColor({r,g,b});
	m_t4.setFillColor({r,g,b});
	if (Keyboard::isKeyPressed(Keyboard::Key::Space))
		game.CambiarEscena(new Partida(m_p,1));
	
}

void Menu::Dibujar (RenderWindow & window) {
	window.clear({0,0,0});
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	window.draw(m_t4);
	window.draw(m_inputName);
	window.display();
}

void Menu::EvaluarEvento (Juego & game, Event & event) {
	if (event.type==Event::KeyPressed and event.key.code==Keyboard::Escape)
		game.Salir();
	else 
		m_inputName.processEvent(event);
}

