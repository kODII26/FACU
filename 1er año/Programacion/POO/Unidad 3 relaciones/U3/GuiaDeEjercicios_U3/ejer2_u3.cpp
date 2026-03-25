//EJERCICIO INCOMPLETO

#include <iostream>
#include <vector>
using namespace std;

class Curso {
	string m_nombre, m_nomC;
	int m_dni;
public:
	Curso(string nombre,string nomC,int dni) : m_nombre(nombre), m_nomC(nomC), m_dni(dni) {}
	
	string NomCurso() { return m_nomC; }//nombre del curso.
	string VerNombre() { return m_nombre; }//nombre del docente o estudiante.
	int VerDni() { return m_dni; }
	virtual int VerNota() { return 0; } ;
};

class Estudiante : public Curso {
	int m_nota;
public:
	Estudiante (string nom,string nomC, int dni, int nota) : Curso(nom,nomC,dni) {
		m_nota = nota;
	}
	
	int VerNota() { return m_nota; }
};

class Docente : public Curso {
public:
	Docente(string nom,string nomC,int dni) : Curso(nom,nomC,dni) {}
};


vector<Curso*> CargarDatos(vector<Curso*> &v) {
	string nombre,nomC;
	int dni;
	cout<<"Ingrese nombre del curso: ";cin>>nomC;
	cout<<"Ingrese el nombre del Docente: ";cin>>nombre;
	cout<<"Ingrese DNI: ";cin>>dni;
	v.push_back(new Docente(nombre,nomC,dni));
	
	int nota, i=1, op=1;
	while( i<51 and op==1){
		cout<<"Ingrese el nombre del estudiante de "<<v[0]->NomCurso()<<" nro["<<i<<"]: ";cin>>nombre;
		cout<<"Ingrese DNI: ";cin>>dni;
		cout<<"Ingrese la nota del alumno: ";cin>>nota;
		v.push_back(new Estudiante(nombre,nomC,dni,nota));
		i++;
		if(i != 51) {
			cout<<"desea agregar alumno?(SI:1 o NO:0) op = ";cin>>op;
		}
	}
	
	return v;
}

int MejorA(vector<Curso*> &v) {
	int mejorN = 0;
	int mejorA = 1;
	for(size_t i=1; i<v.size(); i++) {
		if(mejorN < v[i]->VerNota()) {
			mejorN = v[i]->VerNota();
			mejorA = i;
		}
	}
	
	return mejorA;
}

int main() {
	//se puede meter eco y hum dentro de un vector?
	vector<Curso*> A;
	vector<Curso*> B;
	A = CargarDatos(A);
	B = CargarDatos(B);

	//se necesita saber si un alumno debe tener dos calificaciones del curso o estar en varios cursos para sacar un promedio(solo dice: "alumno de mejor promedio" :( ).
	//				si se da el caso de alguno de los dos planteos, no sé hacerlo.Para lograrlo el alumno debe estar en la misma posicion de los vectores de cada curso.
	
	int a1 = MejorA(A);
	int b1 = MejorA(B);
	
	if( B[b1]->VerNota() > A[a1]->VerNota() ) {
		cout<<"El mejor Alumno es "<< B[b1]->VerNombre() <<"("<<A[a1]->VerDni()<<") del curso "<< B[b1]->NomCurso() <<", con una calificación = "<< B[b1]->VerNota()<<endl;
	}else {
		cout<<"El mejor Alumno es "<< A[a1]->VerNombre() <<"("<<A[a1]->VerDni()<<") del curso "<< A[a1]->NomCurso() <<", con una calificación = "<< A[a1]->VerNota()<<endl;
	}
	
	
	return 0;
}
 
