#include "Partida.h"
#include "ZonaPuntos.h"
#include "Juego.h"
#include <cmath>
#include <iostream>
#include "Menu.h"
#include "PantallaFinal.h"
#include <fstream>
#include <algorithm>
using namespace std;
void Partida::EscribirArchivo() {
	string nom_arch = "TablaDePuntos.txt";
	
	ifstream arch(nom_arch);
	vector<int> v;
	int puntos;
	while( arch>>puntos ){
		v.push_back(puntos);
	}
	arch.close();
	int x = *m_player.ObtenerPunt();
	cout<<"PUNTOS = "<<x<<endl;
	v.resize(v.size()+1);
	v[v.size()] = x;
	
	cout<<"VECTOR PUNTOS = "<<endl;
	ofstream archi(nom_arch,ios::trunc);
	for(size_t i=0;i<=v.size();++i) {
		cout<< v[i] <<endl;
		archi<< v[i] <<endl;
	}
	sort(v.begin(),v.end());
	archi.close();
}


Partida::Partida() {
	m_punt = 0;
	m_punt += *m_player.ObtenerPunt();	
	m_fontP.loadFromFile("asap.ttf");
	m_tPuntaje.setFont(m_fontP);
	
	
	m_tPuntaje.setString("Puntos Naw = "+to_string(m_punt));
	m_tPuntaje.setFillColor({150,0,0});
	m_tPuntaje.setPosition(180,150);
	m_tPuntaje.setCharacterSize(510);
}

bool fuera_de_la_pantalla(Disparo &d) {
	Vector2f p = d.verPosicion();
	if (p.x<0 or p.x>480) return true;
	return false;
}

bool fuera_de_la_pantallaE(ZonaPuntos &z) {
	Vector2f p = z.verPosicion();
	if (p.x<0 or p.x>480) return true;
	return false;
}

bool Colisiona(Disparo &d,Player &n) {
	Vector2f pd = d.verPosicion();
	Vector2f pn = n.verPosicion();
	Vector2f v = pd-pn;
	return sqrt((v.x*v.x+v.y*v.y))<15;
}



void Partida:: Actualizar(Juego &game) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		game.CambiarEscena(new PantallaFinal());
	
	m_enemiga.Actualizar();
	m_player.Actualizar(m_player);
	
	if( m_estrella.debeGenerar() ) { //deberia preguntarlo a un enemigo o a una partida 
		vo.push_back(m_estrella.GenerarZona());
	}
	for(ZonaPuntos &z: vo) {
		z.Actualizar();
		if (z.CollideWith(m_player)) {
			
			auto it3 = remove_if(vd.begin(),vd.end(),fuera_de_la_pantalla); 
			vd.erase(it3,vd.end());
			m_player.CalcularPuntos();
		}
	}
	
	if( m_enemiga.debeDisparar() ){ 
		vd.push_back(m_enemiga.generarDisparo());
	}
	for(Disparo &d: vd){ 
		d.Actualizar();
		if(Colisiona(d,m_player)){
			EscribirArchivo();
			game.CambiarEscena(new PantallaFinal());
		}
	}
	
	auto it = remove_if(vd.begin(),vd.end(),fuera_de_la_pantalla); 
	vd.erase(it,vd.end());
	auto it2 = remove_if(vo.begin(),vo.end(),fuera_de_la_pantallaE); 
	vo.erase(it2,vo.end());	
}

void Partida::Dibujar(RenderWindow &window) {
	window.draw(m_tPuntaje);
	window.clear(Color({0,0,0}));
	m_enemiga.Dibujar(window);
	m_player.Dibujar(window);
	for(ZonaPuntos &z: vo) z.Dibujar(window);
	for(Disparo &d: vd) d.Dibujar(window);
	window.display();
}




