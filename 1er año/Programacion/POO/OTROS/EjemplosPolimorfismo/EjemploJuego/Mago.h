#ifndef MAGO_H
#define MAGO_H
#include "Personaje.h"

class Mago : public Personaje {
public:
	Mago();
	void Atacar (Personaje & otro) override;
private:
};

#endif

