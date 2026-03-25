#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Contacto {
	string nombre;
	int numero;
};

int main() {
	
	ifstream archi("archivo_de_practica.txt");
	if( !archi.is_open() ) {
		cout<<"No se pudo abrir el archivo.";
		return 1;
	}
	vector<Contacto> v;
	string nom;
	int n=0;
	
	while( getline(archi,nom) or archi>>nom ) {
		++n;
	}
	
	cout<<n<<endl;
	
	int i=0;
	while( i<n ) {
		
		if(getline(archi,nom) ){
		cout<<nom<<endl;
		}
		
		++i;
	}
	
	cout<<endl<<"n = "<<n;
	
	return 0;
}

