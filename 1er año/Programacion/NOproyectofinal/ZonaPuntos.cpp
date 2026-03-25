#include "ZonaPuntos.h"
using namespace sf;

ZonaPuntos::ZonaPuntos()  {
	m_zona("zonapuntos.png")
	m_sprite.setScale(0.1,0.1);
	int aleatorio = 100+rand()%501;
	m_sprite.setPosition(aleatorio,0);
}

void ZonaPuntos::Actualizar() {
	m_sprite.move(0,1);
	
}

bool ZonaPuntos::debeGenerar() {
	int num = rand()%10;
	if( num==3) return true;
	
	return false;
}

ZonaPuntos ZonaPuntos::GenerarZona() { 
	return ZonaPuntos();
}
