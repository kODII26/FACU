#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Contacto {
	string nombre;
	int numero;
};

class Practica {
	vector<Contacto> v;
public:
	Practica(vector<Contacto> m) : v(m) {}
	
	void EscribirArchivo( ofstream &archi ) {
		for( size_t i=0; i<v.size(); ++i ) {
			archi<<v[i].nombre<<endl;
			archi<<v[i].numero<<endl;
		}
	}
	
	void LeerArchivo( ifstream &archi ) {
		string nom,nom2;
		int num;
		

		while( getline(archi,nom) or archi>>num ){
			
			if (getline(archi,nom2) and archi>>num) {//¿por qué no anda el getline?
				cout<<"true: "<<nom2<<endl;
				cout<<"true: "<<num<<endl;
			}else{
				cout<<"false"<<endl;
			}
			
		}
		
	}
};

int main() {
	vector<Contacto> v(2);
	for(size_t i=0;i<v.size();++i) {
		cout<<"Ingrese nombre["<<i<<"]: ";getline(cin,v[i].nombre);
		cout<<"Ingrese su numero: ";cin>>v[i].numero;
		cin.ignore();
	}
	
	ofstream archi("archivo_de_practica.txt",ios::trunc);
	if( !archi.is_open() ){
		cout<<"1:no se pudo abrir el archivo.";
		return 1;
	}
	ifstream archi2("archivo_de_practica.txt");
	if( !archi2.is_open() ){
		cout<<"2:no se pudo abrir el archivo.";
		return 1;
	}
	
	Practica p(v);	
	
	p.EscribirArchivo(archi);
	p.LeerArchivo(archi2);
	
	return 0;
}

