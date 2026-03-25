#ifndef ARQUERO_H
#define ARQUERO_H
#include "Personaje.h"

class Arquero : public Personaje {
public:
	Arquero();
	void Atacar (Personaje & otro) override;
private:
};

#endif

