#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
/* ********************************************************************************************************/
///CREAR UN MAP CON UN OBJETO Y CONFIRMAR SU EXISTENCIA.
/*
int main() {
	map<string,int> agenda;
	agenda["HOLA"] = 9999123;
	map<string,int>::iterator it = agenda.find("HOLA");
	if( it == agenda.end() ) {
		cout<<"No se encuentra en la agenda."<<endl;
	}else{
		cout<<"Si se encuntra "<<it->first<<": "<<it->second<<endl;
	}
	return 0;
}
*/


/* ********************************************************************************************************/
///ELIMINAR REPETIDOS CON SORT Y UNIQUE.
/*
int main() {
	vector<int> v = {6,2,5,3,99,33,2,8,2,77,77,2,8};
	for(size_t i=0;i<v.size();++i) {
		cout<<v[i]<<" ";
	}
	sort(v.begin(),v.end());
	
	cout<<endl<<endl;
	for(size_t i=0;i<v.size();++i) {
		cout<<v[i]<<" ";
	}
	
	vector<int>::iterator it = unique(v.begin(),v.end());
	
	int cant_elim = v.end()-it;
	
	v.resize(v.size()-cant_elim);
	
	cout<<endl<<endl;
	for(size_t i=0;i<v.size();++i) {
		cout<<v[i]<<" ";
	}
	
	cout<<endl<<"se eliminaron "<< cant_elim <<" elementos."<<endl;
	return 0;
}
*/
/* ********************************************************************************************************/

///EJEMPLO 1: eliminar repetidos(genérico) de un archivo binario con funciones sueltas. 
/*
Ejercicio: 
Escriba una función que reciba el nombre de un archivo binario que contenga
un conjunto de registros de un tipo genérico, y elimine del archivo todos
los registros repetidos.La funcion debe retornar la cantidad de elementos eliminados.
*/
/*
struct Alumno {
	char nombre[50], apellido[50];
	float prom;
	int fecha_nac;
};

bool operator==(const Alumno &a1, const Alumno &a2) {
	return a1.nombre==a2.nombre && a1.apellido==a2.apellido;
}


template<typename T>
int elimina_reps(string nom_arch) {

	ifstream archi_in(nom_arch,ios::binary|ios::ate);
	int n = archi_in.tellg()/sizeof(T);
	archi_in.seekg(0);
	vector<T> v(n);
	for(T &x:v)
		archi_in.read(reinterpret_cast<char*>(&x),sizeof(T));
	archi_in.close();
	
	for(size_t i=0; i<v.size(); ++i) {
		auto it2 = remove(v.begin()+i+1,v.end(),v[i]);
		v.erase(it2,v.end());
	}
	
	ofstream archi_out(nom_arch,ios::binary|ios::trunc);
	for(T &x:v)
		archi_out.write(reinterpret_cast<char*>(&x),sizeof(T));
	archi_out.close();
	
	return n-v.size();
}


int main() {
	
	elimina_reps<Alumno>("ArchivoPrueba.poo");

	return 0;
}

*/

/* ********************************************************************************************************/
///EJEMPLO 2: Actualizar un Archivo(medallero de Paises).
/*
struct Competencia {
	string nomP;
	int m1,m2,m3;
};

void actualizar_medallas( string nom_arch ) {
	ifstream arch(nom_arch,ios::binary|ios::in);
	Competencia x;
	vector<Competencia> v;
	
	while( arch>>x.m1>>x.m2>>x.m3>>x.nomP ) {
		v.push_back(x);
		cout<<x.m1<<" "<<x.m2<<" "<<x.m3<<" "<<x.nomP<<endl;
	}
	
	arch.close();
	for(int i=0;i<3;++i) {
		Competencia c;
		cout<<"Ingrese m1: ";cin>>c.m1;
		cout<<"Igrese m2: ";cin>>c.m2;
		cout<<"Igrese m3: ";cin>>c.m3;
		cout<<"Igrese nombre del Pais: ";cin>>c.nomP;
		for(size_t i=0;i<v.size();++i)  {
			if( v[i].nomP == c.nomP ) {
				v[i].m1 += c.m1;
				v[i].m2 += c.m2;
				v[i].m3 += c.m3;
			}
		}
	}
	
	ofstream archi(nom_arch,ios::binary|ios::trunc);
	
	for(size_t i=0;i<v.size();++i) {
		archi<<v[i].m1<<" "<<v[i].m2<<" "<<v[i].m3<<" "<<v[i].nomP<<endl;
	}
	archi.close();
}

int main() {
	actualizar_medallas("ArchivoPrueba.poo");
	return 0;
}
*/

/* ********************************************************************************************************/
///EJEMPLO 2: Más práctico con el uso de MAP(Actualizar Medallero).
/*
struct Medalla {
	int oro,plata,bronce;
};

void actualizar_medallas( string nom_arch ) {
	ifstream arch(nom_arch,ios::binary|ios::in);
	map<string,Medalla> v;
	int o,p,b;
	string nomP;
	while( arch>>o>>p>>b>>nomP ) {
		v[nomP].oro = o;
		v[nomP].plata = p;
		v[nomP].bronce = b;
	}
	arch.close();
	
	string nom1,nom2,nom3;
	cout<<"Ingrese el nombre del Pais que salio primero: ";cin>>nom1;
	cout<<"Ingrese el nombre del Pais que salio segundo: ";cin>>nom2;
	cout<<"Ingrese el nombre del Pais que salio tercero: ";cin>>nom3;
	
	v[nom1].oro++;
	v[nom2].plata++;
	v[nom3].bronce++;
	
	ofstream archi(nom_arch,ios::binary|ios::trunc);
	
	for( auto p=v.begin(); p!=v.end(); ++p ) {
		archi<< p->second.oro <<" "<< p->second.plata <<" "<< p->second.bronce <<" "<< p->first <<endl;
	}
	archi.close();
}

int main() {
	actualizar_medallas("ArchivoPrueba.poo");
	return 0;
}
*/

/* ********************************************************************************************************/

