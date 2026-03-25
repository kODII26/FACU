#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

class Persona {
	string m_nom,m_ape;
	string m_d,m_m,m_a;

public:
	Persona(string nom,string ape,string d,string m,string a) : m_nom(nom),m_ape(ape),m_d(d),m_m(m),m_a(a) {}
	string VerNom() { return m_nom; }
	string VerApe() { return m_ape; }
	string VerDia() { return m_d; }
	string VerMes() { return m_m; }
	string VerAnio() { return m_a; }
};

class RecursosHumanos {
	vector<Persona> m_v;
	string m_nomArchi;
	int m_n;
public:
	RecursosHumanos(vector<Persona> &v, string nomArchi) : m_v(v),m_nomArchi(nomArchi),m_n(v.size()) {}
	
	void GuardarDatos() {
		ofstream arch(m_nomArchi,ios::binary|ios::trunc);
		
		for(int i=0;i<m_n; ++i) {
			string todo =  m_v[i].VerNom()+" "+m_v[i].VerApe()+" "+m_v[i].VerDia()+"/"+m_v[i].VerMes()+"/"+m_v[i].VerAnio();
			char data[356];
			strcpy(data, todo.c_str());
			arch.write(reinterpret_cast<char*>(&data), sizeof(data));
		}
		arch.close();
	}
	
	void CargarDatos() {
		ifstream arch(m_nomArchi,ios::binary);
		
		for(int i=0;i<m_n; ++i) {
			char data[356];
			arch.read(reinterpret_cast<char*>(&data), sizeof(data));
			cout<<data<<endl;
		}
	}
	
	void AgregarPersona() {
		string nom,ape,d,m,a;
		cout<<"Nombre: ";cin>>nom;
		cout<<"Apellido: ";cin>>ape;
		cout<<"Dia: ";cin>>d;
		cout<<"Mes: ";cin>>m;
		cout<<"Año: ";cin>>a;
		m_v.push_back(Persona(nom,ape,d,m,a));
		++m_n;
		GuardarDatos();
		
	}
	
	void EliminarPersona() {
		string x;
		int pos = -1;
		cout<<"Ingrese nombre o apellido a eliminar: ";cin>>x;
		for(int i=0;i<m_n;++i) {
			if( x == m_v[i].VerNom() or x == m_v[i].VerApe() ) {
				pos = i;
			}
		}
		if( pos != -1 ){
			for(int i=pos; i<m_n-1; ++i) {
				m_v[i] = m_v[i+1];
			}
			
			--m_n;
		}
		
		GuardarDatos();
		
	}
	
	int VerCantDePersonas() {
		return m_n;
	}
};

int main() {
	vector<Persona> v;
	v.push_back(Persona("matias","amati","30","6","2004"));
	v.push_back(Persona("juan","perez","24","9","1998"));
	v.push_back(Persona("Pepe","rodol","19","12","1999"));
	
	RecursosHumanos r(v,"Archivo.poo");
	r.GuardarDatos();
	r.CargarDatos();
	cout<<"*******************"<<endl;
	r.AgregarPersona();
	r.CargarDatos();
	cout<<"*******************"<<endl;
	r.EliminarPersona();
	r.CargarDatos();
	
	cout<<endl<<"cantidad: "<<r.VerCantDePersonas()<<endl;
	return 0;
}

