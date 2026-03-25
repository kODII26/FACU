#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <string>

/**
* Clase para guardar el estado de un personaje e implementar sus acciones específicas.
* Hacemos virtuales los métodos que queremos que puedan variar según el tipo de personaje,
* ya que por cada tipo específico habrá una herencia.
**/
class Personaje {
	
public:
	
	Personaje(std::string tipo);
	
	// métodos para consultar el estado del personaje... para mostrar desde el main 
	// o para que otros personajes puedan eventualmente elegir mejor a quien atacar
	std::string VerTipo() const;
	int VerMana() const;
	int VerVida() const;
	bool EstaVivo() const;
	
	/// mediante este método la clase Juego le indica al Personaje que le toca realizar su ataque,
	/// dirigido al otro que recibe como argumento
	virtual void Atacar(Personaje &otro);
	
	/// a medida que el tiempo avanza (en cada turno), se regenera el mana... 
	void RegenerarMana();
	
	/// mediante este método, un personaje recibe un ataque durante un turno, y se defiende o pierde vida
	virtual void RecibirAtaque(int cuanto);
	
	/// si hay métodos virtuales, por las dudas el destructor debe ser virtual también
	virtual ~Personaje() { }
	
protected:
	
	// datos y estado del personaje
	std::string m_tipo;
	int m_vida, m_mana;
	
};

#endif

