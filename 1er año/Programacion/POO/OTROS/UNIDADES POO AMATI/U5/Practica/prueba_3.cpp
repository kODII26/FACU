///DEFINITIVO:lee lineas de nombres y números dentro de un archivo y las guarda en un vector de tipo struct.
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Contacto {
	string nombre; 
	int numero;
};

int ContarRenglones() {
	ifstream archi("archivo_de_practica.txt");
	string x;
	int N = 0;
	while( getline(archi,x) ) {
		N++;
	}
	
	return N;
}

int main() {
	ifstream archi("archivo_de_practica.txt");
	
	vector<Contacto> v;
	Contacto c;
	
	int N = ContarRenglones()/2;///cuento los renglones y los divido 2 ya que dos renglones le pertenecen a un solo contacto
	string x;
	for(int i=0; i<N ;++i) {
		int cont = 0;
		while( cont<2 ){
			if( getline(archi,x) and (cont%2) == 0){
				c.nombre = x;
				cout<<"nombre: "<<c.nombre<<endl;
			}else{
				string x2 = x;
				int newX;
				istringstream iss(x2);
				iss >> newX;
				
				c.numero = newX;
				cout<<"numero: "<<c.numero<<endl;
			}
			++cont;
			
		}
		v.push_back(c);
	}
	
	cout<<"***************************************"<<endl;
	for( size_t i=0; i<v.size(); ++i ) {
		cout<<"nombre: "<<v[i].nombre<<endl;
		cout<<"numero: "<<v[i].numero<<endl;
	}
	return 0;
}

