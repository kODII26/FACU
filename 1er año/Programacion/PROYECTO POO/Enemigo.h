#ifndef NAVEENEMIGA_H
#define NAVEENEMIGA_H
#include "Enemigo.h"
#include "Objeto.h"
#include "Disparo.h"

class Enemigo : public Objeto {
public:
	Enemigo();
	void Actualizar(int n_actual);
	bool debeDisparar(int n_actual);
	Disparo generarDisparo();
	Vector2f verPosicion() { return m_sprite.getPosition(); }
private:
	Vector2f m_speed = {2,0};
	Vector2f m_speed2 = {4,0};
	Clock m_clock;
	int m_num = 0;
};

#endif



