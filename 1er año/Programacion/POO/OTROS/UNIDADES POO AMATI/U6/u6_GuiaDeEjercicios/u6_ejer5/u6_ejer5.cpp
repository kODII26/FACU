#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

struct Jugador {
	string nombre;
	int puntos;
};

int Estar( vector<Jugador> &w , string nom ) {
	for(size_t i=0; i<w.size(); ++i) {
		if(w[i].nombre == nom) {
			return 1;
		}
	}
	return 0;
}

vector<Jugador> OrdenarTabla(const vector<Jugador> &v) {
	vector<Jugador> w;
	size_t p=0;
	while( p < v.size() ) {
		int pos1,mejor=0;
		for(size_t i=0; i<v.size();++i) {
			if( mejor < v[i].puntos and Estar(w,v[i].nombre) == 0 )  {
				mejor = v[i].puntos;
				pos1 = i;
			}
		}
		
		Jugador j;
		j.nombre = v[pos1].nombre;
		j.puntos = v[pos1].puntos;
		w.push_back(j);
		
		++p;
	}
	
	return w;
}

class Juego {
	vector<Jugador> m_v;
	int m_n;
public:
	Juego(vector<Jugador> &w, int n) : m_v(w), m_n(n) {}
	
	void AgregarJugador() {
		Jugador j;
		cout<<"*********nuevo jugador***********"<<endl;
		string nom;
		int ptos;
		cout<<"Nombre: ";cin>>nom;
		cout<<"Puntos: ";cin>>ptos;
		
		int pos = 0;
		size_t i=0;
		while( i<m_v.size() ) {
			if( m_v[i].puntos > ptos ) {
				++pos;
			}
			++i;
		}
		m_v.resize(m_v.size()+1);
		
		for(int i = m_v.size(); i>pos; --i) {
			m_v[i].nombre = m_v[i-1].nombre;
			m_v[i].puntos = m_v[i-1].puntos;
		}
		
		m_v[pos].nombre = nom;
		m_v[pos].puntos = ptos;
		
	}
	
	void MostrarLista() {
		cout<<"*/*/*/**/*/***///**/*/***/*/*//*"<<endl;
		for(size_t i=0; i<m_v.size(); ++i) {
			cout<<"Nombre: "<<m_v[i].nombre<<endl;
			cout<<"Puntos: "<<m_v[i].puntos<<endl;
		}
	}
	
	void EscribirArchivo(string nom) {
		ofstream arch(nom,ios::binary);
		for(size_t i=0;i<m_v.size();++i) {
			char nom[256];
			strcpy(nom, m_v[i].nombre.c_str());
			arch.write(nom,sizeof(nom));
			arch.write(reinterpret_cast<char*>(&m_v[i].puntos), sizeof(m_v[i].puntos));
		}
		arch.close();
	}
	
	
	void LeerArchivo() {
		ifstream archi("Juego.poo",ios::binary);
		char nom[256];
		int ptos;
		for(size_t i=0;i<m_v.size();++i) {
			archi.read(reinterpret_cast<char*>(&nom),sizeof(nom));
			cout<<"Nombre: "<<nom<<endl;
			archi.read(reinterpret_cast<char*>(&ptos), sizeof(ptos));
			cout<<"Puntos: "<<ptos<<endl;
		}
		archi.close();
	}
	
};



int main() {
	int N = 2;
	Jugador x;
	vector<Jugador> v;
	
	for(int i=0; i<N; ++i) {
		cout<<"Nombre del jugador["<<i<<"]: ";cin>>x.nombre;
		cout<<"Puntos: ";cin>>x.puntos;
		
		v.push_back(x);
	}
	
	vector<Jugador> w = OrdenarTabla(v);
	
	for(size_t i=0; i<w.size(); ++i) {
		cout<<"Nombre: "<<w[i].nombre<<endl;
		cout<<"Puntos: "<<w[i].puntos<<endl;
	}
	
	Juego a(w,N);
	a.AgregarJugador();
	a.MostrarLista();
	string nom = "Juego.poo";
	a.EscribirArchivo(nom);
	cout<<endl<<"				ARCHIVO"<<endl<<endl;
	a.LeerArchivo();
	
	
	
	return 0;
}

