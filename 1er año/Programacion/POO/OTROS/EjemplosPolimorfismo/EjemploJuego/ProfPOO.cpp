#include "ProfPOO.h"

ProfPOO::ProfPOO() : Personaje("ProfPOO") {
	
}

// El Profesor es letal, con solo una unidad de maná realiza un súper-ataque
// que le baja 10 puntos de vida al otro personaje
void ProfPOO::Atacar (Personaje & otro) {
	if (m_mana>=1 && otro.VerVida()>1) {
		otro.RecibirAtaque(10);
		--m_mana;
	} else {
		Personaje::Atacar(otro);
	}
}

