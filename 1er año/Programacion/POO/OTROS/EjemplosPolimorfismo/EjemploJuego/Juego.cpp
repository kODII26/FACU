#include "Juego.h"
#include <cstdlib>
#include "Mago.h"
#include "Caballero.h"
#include "Arquero.h"
#include "ProfPOO.h"
#include "Mongalote.h"
using namespace std;

Juego::Juego (int cant_personajes) {
	for(int i=0;i<cant_personajes;++i) { 
		switch(rand()%5) {
		case 0: m_v.push_back( new Mago() ); break;
		case 1: m_v.push_back( new Caballero() ); break;
		case 2: m_v.push_back( new Arquero() ); break;
		case 3: m_v.push_back( new ProfPOO() ); break;
		case 4: m_v.push_back( new Mongalote() ); break;
		}
	}
}

int Juego::SeleccionarUnoVivo(int que_no_sea_justo_este) const {
	int cual;
	do {
		cual = rand()%m_v.size();
	} while(not m_v[cual]->EstaVivo() or cual==que_no_sea_justo_este);
	return cual;
}

InfoAtaque Juego::Turno ( ) {
	InfoAtaque info;
	info.atacante = SeleccionarUnoVivo();
	info.atacado = SeleccionarUnoVivo(info.atacante);
	m_v[info.atacante]->Atacar(*m_v[info.atacado]);
	for(size_t i=0;i<m_v.size();++i) 
		m_v[i]->RegenerarMana();
	return info;
}

bool Juego::Terminado ( ) const {
	int cant_vivos = 0;
	for(size_t i=0;i<m_v.size();++i) { 
		if (m_v[i]->EstaVivo())
			++cant_vivos;
	}
	return cant_vivos==1;
}

int Juego::CantPersonajes ( ) const {
	return m_v.size();
}

const Personaje & Juego::VerPersonaje (int cual) const {
	return *m_v[cual];
}

int Juego::VerGanador ( ) const {
	for(size_t i=0;i<m_v.size();++i) { 
		if (m_v[i]->EstaVivo())
			return i;
	}
	return -1;
}

Juego::~Juego ( ) {
	for(size_t i=0;i<m_v.size();++i) { 
		delete m_v[i];
	}
}

