#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
vector<int> getNumeros (int cant) {
	int numero;
	vector<int> v(cant);
	for (int i=0; i<cant;i++) {
		cin>> numero;
		v[i] = numero;
	}
	return v;
}
void mostrar ( vector<int> datos) {
	for (int x:datos)
		cout<<x<<"-";
	cout<<endl;
}
int buscar(vector<int>datos) {
	for (size_t i=0; i<datos.size(); i++) {
		if (datos[i] == 523) {
			return i;
		}
	}
	return -1;
}
void eliminar (vector<int>&datos, int pos) {
	for (size_t i=pos; i+1<datos.size(); i++) {
		datos[i] = datos[i+1];
	}
	datos.resize(datos.size()-1);
}

int main() {
	int cant,pos;
	cout<<"cuantos numeros hay"<<endl;
	cin>>cant;
	vector<int> datos = getNumeros(cant);
	mostrar(datos);
	
	pos = buscar(datos);
	while (pos!=-1) {
		eliminar(datos,pos);
		pos = buscar(datos);
	}
	
	mostrar(datos);
	return 0;
}

