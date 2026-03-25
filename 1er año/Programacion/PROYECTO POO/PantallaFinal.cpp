#include "PantallaFinal.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "Juego.h"
#include "Menu.h"
#include "Partida.h"
#include <iostream>
using namespace std;
using namespace sf;

vector<infoPlayer> MejoresTres(string nomArch) {
	ifstream archii(nomArch);
	vector<infoPlayer> v;
	vector<infoPlayer> mejores_tres(3);
	infoPlayer p;
	while(archii>>p.nombre>>p.puntos ){
		v.push_back(p);
	}
	archii.close();
	

	
	infoPlayer m1,m2,m3;
	
	
	for(size_t i=0;i<v.size();++i) {
		if( v[i].puntos > m1.puntos ){
			m3 = m2;
			m2 = m1;
			m1 = v[i];
		}else{
			if( v[i].puntos> m2.puntos){
				m3 = m2;
				m2 = v[i];
			}else{
				if(v[i].puntos>m3.puntos) {
					m3 = v[i];
				}
			}
		}
	}
	mejores_tres[0]=m1; 
	mejores_tres[1]=m2;
	mejores_tres[2]=m3;
	return mejores_tres;
}

PantallaFinal::PantallaFinal() {
	
	m_t1.setFont(m_font);
	m_t2.setFont(m_font2);
	m_t3.setFont(m_font);
	m_t4.setFont(m_font2);
	
	m_t1.setString("Game Over");
	m_t1.setPosition(130,30);
	m_t1.setCharacterSize(50);
	
	m_t3.setString("-presione Q para ir al menu-");
	m_t3.setPosition(110,120);
	m_t3.setCharacterSize(20);
	

	m_t4.setString("RANKINGS");
	m_t4.setFillColor({150,150,150});
	m_t4.setPosition(30,300);
	m_t4.setCharacterSize(40);

	vector<infoPlayer> vm = MejoresTres(m_nomArch);
	
	m_t2.setString(to_string(1)+"   "+vm[0].nombre+": "+to_string(vm[0].puntos)+"\n"+to_string(2)+"   "+vm[1].nombre+": "+to_string(vm[1].puntos)+"\n"+to_string(3)+"   "+vm[2].nombre+": "+to_string(vm[2].puntos)+"\n");
	m_t2.setFillColor({150,150,150});
	m_t2.setPosition(40,350);
	m_t2.setCharacterSize(20);

}

void PantallaFinal::Actualizar (Juego &game) {
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t1.setFillColor({r,g,b});
	m_t3.setFillColor({r,g,b});
	if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		game.CambiarEscena(new Menu());
}

void PantallaFinal::Dibujar (RenderWindow & window) {
	window.clear({0,0,0});
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	window.draw(m_t4);
	window.display();
}

