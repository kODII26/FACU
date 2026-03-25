#include "Personaje.h"


Personaje::Personaje (std::string tipo) 
	: m_tipo(tipo), m_vida(10), m_mana(5)
{
	
}

std::string Personaje::VerTipo ( ) const {
	return m_tipo;
}

int Personaje::VerMana ( ) const {
	return m_mana;
}

int Personaje::VerVida ( ) const {
	return m_vida;
}

void Personaje::Atacar (Personaje & otro) {
	--otro.m_vida;
}

bool Personaje::EstaVivo ( ) const {
	return m_vida>0;
}

void Personaje::RegenerarMana ( ) {
	++m_mana;
}

void Personaje::RecibirAtaque (int cuanto) {
	m_vida -= cuanto;
}

