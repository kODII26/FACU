#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;
struct Persona {
	char nyp[256];
	int anio;
};
class RecursosHumanos {
	vector<Persona> m_v;
public:
	RecursosHumanos () {}
	RecursosHumanos (Persona p){
		m_v.push_back(p);
	}
	void guardarEnArch() {
		ofstream archi("NuevaBaseDeDatos.poo",ios::binary|ios::trunc);
		for (size_t i=0;i<m_v.size();++i){
			Persona p= m_v[i];
			archi.write(reinterpret_cast<char*>(&p),sizeof(Persona));
			//cout<<m_v[i].nyp<<" "<<m_v[i].anio<<endl;
		}
		archi.close();
	}
	void cargarDesdeArch(string nombrearch) {
		ifstream archi2("NuevaBaseDeDatos.poo", ios::binary);
		Persona p;
		archi2.read(reinterpret_cast<char*>(&p),sizeof(Persona));
		cout<<"***********"<<p.nyp<<" "<<p.anio<<endl;
		archi2.close();
	}
	void verVector () {
		for (size_t i=0;i<m_v.size();++i){
			cout<<m_v[i].nyp<<"  "<<m_v[i].anio<<endl;
		}
	}
	void agregarPers(Persona h) {
		m_v.push_back(h);
	}
	void eliminarPers (string nyp) {
		int pos=0;
		for (size_t i=0;i<m_v.size();++i){
			if (m_v[i].nyp==nyp){
				pos =i;
				break;
			}
		}
		for (size_t i=pos;i+1<m_v.size();++i){
			m_v[i] = m_v[i+1];
		}
		m_v.resize(m_v.size()-1);
	}
	int cantPersonas () {return m_v.size();}
};

int main() {
	string nombre= "Luis alberto";
	
	Persona p; p.anio=2006;
	strcpy(p.nyp,nombre.c_str());
	
	RecursosHumanos q(p);
	//cout<<" vector: "<<endl;
	//q.verVector();
	q.guardarEnArch();
	q.cargarDesdeArch("NuevaBaseDeDatos.poo");
	cout<<"------------------"<<endl;
	q.verVector();

	return 0;
}

