#include "Partida.h"
#include "ZonaPuntos.h"
#include "Juego.h"
#include <cmath>
#include <iostream>
#include "Menu.h"
#include "PantallaFinal.h"
#include <fstream>
#include <algorithm>
#include <vector>
#include "Intermedio.h"
#include <SFML/Audio/Music.hpp>
using namespace std;
bool fuera_de_la_pantalla(Disparo &d) {
	Vector2f p = d.verPosicion();
	if (p.y<0 or p.y>480) return true;
	return false;
}

bool fuera_de_la_pantallaE(ZonaPuntos &z) {
	Vector2f p = z.verPosicion();
	if (p.y<0 or p.y>480) return true;
	return false;
}

bool Colisiona(Disparo &d,Player &n) {
	Vector2f pd = d.verPosicion();
	Vector2f pn = n.verPosicion();
	Vector2f v = pd-pn;
	return sqrt((v.x*v.x+v.y*v.y))<25;
}

Partida::Partida(infoPlayer p, int n) {
	n_actual=n;
	m_info=p;
	m_player.asignarPunt(m_info.puntos);
	m_text_zona.loadFromFile("Recursos/ZonaPuntos.png");
	
	m_punt = m_player.ObtenerPunt();
	m_tPuntaje.setFont(m_font);
	m_tPuntaje.setString("Puntos "+to_string(m_player.ObtenerPunt()));
	m_tPuntaje.setFillColor({255,255,255});
	m_tPuntaje.setPosition(545,460);
	m_tPuntaje.setCharacterSize(10);
	
	m_perder.loadFromFile("Sonidos/perder.ogg");
	m_sound_perder.setBuffer(m_perder);
	m_sound_perder.setVolume(8);
	
	m_nivel.loadFromFile("Sonidos/nivel.wav");
	m_sound_nivel.setBuffer(m_nivel);
	m_sound_nivel.setVolume(8);
	
}

void Partida::Dibujar(RenderWindow &window) {
	window.clear(Color({0,0,0}));
	nivel.dibujarNivel(window,m_player, n_actual);
	window.draw(m_tPuntaje);
	m_enemiga.Dibujar(window);
	m_player.Dibujar(window);
	for(ZonaPuntos &z: vo) z.Dibujar(window);
	for(Disparo &d: vd) d.Dibujar(window);
	window.display();
}

void Partida:: Actualizar(Juego &game) {
	if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
		m_sound_perder.play();
		game.CambiarEscena(new PantallaFinal());
	}
	if (n_actual==1){
		if (m_player.ObtenerPunt()>100){
			m_info.puntos=m_player.ObtenerPunt();
			m_sound_nivel.play();
			game.CambiarEscena(new Intermedio(m_info));
		}
	}
	m_enemiga.Actualizar(n_actual);
	m_player.Actualizar(m_player);

	if( debeGenerarZona() and vo.size()<1)  { 
	vo.push_back(GenerarZona());
	}
	for(ZonaPuntos &z: vo) {
		z.Actualizar();
		if (z.CollideWith(m_player)) {
			m_player.CalcularPuntos();
			vo.pop_back();
		}
	}
	
	if( m_enemiga.debeDisparar(n_actual) ){ 
		vd.push_back(m_enemiga.generarDisparo());
	}
	for(Disparo &d: vd){ 
		d.Actualizar();
		if(Colisiona(d,m_player)){
			EscribirArchivo();
			m_sound_perder.play();
			game.CambiarEscena(new PantallaFinal());
		}
	}
	
	auto it = remove_if(vd.begin(),vd.end(),fuera_de_la_pantalla); 
	vd.erase(it,vd.end());
	auto it2 = remove_if(vo.begin(),vo.end(),fuera_de_la_pantallaE); 
	vo.erase(it2,vo.end());	
	m_punt = m_player.ObtenerPunt();
	m_tPuntaje.setString("Puntos "+to_string(m_punt));
} 

bool Partida::debeGenerarZona() {
	int num = rand()%300;
	if( num==100) return true;
	return false;
}
ZonaPuntos Partida::GenerarZona ( ) {
	return ZonaPuntos(m_text_zona);
}
void Partida::EvaluarEvento (Juego & game, Event & event) {
	if (event.type==Event::KeyPressed and event.key.code==Keyboard::Escape)
		game.CambiarEscena(new Menu);
}
void Partida::EscribirArchivo() {
	m_info.puntos=m_player.ObtenerPunt();
	string nom_arch = "TablaDePuntos.txt";
	
	ifstream arch(nom_arch);
	vector<infoPlayer> vp;
	infoPlayer p;
	
	while(arch>>p.nombre>>p.puntos ){
		vp.push_back(p);
	}
	arch.close();
	
	vp.push_back(m_info);
	
	ofstream archi(nom_arch,ios::trunc);
	for(size_t i=0;i<vp.size();++i) {
		archi<<vp[i].nombre<<" "<<vp[i].puntos;
	}
	archi.close();
}


