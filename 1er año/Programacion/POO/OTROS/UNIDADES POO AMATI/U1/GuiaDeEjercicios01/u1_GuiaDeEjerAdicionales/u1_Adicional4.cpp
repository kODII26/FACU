#include <iostream>
#include <vector>
using namespace std;

struct alumno {
	char nombre[50];
	int dni, edad, calificacion;
};

alumno busca_mayor(const vector<alumno> &v,int N,bool puntero_func(alumno,alumno)) {
	alumno mayor = v[0];
	for(int i=1;i<N;++i) {
		
		if(puntero_func(mayor,v[i])) {
			mayor = v[i];
		}
		
	}
	return mayor;
}

bool MayorEdad(alumno a1,alumno a2) {
	return a1.edad<a2.edad;
}

bool MayorCalificacion(alumno a1,alumno a2) {
	return a1.calificacion<a2.calificacion;
}
bool MayorNombre(alumno a1,alumno a2) {
	return a1.nombre<a2.nombre;
}

bool MayorDni(alumno a1,alumno a2) {
	return a1.dni<a2.dni;
}
int main() {
	int N;
	cout<<"Ingrese tamaño del arreglo: ";cin>>N;
	vector<alumno> v(N);
	for(size_t i=0;i<v.size();++i) {
		cout<<"Alumno"<<i<<"_nombre: ";cin>>v[i].nombre;
		cout<<"Alumno"<<i<<"_calificacion: ";cin>>v[i].calificacion;
		cout<<"Alumno"<<i<<"_edad: ";cin>>v[i].edad;
	}
	
	alumno e = busca_mayor(v,N,MayorEdad);
	alumno c = busca_mayor(v,N,MayorCalificacion);
	alumno n = busca_mayor(v,N,MayorNombre);
	
	cout<<"El alumno de mayor edad es: "<< e.nombre <<" con "<<e.edad<<" años."<<endl;
	cout<<"El alumno de mayor calificación es: "<< c.nombre <<" con "<<c.calificacion<<" de nota."<<endl;
	cout<<"El alumno de mayor nombre es: "<< n.nombre <<endl;
	return 0;
}

