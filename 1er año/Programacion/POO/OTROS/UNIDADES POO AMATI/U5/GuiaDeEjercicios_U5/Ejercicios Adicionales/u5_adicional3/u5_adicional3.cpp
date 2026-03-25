#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Contacto {
	string nombre;
	int numero;
};


int ContarRenglones(string nomArchivo) {
	ifstream archi(nomArchivo);
	int N=0;
	string x;
	while( getline(archi,x) ) {
		++N;
	}
	
	return N;
}



class Agenda {
	vector<Contacto> m_v;
	int N;
public:
	void Cargar(string nomArchivo) {
		Contacto c;
		ifstream archi(nomArchivo);
		N = ContarRenglones(nomArchivo)/2;
		string x; 
		
		for( int i=0; i<N; ++i ){
			int cont =0;
			while( cont<2) { 
				if( getline(archi,x) and (cont%2)==0 ){
					c.nombre = x;
					
				}else{
					int numX;
					string x2 = x;
					istringstream iss(x2);
					iss >> numX;
					c.numero = numX;
				}
				++cont;
		
			}
			m_v.push_back(c);
			cout<<"true->"<<m_v[i].nombre<<"-"<<m_v[i].numero<<endl;
		}
		
		archi.close();
	}
	
	
	
	void Buscar( string nomX, string nomArchivo ) {
		bool encontrado = false;
		size_t i=0;
		while( i<m_v.size() and encontrado==false ){
			if ( m_v[i].nombre.find(nomX) != string::npos ){
				cout<<"contacto nro["<<i+1<<"]: "<<endl;
				cout<<"_nombre: "<<m_v[i].nombre<<endl;
				cout<<"_numero: "<<m_v[i].numero<<endl;
				encontrado = true;
			}
			++i;
		}
		
		if( encontrado == false ) {
			cout<<"El texto ingresado no pertenece a la lista de contactos."<<endl;
		}
	}
	
	
	void AgregarContacto( string nomArchivo ) {
		Contacto c;
		ofstream archi(nomArchivo,ios::trunc);
		
		cin.ignore();
		cout<<"Ingrese nuevo nombre: ";getline(cin,c.nombre);
		cout<<"Ingrese nuevo numero: ";cin>>c.numero;
		m_v.push_back(c);
		
		for(size_t i=0; i<m_v.size(); ++i) {
			archi<<m_v[i].nombre<<endl;
			archi<<m_v[i].numero<<endl;
		}
		
		
	}

};

int main() {
	string nomArchivo = "agenda.txt";
	
	Agenda a;
	
	a.Cargar(nomArchivo);
	
	string nomX;
	cout<<"Ingrese nombre o apellido a buscar: ";cin>>nomX;
	a.Buscar(nomX,nomArchivo);
	
	a.AgregarContacto(nomArchivo);
	return 0;
}

