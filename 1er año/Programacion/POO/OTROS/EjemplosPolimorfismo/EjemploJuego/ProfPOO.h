#ifndef PROFPOO_H
#define PROFPOO_H
#include "Personaje.h"

class ProfPOO : public Personaje {
public:
	ProfPOO();
	void Atacar (Personaje & otro) override;
private:
};

#endif

