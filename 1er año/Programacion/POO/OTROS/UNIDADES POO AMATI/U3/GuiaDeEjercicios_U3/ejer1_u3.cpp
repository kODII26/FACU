#include <iostream>
#include <vector>
using namespace std;

class Persona {
	string m_apellido,m_nombre,m_estCivil;
	int m_dni,m_anioN;
public:
	Persona(string ape,string nom,string estC,int dni,int anioN) 
	: m_apellido(ape), m_nombre(nom), m_estCivil(estC), m_dni(dni), m_anioN(anioN){}
	
	int Edad(int hoy) { return hoy-m_anioN; }//está mal planteado el cálculo de la edad.
	string VerNombre() { return m_nombre; }
	string VerApellido() { return m_apellido; }
	string VerEstadoCivil() { return m_estCivil; }
	int VerDNI() { return m_dni; }
	
	virtual void EjecutarData()=0;
	
};

class Alumno : public Persona {
	float m_cantAprob,m_prom;
public:
	Alumno(string ape,string nom,string estC,int dni,int anioN,float cantAprob,float prom) 
	: Persona(ape,nom,estC,dni,anioN) {
		m_cantAprob = cantAprob;
		m_prom = prom;
	}
	void EjecutarData() { cout<<"Mérito académico: "<< m_prom*m_cantAprob <<endl; }
};

class Docente : public Persona {
	int m_fechaIngreso,m_hoy;
public:
	Docente(string ape,string nom,string estC,int dni,int anioN,int fechaIngreso,int hoy) 
		: Persona(ape,nom,estC,dni,anioN) {
		m_fechaIngreso = fechaIngreso;
		m_hoy = hoy;
		
	}
	void EjecutarData() { cout<<"antiguedad: "<<m_hoy-m_fechaIngreso<<endl; }
};


void ArrojarData(vector<Persona*> &v,int i,int hoy) {
	cout<<"1.nombre: "<<v[i]->VerNombre()<<endl;
	cout<<"2.apellido: "<<v[i]->VerApellido()<<endl;
	cout<<"3.est. civil: "<<v[i]->VerEstadoCivil()<<endl;
	cout<<"4.DNI: "<<v[i]->VerDNI()<<endl;
	cout<<"5.edad: "<<v[i]->Edad(hoy)<<endl;
	
	cout<<"6.";v[i]->EjecutarData();
	
	cout<<endl<<endl;
}




int main() {
	
	vector<Persona*> v;
	int hoy;
	cout<<"Ingrese el año actual: ";cin>>hoy;
	
	v.push_back(new Alumno("Amati","Matias","soltero",49349839,2004,6,78));
	v.push_back(new Docente("Perez","Juan","casado",89898989,1967,2003,hoy));
	
	int i;
	do{
		cout<<"Elija nro de info para Alumno(0) o Docente(1): ";cin>>i;
		
		ArrojarData(v,i,hoy);
		
		cout<<"Ingrese enter para repetir."<<endl;
		
	} while(cin.get()=='\n');
	
	for(Persona *p:v) delete [] p;
	
	return 0;
}

