#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Alumno {
	string nom;
	int nt1,nt2;
	float prom;
};

int main() {
	//a)cambiar las dos notas de un alumno.
	ifstream archi("u5-lista-ej2.txt");
	if( !archi.is_open() ){
		cout<<"no se pudo abrir el archivo."<<endl;
		return 1;
	}
	Alumno a;
	vector<Alumno> v;
	
	
	
	while( getline(archi,a.nom) and archi>>a.nt1>>a.nt2) {
		archi.ignore();
		v.push_back(a);
	}
	
	string nombre;
	int n1,n2;
	cout<<"Ingrese nombre del alumno: ";getline(cin,nombre);cin.ignore();
	cout<<"Indique nota 1: ";cin>>n1;
	cout<<"Indique nota 2: ";cin>>n2;
	
	ofstream archi2("u5-lista-ej2.txt");
	
	for( size_t i=0; i<v.size(); ++i ) {
		if( v[i].nom == nombre ){
			archi2<<nombre<<endl;
			archi2<<n1<<"	"<<n2<<endl;
		}else {
			archi2<< v[i].nom <<endl;
			archi2<< v[i].nt1 <<"	"<< v[i].nt2 <<endl;
		}
	}

	///b)poner el promedio en vez de las notas en un archivo nuevo.
	ofstream arch("promedios.txt");
	if( !arch.is_open() ){
		cout<<"No se puso abrir el archivo"<<endl;
		return 1;
	}
	

	while( getline(archi,a.nom) and archi>>a.nt1>>a.nt2) {
		archi.ignore();
		a.prom = (a.nt1+a.nt2)/2;
		v.push_back(a);
	}
	
	for( size_t i=0; i<v.size(); ++i ) {
		arch << v[i].nom <<endl;
		arch << (v[i].nt1+v[i].nt2)/2 <<endl;
	}
	
	return 0;
}

