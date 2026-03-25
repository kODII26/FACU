#include <iostream>
#include <vector>
using namespace std;
vector<int> getNotas (int cant) {
	vector<int> v(cant);
	for (size_t i=0;i<v.size();i++) {
		v[i] = rand()%101;
	}
	return v;
}
int getProm (vector<int> notas, int cant) {
	int suma=0;
	for (int x:notas) {
		suma = suma + x;
	}
	return suma/cant;
}
void mostrarNotas (vector<int>notas, int prom, int cant) {
	cout<<"Los que estan arriba del promedio son: "<<endl;
	for (int i=0; i<cant; i++) {
		if (notas[i]>= prom) {
			cout<<notas[i]<<endl;
		}
	}
}
int main() {
	int cant=30;
	int prom;
	vector<int> notas = getNotas(cant);
	prom = getProm(notas,cant);
	mostrarNotas(notas,prom,cant);
	return 0;
}

