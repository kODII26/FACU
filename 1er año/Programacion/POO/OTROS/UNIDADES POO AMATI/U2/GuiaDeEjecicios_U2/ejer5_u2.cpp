#include <iostream>
#include <vector>
using namespace std;

class Alumno {
	vector<float> nta;
	vector<string> nom;
public:
	Alumno(int N) {
		nta.resize(N);
		nom.resize(N);
	}
	
	void Cargar(float nota,string nombre,int i) {
		nta[i] = nota;
		nom[i] = nombre;
	}
	
	void AgregarAlum(string nombre,float nota){
		nta.resize(nta.size()+1);
		nom.resize(nom.size()+1);
		nta[nta.size()-1] = nota;
		nom[nom.size()-1] = nombre;
	}
	
	float VerProm(){
		float prom=0;
		for(size_t i=0; i<nta.size(); ++i) {
			prom += nta[i];
		}
		prom = prom/nta.size();
		return prom;
	}
	
	void VerMejorAlumno() {
		float mejorNota=0;
		string mejorNombre;
		
		for(size_t i=0; i<nta.size(); ++i) {
			if(mejorNota < nta[i]) {
				mejorNota = nta[i];
				mejorNombre = nom[i];
			}
		}
		
		cout<<"El alumno "<<mejorNombre<<" fue quien consiguió la nota más alta(nota = "
			<<mejorNota<<")."<<endl;
	}
	
	
	void VerCurso() {
		for(size_t i=0;i<nom.size();++i) {
			cout<<"integrante["<<i+1<<"]: 	"<<nom[i]<<"_______nota: "<<nta[i]<<endl;
		}
		cout<<endl;
	}
};

class Curso : public Alumno {
	string m_nom;
public:
	Curso(int N,string nom) : Alumno(N) {
		m_nom = nom;
	}
	
	string NombreCurso() { return m_nom; }
};


int main() {
	string nom;
	float nota;
	int N;
	cout<<"Nombre del curso1: ";cin>>nom;
	cout<<"Indique cantidad de estudiantes que posee: ";cin>>N;
	Curso c(N,nom);
	int i=0;
	while(i < N){
		cout<<"indique nombre del alumno: ";cin>>nom;
		cout<<"indique nota: ";cin>>nota;
		c.Cargar(nota,nom,i);
		
		i++;
	}
	
	c.VerMejorAlumno();
	cout<<"Promedio del curso: "<<c.VerProm()<<endl;
	string op;
	cout<<"desea agregar alumno nuevo?(si-no): ";cin>>op;
	if(op=="si") {
		cout<<"Nombre: ";cin>>nom;
		cout<<"Nota: ";cin>>nota;
		c.AgregarAlum(nom,nota);
	}
	
	cout<<endl<<"*******************************************"<<endl;
	cout<<"Indique nombre del curso2: ";cin>>nom;
	cout<<"Indique cantidad de estudiantes que posee: ";cin>>N;
	Curso b(N,nom);
	i=0;
	while(i < N){
		cout<<"indique nombre del alumno: ";cin>>nom;
		cout<<"indique nota: ";cin>>nota;
		b.Cargar(nota,nom,i);
		
		i++;
	}
	b.VerMejorAlumno();
	cout<<"Promedio del curso: "<<b.VerProm()<<endl;
	
	cout<<"desea agregar alumno nuevo?(si-no): ";cin>>op;
	if(op=="si") {
		cout<<"Nombre: ";cin>>nom;
		cout<<"Nota: ";cin>>nota;
		b.AgregarAlum(nom,nota);
	}
	
	cout<<"CURSO: "<<c.NombreCurso()<<endl;
	c.VerCurso();
	cout<<endl;
	cout<<"CURSO: "<<b.NombreCurso()<<endl;
	b.VerCurso();
	return 0;
}

