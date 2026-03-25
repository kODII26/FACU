///Que es la programacion generica?
Que es programacion generica? 
	Tecnica de programacion que se enfoca en los algoritmos e ignora 
	  los tipos de datos sobre los cuales se aplican.
	El objetivo es no reescribir un mismo algoritmo o clase para distintos tipos de datos

///Primer ejemplo de plantilla	
int menor (const vector<int> &v){
	int men= v[0];
	for (size_t i=0;i<v.size();++i){
		if (v[i]<men)
			men=v[i];
	}
	return men;
}

Este algoritmo de busqueda de menor solo sirve para enteros, que pasa si queremos usarlo
 para flotantes, char , string o cualquier tipo de datos? Tendriamos que copiar y pegarlo varias veces
 mas facil es usar templates, cambiando los tipos de datos por T y agregando el template al principio

template<typename T> //Template indica que lo que sigue es una plantilla (funcion/clase generica)
T menor(const vector<T> &v){
	T men= v[0];
	for (size_t i=0;i<v.size();++i){
		if (v[i]<men)
			men=v[i];
	}
	return men; //<- Ahora este algoritmo es generico y no hace falta hacer copypaste
}

Para llamarla desde el main se hace asi;
vector<float> v;
...
float men= menor<float> (v); //<- Como el vector ya es de float, podes no poner <float> y c++ lo deduce
//En la variable donde vas a guardar al menor llamas a la funcion con el tipo de datos entre <>
// y le pasas el vector como argumento
	
///Que tipos de datos no se puede usar con template?
template<typename T>
T menor(const vector<T> &v){
	T men= v[0]; //<- Implementar constructor de copia
	for (size_t i=0;i<v.size();++i){
		if (v[i]<men)//<- Sobrecargar <
			men=v[i]; //<- Sobrecargar =
	}
	return men; 
}	
//Con esta plantilla se podria usar cualquier tipo de datos incluido struct o clases 
//	(QUE NO TENGAN PUNTEROS), lo unico que necesitarias seria implementar un
//  constructor de copia, sobrecargar el < y el =
	
///Templates de clases
//Se puede usar para declarar atributos, para declarar valores de retorno y tambien para declarar argumentos
template<typename T>
class Vector3D {
	T m_datos[3];
public:
	Vector3D();
	Vector3D operator-(const vector3D &v2);
	Vector3D operator+(const vector3D &v2);
	T operator*(const Vector3D &v2);
	T &operator[](int i);
};
//Implementar metodos afuera de la clase
template<typename T> //Para usar metodos afuera de la clase plantilla, hay que hacerlos como plantilla tmb
T &Vector3D<T>::operator[](int i){
	return m_datos[i];
}
//Y los operadores << y >> ?
//Para sobrecargar tambien tenemos que hacerlo como plantilla con template
template<typename T>
istream &operator>>(istream &i, Vector3D<T> &m);

int main(){
	Vector3D<float> m1,m2;
	cin>>m1>>m2;
	cout<<m1*m2<<endl; //cin y cout se sobrecargan si o si como funciones sueltas
}

///Primer ejemplo (Novara recomienda hacer la clase como float y luego reemplazar todo por una T)
template<typename T>
class Binario {
	fstream archi;
	//Cuando la clase esta relacionada con archivos conviene abrirla 1 sola vez en fstream
	//para no estar abriendola y cerrandola 40 veces
public:
	Binario (string nombre):archi(nombre,ios::binary|ios::in|ios::out) {}
	int Cant () {
		archi.seekg(0,ios::end); //<- ir al final del archivo sin el ios::ate
		return archi.tellg()/sizeof(T);
	}
	T Ver(int i){
		archi.seekg(i*sizeof(T));
		T f;
		archi.read(reinterpret_cast<char*>(&f),sizeof(T));
		return f;
	}
	void Agregar (T f){
		archi.seekp(0,ios::end);
		archi.write(reinterpret_cast<char*>(&f),sizeof(T));
	}
	void Modificar(int i, T f){
		archi.seekp(i*sizeof(T));
		archi.write(reinterpret_cast<char*>(&f), sizeof(T));
	}
};
int main(){
	Binario b("float.dat");
	
	b.Agregar(2.71);
	b.Modificar(4,3.14);
	
	cout<<"Hay "<<b.Cant() <<" flotantes"<<endl;
	for (int i=0;i<b.Cant();++i){
		cout<< b.Ver(i)<<endl;
	}
}
///Ejemplo de template de mas de 1 tipo
template<typename T1, typename T2>
struct Par {
	T1 primero;
	T2 segundo;
};
int main () {
	Par <string , float> p;
	p.primero ="Hola";
	p.segundo= 0.14;
	return 0;
}
	
///Punteros a funciones
template<typename T, typename T2>
T menor (const vector<T> &v, T2 punt_a_func){
	T men(v[0]);
	for (size_t i=1;i<v.size();++i){
		if (punt_a_func(v[i],men))
			men= v[i];
	}
	return men;
}

struct Alumno {
		string nom;
		float prom;
		int fnac;
};

bool compara_fecha(const Alumno &a1, const Alumno &a2){
	return a1.fnac>a2.fnac;
}
bool compara_prom(Alumno a1,Alumno a2){
	return a1.prom<a2.prom;
}	
bool compara_fecha(Alumno a1,Alumno a2){
	return a1.nom<a2.nom;
}	

int main () {
	vector<Alumno> v;
	...;
	Alumno menor_edad = menor (v, compara_fecha);
	//Como le paso una funcion como 2do argumento, c++ deduce que es un puntero a funcion
	Alumno menor_prom = menor (v, compara_prom);
	Alumno menor_nom = menor (v, compara_nom);
	return 0;
}

///Desventajas del uso de templates
*Los errores que arroja el compilador suelen ser mucho mas largos y confusos
*Una biblioteca de templates debe estar definida por completo en un .h
	(no se puede separar en .h y .cpp)




















	
	
	
	
	
	
	
	
