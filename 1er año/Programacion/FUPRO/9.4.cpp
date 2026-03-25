#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<string> nombres;
	vector<string> nombresAprob;
	vector<string> nombresNoAprob;
	vector<int> notas;
	string nombre;
	int nota;
	cout<<"Ingrese la nota y luego el nombre"<<endl;
	cin>>nota>>nombre;
	while (nota!=0) {
		notas.push_back(nota);
		nombres.push_back(nombre);
		if (nota>=60) 
			nombresAprob.push_back(nombre);
		if (nota<60) 
			nombresNoAprob.push_back(nombre);
		cin>>nota>>nombre;
	}
	cout<<"los aprobados son: "<<endl;
	for (string i:nombresAprob) {
		cout<<i<<endl;
	}
	cout<<"los no aprobados son: "<<endl;
	for (string c:nombresNoAprob) {
		cout<<c<<endl;
	}
	return 0;
}

