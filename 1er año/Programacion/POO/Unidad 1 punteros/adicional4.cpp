#include <iostream>
using namespace std;
struct alumno{
	string nombre;
	int dni, edad, calificacion;
};
alumno mayEdad(alumno *v, int cant) {
	alumno mayor;
	mayor.edad = 1;
	for (int i=0;i<cant;i++){
		if (v[i].edad > mayor.edad){
			mayor.nombre= v[i].nombre;
			mayor.dni= v[i].dni;
			mayor.edad=v[i].edad;
			mayor.calificacion=v[i].calificacion;
		}
	}
	return mayor;
}
alumno mejNota (alumno *v, int cant){
	alumno m;
	m.calificacion = 0;
	for (int i=0;i<cant;i++){
		if (v[i].calificacion > m.calificacion){
			m.nombre= v[i].nombre;
			m.dni= v[i].dni;
			m.edad=v[i].edad;
			m.calificacion=v[i].calificacion;
		}
	}
	return m;
}
alumno primNombre (alumno *v, int cant){
	alumno mayor;
	mayor.nombre = "a";
	for (int i=0;i<cant;i++){
		if (v[i].nombre > mayor.nombre){
			mayor.nombre= v[i].nombre;
			mayor.dni= v[i].dni;
			mayor.edad=v[i].edad;
			mayor.calificacion=v[i].calificacion;
		}
	}
	return mayor;
}
void busca_mayor (alumno *v, int cant, char opcion) {
	if (opcion=='a') {
		alumno a= mayEdad(v,cant);
		cout<<" los datos del alumno mas grande del curso son: "<<endl<<" Nombre: "<<a.nombre<<endl<<" Edad: "<<a.edad<<endl<<" Dni: "<<a.dni<<endl<<" Calificacion: "<<a.calificacion<<endl;
	}
	if (opcion=='b'){
		alumno a= mejNota(v,cant);
		cout<<" los datos del alumno con mejor nota del curso son: "<<endl<<" Nombre: "<<a.nombre<<endl<<" Edad: "<<a.edad<<endl<<" Dni: "<<a.dni<<endl<<" Calificacion: "<<a.calificacion<<endl;
	} else {
		alumno a= primNombre(v,cant);
		cout<<" los datos del primer alumno del curso son: "<<endl<<" Nombre: "<<a.nombre<<endl<<" Edad: "<<a.edad<<endl<<" Dni: "<<a.dni<<endl<<" Calificacion: "<<a.calificacion<<endl;
	}
}

int main() {
	int cant=2;
	alumno *v = new alumno[cant];
	for (int i=0;i<cant;i++){
		cout<<" nombre dni edad y calificacion"<<endl;
		cin>>v[i].nombre>>v[i].dni>>v[i].edad>>v[i].calificacion;
	}
	cout<<"Quiere ordenar los alumnos por a) edad b) calificacion c) nombre alfabeticamente"<<endl;
	char opc;
	cin>>opc;
	busca_mayor (v,cant,opc);
	
	return 0;
}

