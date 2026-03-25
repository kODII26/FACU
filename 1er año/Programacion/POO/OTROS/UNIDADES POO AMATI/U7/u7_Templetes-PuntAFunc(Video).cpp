#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


/* *********************************************************************************************************************/
//PRIMER EJEMPLO CON TEMPLATES.

template<typename T>
class Binario {
	fstream archi;
public:
	Binario(string nombre) : archi(nombre,ios::trunc|ios::binary|ios::in|ios::out) {}
	int Cant();
	T Ver(int i);
	void Agregar(T f);
	void Modificar(int i, T f) {
		archi.seekp(i*sizeof(T));
		archi.write(reinterpret_cast<char*>(&f), sizeof(T));
	}
};

template<typename T>
int Binario<T>::Cant() {
	archi.seekg(0,ios::end);
	return archi.tellg()/sizeof(T);
}

template<typename T>
T Binario<T>::Ver(int i) {
	archi.seekg(i*sizeof(T));
	T x;
	archi.read(reinterpret_cast<char*>(&x), sizeof(x));
	return x;
}

template<typename T>
void Binario<T>::Agregar(T f) {
	archi.seekp(0,ios::end);
	archi.write(reinterpret_cast<char*>(&f), sizeof(f));
	cout<<"se agregó el-> "<< f <<endl;
}


int main() {
	Binario<float> b("documento.poo");// cambiar el float por char,int,double.(no por variables dinámicas como el string porque actua el write y read)
	
	
	b.Agregar(3.3);
	b.Agregar(3.2);
	b.Agregar(3.1);
	
	
	
	cout<< "Hay " << b.Cant() << " floatantes" <<endl;
	for(int i=0; i<b.Cant(); ++i) {
		cout<< b.Ver(i) <<endl;
	}
	
	
	return 0;
}


/* *********************************************************************************************************************/
//TEMPLATES ANIDADOS.
/*
template<typename T1,typename T2>
struct Par {
	T1 primero;
	T2 segundo;
};

int main() {
	Par<string,double> p;
	p.primero = "hola";
	p.segundo = 3.14;
	
	cout<<p.primero;
	return 0;
}

*/

/* *********************************************************************************************************************/
//PUNTERO A FUNCION QUE COMPARA.(con puntero de tipo T2)
/*
struct Alumno {
	string nom;
	float prom;
	int fnac;
};


template<typename T,typename T2>
T menor(const vector<T> &v, T2 puntero_a_funcion_que_compara ) { // con T2 se tipea más fácil(sigue siendo un puntero)
	T men(v[0]); //variable menor de tipo T incializada con el primer Alumno
	for( size_t i=1; i<v.size(); ++i ){
		if( puntero_a_funcion_que_compara(v[i],men) ){//llama a la funcion a la que apunta
			men = v[i];
		}
	}
	return men;//retorna el menor de toda la comparación
}


bool compara_fecha(const Alumno &a1, const Alumno &a2) {
	return a1.fnac > a2.fnac; // el de menor edad tiene fecha más grande
}

bool compara_prom(const Alumno &a1, const Alumno &a2) {
	return a1.prom < a2.prom;
}

bool compara_nom(const Alumno &a1, const Alumno &a2) {
	return a1.nom < a2.nom;
}



int main() {
	vector<Alumno> v(3);
	
	for( int i=0; i<3; ++i ) {
		cout<<"nombre["<<i<<"]: ";cin>>v[i].nom;
		cout<<"prom: ";cin>>v[i].prom;
		cout<<"fnac: ";cin>>v[i].fnac;
	}
	
	Alumno menor_edad = menor(v, compara_fecha);// menor( vector<Alumno>, direccion de la funcion )
	Alumno menor_prom = menor(v, compara_prom);
	Alumno menor_nom = menor(v, compara_nom);
	
	
	cout<<"El de menor edad(="<<menor_edad.fnac<<") es: "<< menor_edad.nom << endl;
	cout<<"El de menor promedio es(="<<menor_prom.prom<<"): "<< menor_prom.nom << endl;
	cout<<"El de menor(a<z) nombre es: "<< menor_nom.nom << endl;
	return 0;
}
*/

/* *********************************************************************************************************************/
