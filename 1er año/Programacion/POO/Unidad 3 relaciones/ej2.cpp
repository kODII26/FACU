#include <iostream>
#include <vector>
using namespace std;
class Persona {
	string m_nombre;
	int m_dni;
public: 
	Persona (string nombre, int dni) : m_nombre(nombre),m_dni(dni){}
	string getNombre () {return m_nombre;}
	int getDni() {return m_dni;}
	void redNombre (string n) {
		m_nombre = n;
	}
	void redDni (int d) {
		m_dni = d;
	}
	virtual void mostrarDatos () {
		cout<<"Nombre: "<<m_nombre<<endl<<"Dni: "<<m_dni;
	}
	 ~Persona () {cout<<"se borro una persona"<<endl;}
};

class Alumno: public Persona{
	float m_prom;
public:
	Alumno (string nombre, int dni,float prom) : Persona(nombre,dni) {
		m_prom = prom;
	}
	int getProm () {return m_prom;}
	void mostrarDatos () override {
		cout<<"Nombre: "<<getNombre()<<" - dni: "<<getDni()<<" - prom: "<<m_prom;
	}
	void redProm(float p) {m_prom =p;}
	~Alumno () {cout<<"se borro un alumno"<<endl;}
};

class Docente : public Persona {
public:
	Docente (string nombre, int dni): Persona(nombre,dni) { }
	~Docente () {cout<<"se borro un docente"<<endl;}
};

class Curso {
	string m_nombreC;
	Docente m_c;
	vector<Alumno> m_v;
public:
	Curso (string nombreC,Docente c) : m_nombreC(nombreC),m_c(c) {}
	void AgregarAlumno (Alumno a) {
		m_v.push_back(a);
	}
	Alumno MejorPromedio () {
		Alumno may(m_v[0]);
		for (size_t i=1;i<m_v.size();i++){
			if (m_v[i].getProm() > may.getProm()) {
				may.redDni(m_v[i].getDni());
				may.redNombre(m_v[i].getNombre());
				may.redProm(m_v[i].getProm());
			}
		}
		return may;
	}
	~Curso () {cout<<"se borro un curso"<<endl;}
};
int main() {
	Docente p("pablo novara",999);
	Curso q("POO",p);
	string opc;
	int c=0;
	while ((opc != "NO") & (c<50)){
		string n; int d; float p;
		cout<<"Ingrese nombre dni y prom del alumno a agregar"<<endl;
		cin>>n>>d>>p;
		Alumno a(n,d,p);
		q.AgregarAlumno(a);
		cout<<"Desea agregar otro alumno?"<<endl;
		cout<<"SI o NO"<<endl;
		cin>>opc;
		c++;
	}

	Alumno mejP= q.MejorPromedio();
	cout<<"El alumno con mejor promedio es: "<<endl;
	mejP.mostrarDatos();
	
	return 0;
}

