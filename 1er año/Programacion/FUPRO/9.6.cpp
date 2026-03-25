#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
void mostrar(vector<int> datos) {
	cout<<"Monto por mes:"<<endl;
	for (int i:datos) {
		cout<<i<<endl;
	}
}
int mesmenor (vector<int> datos) {
	int menor=1000000;
	int posmenor=0;
	for (size_t i=0; i<datos.size(); i++) {
		if (datos[i]<menor) {
			menor = datos[i];
			posmenor = i;
		}
	}
	return posmenor;
}
int main() {
	vector<int> datos(12,0);
	int monto, mes, posmenor;
	while (monto !=0) {
		cout<<"mes  y monto"<<endl;
		cin>>mes>>monto;
		mes = mes-1;
		for (int i=0; i<datos.size();i++) {
			if (i==mes) {
				datos[i] = monto + datos[i];
			}
		}
	}
	mostrar(datos);
	posmenor = mesmenor(datos);
	++posmenor;
	cout<<"El mes con menos aportes fue: "<<posmenor<<endl;
	return 0;
}

