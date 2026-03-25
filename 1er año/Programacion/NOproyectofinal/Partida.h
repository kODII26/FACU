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
using namespace sf;

class Partida : public Escena{
public:
	Partida();
	virtual void Actualizar(Juego &game) override;
	virtual void Dibujar(RenderWindow &window) override;
	void EscribirArchivo();
private:
	Enemigo m_enemiga;
	Player m_player;
	vector<Disparo> vd;
	vector<ZonaPuntos> vo;
	ZonaPuntos m_estrella; //<- Mal, no tiene sentido una estrella generada afuera del vector
	Font m_fontP;
	Text m_tPuntaje;
	float m_punt;
};

#endif

