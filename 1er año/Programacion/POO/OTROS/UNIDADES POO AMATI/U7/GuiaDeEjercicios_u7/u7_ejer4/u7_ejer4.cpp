#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
class ManejadorArchivo {
	fstream m_archi;
	string m_nomArchi;
	vector<T> m_v;
public:
	ManejadorArchivo(string nomA,vector<T> &v) : m_archi(nomA,ios::trunc|ios::binary|ios::in|ios::out) {
		m_nomArchi = nomA;
		m_v = v;
	}
	
	void CargarRegistro() {
		cout<<"CARGANDO..."<<endl;
		for(size_t i=0;i<m_v.size();++i) {
			T val = m_v[i];
			cout<<val<<"  ";
			m_archi.write(reinterpret_cast<char*>(&val), sizeof(T));
		}
	}
	
	T VerEnPos(int pos) {
		m_archi.seekg(pos*sizeof(T));
		T val;
		m_archi.read(reinterpret_cast<char*>(&val), sizeof(T));
		return val;
	}
	
	void ModificarEnPos(int pos) {
		m_archi.seekp(pos*sizeof(T));
		T val;
		cout<<"Ingrese valor para insertar en la pos["<<pos<<"]: ";cin>>val;
		m_v[pos] = val;
		m_archi.write(reinterpret_cast<char*>(&val), sizeof(T));
	}
};

template<typename T>
vector<T> v(int n){
	
	return v;
}

int main() {
	vector<int> v(3);
	for(size_t i=0;i<v.size();++i) {
		cout<<"Ingrese valor["<<i<<"]: ";cin>>v[i];
	}
	
	ManejadorArchivo<int> m("Registro.poo",v);
	m.CargarRegistro();
	m.ModificarEnPos(1);
		
	for(size_t i=0;i<v.size();++i) {
		cout<<"valor["<<i<<"] =  "<<m.VerEnPos(i)<<endl;
	}	
	return 0;
}

