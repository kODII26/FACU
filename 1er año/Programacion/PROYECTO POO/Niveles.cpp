#include "Niveles.h"
#include "Player.h"

using namespace std;
using namespace sf;
Niveles::Niveles() {
	m_fondo.loadFromFile("Recursos/fondo.jpg");
	m_fondo2.loadFromFile("Recursos/fondo2.jpg");
	int n=1;
	cargarNivel(n);
}

void Niveles::cargarNivel (int n) {
	if (n==1){
		m_s_fondo.setTexture(m_fondo);
		m_s_fondo.setScale(1,1);
		m_s_fondo.setPosition(0,0);
	}
	if (n==2){
		m_s_fondo.setTexture(m_fondo2);
		m_s_fondo.setScale(1,1);
		m_s_fondo.setPosition(0,0);
	}
}

void Niveles::dibujarNivel (RenderWindow & win, Player j, int n) {
	cargarNivel(n);
	win.draw(m_s_fondo);
}

