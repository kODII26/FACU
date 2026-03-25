#ifndef PARTIDA_H
#define PARTIDA_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Escena.h"
#include "Player.h"
#include "ZonaPuntos.h"
#include "Enemigo.h"
#include "PantallaFinal.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "Partida.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "Niveles.h"
using namespace std;
using namespace sf;

struct infoPlayer {
	int puntos=0;
	string nombre;
};

class Partida : public Escena{
public:
	Partida(infoPlayer p,int n);
	void EvaluarEvento(Juego &game, Event &event) override;
	void Actualizar(Juego &game) override;
	void Dibujar(RenderWindow &window) override;
	void EscribirArchivo();
	bool debeGenerarZona();
	ZonaPuntos GenerarZona();
private:
	Enemigo m_enemiga;
	Player m_player;
	vector<Disparo> vd;
	vector<ZonaPuntos> vo;
	Text m_tPuntaje;
	int m_punt=0;
	Texture m_text_zona;
	infoPlayer m_info;
	Sound m_sound_perder,m_sound_nivel;
	SoundBuffer  m_perder, m_nivel;
	Niveles nivel;
	int n_actual;
};

#endif

