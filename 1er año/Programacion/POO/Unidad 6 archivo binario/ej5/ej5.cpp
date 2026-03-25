#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
class Puntuaciones {
	string m_nombre;
	int m_cant;
	vector<int> m_v;
public:
	Puntuaciones (string nombre): m_nombre(nombre) { }
	void getCantidad () {
		ifstream archi(m_nombre,ios::binary|ios::ate);
		int cant = archi.tellg()/sizeof(int);
		m_cant= cant;
		archi.seekg(0);
		for (int i=0;i<cant;++i){
			int n;
			archi.read(reinterpret_cast<char*>(&n),sizeof(n));
			m_v.push_back(n);
		};
		archi.close();
	}

	void agregarPunt (int new_puntaje) {
		int pos=0;
		ifstream archi2(m_nombre,ios::binary);
		for (int i=0;i<m_cant;++i){
			int x;
			archi2.read(reinterpret_cast<char*> (&x),sizeof(x));
			if (new_puntaje<x) {
				pos++;
			}
		}
		cout<<"POSICION"<<pos<<endl;
		archi2.close();
		ofstream archi3(m_nombre,ios::binary);
		for (int i=0;i<pos;++i){
			archi3.write(reinterpret_cast<char*>(&m_v[i]),sizeof(m_v[i]));
		}
		archi3.write(reinterpret_cast<char*>(&new_puntaje),sizeof(new_puntaje));
		for (int i=pos;i<m_cant;++i){
			archi3.write(reinterpret_cast<char*>(&m_v[i]),sizeof(m_v[i]));
		}
		archi3.close();
	}
	void verTabla() {
		ifstream archi4(m_nombre,ios::binary|ios::ate);
		int c = archi4.tellg()/sizeof(int);
		archi4.seekg(0);
		for (int i=0;i<c;++i){
			int f;
			archi4.read(reinterpret_cast<char*>(&f),sizeof(f));
			cout<<f<<endl;
		}
	}

};


int main() {
	Puntuaciones q("TablaPuntuaciones.poo");
	q.getCantidad();
	cout<<"La tabla de puntuaciones se encuentra asi:" <<endl;
	q.verTabla();
	cout<<"Cual fue su puntuacion"<<endl;
	int punt;cin>>punt;
	q.agregarPunt(punt);
	cout<<"Tabla actualizada con tu puntuacion: "<<endl;
	q.verTabla();

	return 0;
}

