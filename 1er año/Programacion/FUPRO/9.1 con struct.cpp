#include <iostream>
#include <vector>
using namespace std;
struct alumno {
	string nombre;
	int nota;
};

vector<alumno> getNotas (int cant) {
	vector<alumno> v(cant);
	for (size_t i=0;i<v.size();i++) {
		cin>>v[i].nombre>>v[i].nota; 
	}
	return v;
}
int getProm (vector<alumno> notas, int cant) {
	int suma=0;
	for (int i=0;i<cant;i++) {
		suma = suma + notas[i].nota;
	}
	return suma/cant;
}
void mostrarNotas (vector<alumno>notas, int prom, int cant) {
	cout<<"Los que estan arriba del promedio son: "<<endl;
	for (int i=0; i<cant; i++) {
		if (notas[i].nota>= prom) {
			cout<<notas[i].nombre<<":"<<" con una nota de "<<notas[i].nota<<endl;
		}
	}
}
int main() {
	int cant=2;
	int prom;
	vector<alumno> notas = getNotas(cant);
	prom = getProm(notas,cant);
	mostrarNotas(notas,prom,cant);
	return 0;
}

