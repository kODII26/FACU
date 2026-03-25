#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Persona{
	string nombre;
	string apellido;
	int dni;
};

template<typename T>
T Mayor(T a,T b) {
	if( a > b ) {
		return a;
	}
	return b;
}

template<typename T,typename T2>
	T Mayor(vector<T> &v, T2 puntero_a_funcion) {
	T mayor = v[0];
	for(size_t i=1; i<v.size(); ++i) {
		if( puntero_a_funcion(mayor,v[i]) ) {
			mayor = v[i];
		}
	}
	return mayor;
}

bool Compara_Nom(const Persona &mayor,const Persona &p) {
	return mayor.nombre < p.nombre;
}

bool Compara_Ape(const Persona &mayor,const Persona &p) {
	return mayor.apellido < p.apellido;
}

bool Compara_Dni(const Persona &mayor,const Persona &p) {
	return mayor.dni < p.dni;
}

int main() {
	
	vector<Persona> v(3);
	for(size_t i=0; i<v.size(); ++i) {
		cout<<"nombre["<<i<<"]: ";cin>>v[i].nombre;
		cout<<"apellido["<<i<<"]: ";cin>>v[i].apellido;
		cout<<"dni["<<i<<"]: ";cin>>v[i].dni;
	}
	cout<<endl;
	
	Persona mayor_nombre = Mayor(v, Compara_Nom);
	Persona mayor_apellido = Mayor(v, Compara_Ape);
	Persona mayor_dni = Mayor(v, Compara_Dni);
	
	cout<<"El mayor nombre : "<< mayor_nombre.nombre <<endl;
	cout<<"El apellido dni: "<< mayor_apellido.apellido <<endl;
	cout<<"El mayor dni: "<< mayor_dni.dni <<endl;
	
	
	
	
	
	
	return 0;
}
