#ifndef PANTALLAFINAL_H
#define PANTALLAFINAL_H
#include "Enemigo.h"
#include "Escena.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
#include "Partida.h"
#include "Player.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
using namespace std;

class PantallaFinal : public Escena {
public:
	PantallaFinal();
	void Actualizar(Juego &game) override;
	void Dibujar(RenderWindow &window) override;
private:
	Text m_t1, m_t2, m_t3, m_t4;
	string m_nomArch = "TablaDePuntos.txt";

};

#endif

