#include <iostream>
#include "Juego.h"
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

/// función para mostrar el estado de todos los personajes vivos
void ListarPersonajes(const Juego &j); 

/// función para mostrar los detalles de cómo fue un ataque en un turno
void MostrarAtaque(const Juego &j, InfoAtaque info);	

/// función para informar el ganador una vez finalizada la partida
void MostrarGanador(const Juego &j);


/// función principal, controla el avance del juego
int main (int argc, char *argv[]) {
	
	srand(time(0)); // para que rand no genere siempre los mismos números
	
	Juego j(8);                      // estado inicial, 8 personajes de tipos aleatorios
	do {                             // repetir
		ListarPersonajes(j);         //    listar el estado de cada personaje
		InfoAtaque info = j.Turno(); //    jugar una ronda, alguien intenta atacar a otro alguien
		MostrarAtaque(j,info);       //    informar cómo fue el ataque en esta ronda
	} while(not j.Terminado());      // hasta que quede solo uno vivo
	MostrarGanador(j);               // mostrar quien gano
	
	return 0;
}



// implementación de las funciones declaradas arriba

void ListarPersonajes(const Juego &j) {
	for(int i=0;i<j.CantPersonajes();++i) { 
		const Personaje &p = j.VerPersonaje(i);
		if (p.EstaVivo()) {
			cout << setw(3) << right << i+1 << " ";
			cout << setw(10) << left << p.VerTipo();
			cout << setw(3) << left  << p.VerMana();
			cout << setw(3) << left  << p.VerVida();
			cout << endl;
		}
	}
	cin.get();
}

void MostrarGanador(const Juego &j) {
	int g = j.VerGanador();
	const Personaje &p = j.VerPersonaje(g);
	cout << "Ganó el " << p.VerTipo() << " nro " << g+1 << endl;
}


void MostrarAtaque(const Juego &j, InfoAtaque info) {
	const Personaje &p1 = j.VerPersonaje(info.atacante);
	const Personaje &p2 = j.VerPersonaje(info.atacado);
	cout << "El " << p1.VerTipo() <<  " nro " << info.atacante+1
		<< " ataca al " << p2.VerTipo() << " nro " << info.atacado+1;
	if (not p2.EstaVivo()) cout << " y lo liquida" << endl;
	else cout << ", pero sobrevive" << endl;
	cin.get();
}
