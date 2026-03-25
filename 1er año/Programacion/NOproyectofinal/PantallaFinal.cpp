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

vector<int> MejoresTres(string nomArch) {
	ifstream archii(nomArch);
	vector<int> v;
	vector<int> mejores_tres(6);
	int puntos;
	int i=0;
	while( archii>>puntos ){
		v.push_back(puntos);
		cout<<"punto "<<i<<":"<<v[i]<<endl;
		++i;
	}
	archii.close();
	
	int m1=0,m2=0,m3=0,pos1=0,pos2=0,pos3=0;
	for(size_t i=0;i<v.size();++i) {
		cout<<"1: "<<v[i]<<">"	<<m1<<" ?"<<endl;
		if( v[i] > m1 ){
			m3 = m2;
			m2 = m1;
			m1 = v[i];
			pos3=pos2;
			pos2=pos1;
			pos1=i;
		}else{
			cout<<"2: "<<v[i]<<">"<<m2<<" ?"<<endl;
			if( v[i]> m2){
				m3 = m2;
				m2 = v[i];
				pos3=pos2;
				pos2=i;
			}else{
				cout<<"3: "<<v[i]<<">"<<m3<<" ?"<<endl;
				if(v[i]>m3) {
					m3 = v[i];
					pos3=i;
				}
			}
		}
	}
	mejores_tres[0]=m1; mejores_tres[1]=pos1;
	mejores_tres[2]=m2; mejores_tres[3]=pos2;
	mejores_tres[4]=m3; mejores_tres[5]=pos3;
	return mejores_tres;
}

PantallaFinal::PantallaFinal() {
	m_font.loadFromFile("asap.ttf");
	m_t1.setFont(m_font);
	m_t2.setFont(m_font);
	m_t3.setFont(m_font);
	
	m_t1.setString("Game Over");
	m_t1.setPosition(200,160);
	m_t1.setCharacterSize(50);
	
	vector<int> vm = MejoresTres(m_nomArch);

	m_t2.setString("Partida "+to_string(vm[1]/2)+":"+to_string(vm[0])+"\n"+"Partida "+to_string(vm[3]/2)+":"+to_string(vm[2])+"\n"+"Partida "+to_string(vm[5]/2)+":"+to_string(vm[4]));
	m_t2.setFillColor({150,150,150});
	m_t2.setPosition(150,350);
	m_t2.setCharacterSize(20);
	
	
	
	m_t3.setString("presione Q para ir al menú");
	m_t3.setFillColor({150,150,150});
	m_t3.setPosition(150,300);
	m_t3.setCharacterSize(20);
}

void PantallaFinal::Actualizar (Juego &game) {
	unsigned char r = rand();
	unsigned char g = rand();
	unsigned char b = rand();
	m_t1.setFillColor({r,g,b});
	if (Keyboard::isKeyPressed(Keyboard::Key::Q))
		game.CambiarEscena(new Menu());
}

void PantallaFinal::Dibujar (RenderWindow & window) {
	window.clear({0,0,0});
	window.draw(m_t1);
	window.draw(m_t2);
	window.draw(m_t3);
	window.display();
}

