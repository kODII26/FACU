#ifndef JUEGO_H
#define JUEGO_H
#include <vector>
#include "Personaje.h"

/**
* Struct auxiliar que retorna el método Turno de la clase juego para
* pasarle al main detalles sobre qué ocurrió durante ese turno
**/
struct InfoAtaque {
	int atacante;
	int atacado;
};

/** 
* Clase que modela las reglas generales del juego.
* Modela solo las reglas generales por sí misma, y delega a los métodos de la
* clase Personaje los detalles que dependen de los personajes
**/
class Juego {
public:
	
	/// El ctor crea a los personajes para el juego
	Juego(int cant_personajes);
	
	/// Método que simula un turno/ronda del juego, en el cual se produce un ataque.
	/// El struct que retorna contiene información sobre qué ocurrió exactamente en ese ataque.
	InfoAtaque Turno();
	
	///  Para que el main sepa si el juego terminó (porque quedó uno solo vivo), 
	/// o si debe seguir ejecutando más turnos
	bool Terminado() const;
	
	// métodos para que el main o los Personajes puedan consultar el estado del juego, 
	// pero sin poder modificarlo
	int CantPersonajes() const;
	const Personaje &VerPersonaje(int cual) const;
	int VerGanador() const;
	
	/// función auxiliar para elegir un personaje al azar
	int SeleccionarUnoVivo(int que_no_sea_justo_este=-1) const;
	
	/// Dado que los personajes utilizan polimorfismo, se crean con new, y por
	/// eso se necesita un destructor para hacer los correspondientes deletes
	~Juego();
	
private:
	// estado del juego... todo lo que se necesita es el estado de los personajes
	std::vector<Personaje*> m_v;
	
};

#endif

