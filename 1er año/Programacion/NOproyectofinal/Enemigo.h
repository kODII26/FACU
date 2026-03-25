#ifndef NAVEENEMIGA_H
#define NAVEENEMIGA_H
#include "Enemigo.h"
#include "Objeto.h"
#include "Disparo.h"

class Enemigo : public Objeto {
public:
	Enemigo();
	void Actualizar();
	bool debeDisparar();
	Disparo generarDisparo();
	Vector2f verPosicion() { return m_sprite.getPosition(); }
private:
		Vector2f m_speed = {2,0};
		Clock m_clock;
		int m_num = 0;
};

#endif



