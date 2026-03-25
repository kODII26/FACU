#ifndef MONGALOTE_H
#define MONGALOTE_H
#include "Personaje.h"

class Mongalote : public Personaje {
public:
	Mongalote();
	virtual void RecibirAtaque(int cuanto) override;
private:
};

#endif

