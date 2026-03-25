#ifndef PLAYER_H
#define PLAYER_H
#include "Objeto.h"
#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <string>
using namespace std;
using namespace sf;


class Player : public Objeto {
public:
	Player();
	void Actualizar(Player &);
	Vector2f verPosicion();
	void CalcularPuntos();
	float ObtenerPunt() {return m_puntos;}
	void asignarPunt(int x);
private:
	Keyboard::Key acel,fren,izq,der;
	float m_puntos=0;
};

#endif
