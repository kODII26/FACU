#include <iostream>
#include <vector>
using namespace std;
// cargar una lista de personas hasta que dni sea 0
struct persona {
	string nombre;          // cada componente se llama campo
	int dni, edad;
};

//codificar una funcion que retorne un struct de una persona a partir de su dni
persona GetPersonaPorDni(vector<persona>lista, int dni) {
	persona p;
	for (unsigned int i=0; i<lista.size();i++) {
		if (lista[i].dni == dni) {
			p=lista[i];
			return p;
		}
	}
	return p;
}
// codificar una funcion que apartir del dni de una persona, retorne su posicion
// si no lo encuentra, que retorne -1
int GetPosicion(vector<persona>lista,int dni) {
	for (int i=0; i<lista.size();i++) {
		if (lista[i].dni ==dni)
			return 1;
	}
	return -1;
}
int main(int argc, char *argv[]) {
	persona p;       //declaro una variable o instancia de persona 
	vector<persona>lista; // un vector de tipo persona
	int dni;
	cout<<"Ingrese dni (0 termina) "; cin>>dni;
	while (dni != 0) {
		persona p;   // declaro una variable o instancia de persona 
		p.dni = dni;
		cout<<"Ingrese nombre ";cin>>p.nombre;
		cout<<"Ingrese edad ";cin>>p.edad;
		
		lista.push_back(p);
		cout<<"ingrese dni (0 termina) "; cin>>dni;
	}
	cout<<endl<<endl;
	for (int i=0;i<lista.size();i++) {
		cout<<"Nombre : "<<lista[i].nombre<<"   - edad : "<<lista[i].edad<<endl;
	}
	return 0;
}
