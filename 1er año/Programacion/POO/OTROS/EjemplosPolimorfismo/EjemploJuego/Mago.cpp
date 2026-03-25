#include "Mago.h"

Mago::Mago() : Personaje("Mago") {
	
}

// el ataque especial del mago consiste en absorver él la unidad
// de energía que pierde su enemigo
void Mago::Atacar (Personaje & otro) {
	if (m_mana>=5) {
		otro.RecibirAtaque(1);
		m_mana-=5; ++m_vida;
	} else {
		Personaje::Atacar(otro);
	}
}

