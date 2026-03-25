#ifndef CABALLERO_H
#define CABALLERO_H
#include "Personaje.h"

class Caballero : public Personaje {
public:
	Caballero();
	void Atacar(Personaje &otro) override;
private:
};

#endif

