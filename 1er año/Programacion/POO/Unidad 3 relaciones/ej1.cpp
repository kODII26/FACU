#include <iostream>
using namespace std;
class Persona {
	string m_nombre;
	int m_dni,m_anionac;
	char m_ec;
public: 
	Persona (string nombre, int dni, int anionac, char ec) : m_nombre(nombre),m_dni(dni),m_anionac(anionac),m_ec(ec){}
	int Edad (int anioact) {
		return anioact-m_anionac;
	}
	~Persona () {cout<<"se borro una persona";}
};
class Alumno: public Persona{
	float m_prom;
	int m_mataprob;
public:
	Alumno (string nombre, int dni, int anionac, char ec, float prom, int mataprob) : Persona(nombre,dni,anionac,ec) {
		m_prom = prom, m_mataprob = mataprob;
	}
	float MeritoAcademico() {
		return m_prom*m_mataprob;
	}
	~Alumno () {cout<<"se borro un alumno ";}
};
class Docente : public Persona {
	int m_anioing;
public:
	Docente (string nombre, int dni, int anionac, char ec, int anioing): Persona(nombre,dni,anionac,ec),m_anioing(anioing) { }
	int Antiguedad(int anioact) {
		return anioact-m_anioing;
	}
	~Docente () {cout<<"se borro un docente";}
};
int main() {
	int anioact= 2023;
	Persona p("justo",45507013,2004,'s');
	Alumno q("juan",123,2006,'c',8.5,10);
	cout<<q.MeritoAcademico();
	return 0;
}

