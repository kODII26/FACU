///THIS PARA DIFERENCIAR NOMBRES
#include <iostream>
using namespace std;

class Calculadora {
	float num;
public:
	Calculadora() { this->num = 1;}//se inicializa num del private con this->1.
	void Sum(float num) { this->num += num;}
	void Rest(float num) { this->num -= num;}
	void Mult(float num) {this->num *= num;}
	void Div(float num) { this->num /= num;}
	float Result() {return this->num;}
};

int main() {
	Calculadora calc;
	calc.Sum(9);
	calc.Rest(3);
	calc.Mult(7);
	
	cout<< calc.Result();
	return 0;
}

/* **********************************************************************************************************/
///MISMO EJEMPLO,PERO CONCATENANDO FUNCIONES
#include <iostream>
using namespace std;

class Calculadora {
	float num;
public: 
	Calculadora() {
		this->num = 0;
	}
	Calculadora &Sum(float num) {
		this->num += num;
		return *this;
	}
	Calculadora &Rest(float num) {
		this->num -= num;
		return *this;
	}
	Calculadora &Mult(float num) {
		this->num *= num;
		return *this;
	}
	
	float Result() {
		return this->num;
	}
};

int main() {
	Calculadora calc;
	cout<< calc.Sum(20).Rest(10).Mult(49).Result();
	return 0;
}

/* ***********************************************************************************************************/
///MÉTODO "CONST"
#include <iostream>
using namespace std;

class Calculadora {
	float num;
public:
	Calculadora(float num) { this->num = num; }
	Calculadora &Sum(float num) { this->num += num; return *this;}
	Calculadora &Rest(float num) { this->num -= num; return *this;}
	Calculadora &Mult(float num) {this->num *= num; return *this;}
	Calculadora &Div(float num) { this->num /= num; return *this;}
	float Result() const;//método const.(Nota:sin nada, ya que se completa por fuera del class)
};

float Calculadora::Result() const { return this->num; }//método completado.

void MostrarResultado(const Calculadora &c) {//  funcion que llama al class para obtener sus métodos(como no se modifica, es const)
	cout<<"El resultado es: "<<c.Result()<<endl;//como Result() es const(no modifica) la funcion se ejecuta cumpliendo su const.
}

int main() {
	Calculadora calc(0);
	calc.Sum(4).Rest(2).Mult(8);
	MostrarResultado(calc);
	
	return 0;
}

//Nota: Si algún const falta la función no compila.



/* ***********************************************************************************************************/
///INICIALIZACION DE MIEMBROS
#include <iostream>
#include <vector>
using namespace std;

class Curso {
	vector<int> v;//primero
	string m_nom;//segundo       	        se debe respetar el orden de inicializacion de variables:
	float m_prom;//tercero
public:
	Curso(int n,string nombre,float prom) : v(n,0),m_nom(nombre),m_prom(prom) {} //vector de n ceros,nombre,promedio(se inicializan las variables privadas.
	
	void Data() {
		cout<<"El curso "<<m_nom<<" tiene "<<v.size()<<" alumnos, con un promedio de "<< m_prom <<endl;
	}
	
	void MostrarVector() {
		for(size_t i=0; i<v.size(); ++i) {
			cout<<v[i]<<" ";
		}
		cout<<endl;
	}
};

int main() {
	Curso a(32,"Poo",73.4);// dar valores al Constructor de class
	Curso b(28,"B",78.1);//
	
	a.Data();
	b.Data();
	a.MostrarVector();
	b.MostrarVector();
	return 0;
}


/* ***********************************************************************************************************/
///STATIC(comprobación de delete)
#include <iostream>
using namespace std;

class Foo {
	static int n;//entero estático sin valor
public:
	Foo() { ++n; }//n aumenta de a uno a medida que se crean más Constructores.
	
	~Foo() { --n; }//n disminuye de a uno a medida que se destrullan los Contadores.
	
	static VerN() { return n; }//funcion static para consultar el valor de n.
};

int Foo::n=0;//se le da valor.

void func() {//funcion void normal
	Foo *v = new Foo[10];//puntero de tipo Foo que apunta a la primera pos del arreglo de Foo.(n aumenta 10 veces +1)
	delete [] v;//se eliminan todos los Foo creados.(n disminuye 10 veces -1)
}

int main() {
	
	cout<< Foo::VerN() <<endl;//como es una funcion static se la llama "así nomás".
	func();
	cout<< Foo::VerN() <<endl;
	
	return 0;
}

//Nota: si se olvida de poner delete, el resultado que arrojará la pantalla será: |	0  |(al principio no se llamó a la función func)
//                                                                                |	10 |(se olvidó el delete luego de crear el puntero Foo)

//Nota: esto solo sirve si se crean punteros y deletes fura de los constructores.(no funciona dentro de ellos). <-- ¬oJo¡!



/* ***********************************************************************************************************/
///AMISTAD de class(NO recomendado).
#include <iostream>
using namespace std;

class Calculadora {
	float num = 0;
	friend int main();//permite al main ingresar a los objetos y atributos privados de la clase
};

int main() {
	Calculadora c;
	cout<< c.num;
	return 0;
}


/* ***********************************************************************************************************/
///EJEMPLO 1) COMPOSICION 
#include <iostream>
using namespace std;

class Rueda {
	float m_tamanio1,m_tamanio2;
public:
	Rueda(float tamanio1,float tamanio2) {//se piden los datos desde Bicicleta
		m_tamanio1 = tamanio1;
		m_tamanio2 = tamanio2;
	}
	
	void MostrarTamanio() {
		cout<<"Rueda delantera: "<<m_tamanio1<<endl;
		cout<<"Rueda trasera: "<<m_tamanio2<<endl;
	}
};

class Bicicleta {
	Rueda r;//con r será posible asignarle datos al constructor de Rueda y llamar a métodos de su clase(Rueda)...
public:
	Bicicleta(float rodado1,float rodado2) : r(rodado1,rodado2){//-->... solo dentro del constructor bicicleta.
		r.MostrarTamanio();
	}
	
};


int main() {
	float rod1,rod2;
	cout<<"Indique el rodado de la rueda 1: ";cin>>rod1;
	cout<<"Indique el rodado de la rueda 2: ";cin>>rod2;
	
	Bicicleta b(rod1,rod2);
	
	return 0;
}


/* ***********************************************************************************************************/
///SEGUNDO EJEMPLO DE COMPOSICIÓN(con vector)
#include <iostream>
#include <vector>
using namespace std;

class Ruedas {
	vector<float> m_rodado;
	string m_material;
public:
	Ruedas(vector<float> rodado,string material) : m_rodado(rodado), m_material(material) {}
	void MostrarData() {
		cout<<"Las ruedas delanteras rodado "<<m_rodado[0]<<" y las traseras "<<m_rodado[1]<<", estan hechas de "<<m_material<<endl;
	}
};

class Motor {
	float m_fuerza,m_precio;
	string m_nombre;
	
public:
	Motor(float potencia,float precio,string nombre) : m_fuerza(potencia),m_precio(precio),m_nombre(nombre) {}
	void MostrarData() {
		cout<<"El motor "<<m_nombre<<" con un costo de $"<<m_precio
			<<" posee una fuerza de "<<m_fuerza<<" caballos."<<endl;
	}
};

class Auto {
	Ruedas r;
	Motor m;
public:
	Auto(vector<float> rodado,string materialR,float potencia,float precioM,string nomM)
		: r(rodado,materialR),m(potencia,precioM,nomM) {
		m.MostrarData();
		r.MostrarData();
	}
};

int main() {
	string nom,material;
	float precio,rodado1,rodado2,potencia;
	cout<<"indique nombre del motor: ";cin>>nom;
	cout<<"indique precio del motor: ";cin>>precio;
	cout<<"potencia: ";cin>>potencia;
	cout<<"material de las ruedas: ";cin>>material;
	vector<float> rodado(2);
	cout<<"rodado de ruedas delanteras: ";cin>>rodado1;
	rodado[0] = rodado1;
	cout<<"rodado de rudas traseras: ";cin>>rodado2;
	rodado[1] = rodado2;
	Auto a(rodado,material,potencia,precio,nom);
	
	
	return 0;
}

/* ***********************************************************************************************************/
///HERENCIA(ejemplo 1)
#include <iostream>
using namespace std;

class Equipo {
	string m_nom, m_localidad;
	int m_cantJ;
public:
	string VerNombre(string nom) { m_nom = nom; return m_nom; }
	string VerLocalidad(string localidad) {  m_localidad = localidad; return m_localidad; }
	int VerCantJugadores(int cantJ) { m_cantJ = cantJ; return m_cantJ; }
};

class EquipoFutbol : public Equipo {//con-> (: public Equipo), ahora EquipoFutbol posee todas las clases de Equipo, más sus propias clases.
	string m_promesa;
public: 
	string VerPromesa(string promesa) { m_promesa = promesa; return m_promesa; }
};

class EquipoVoley : public Equipo {
	string m_capitan;
public:
	string VerCapitan(string capitan) { m_capitan = capitan; return m_capitan; }
};

int main() {
	EquipoFutbol f;
	EquipoVoley v;
	string nom;
	int cantJ;
	//datos de futbol
	cout<<"Indique nombre del equipo de futbol: ";cin>>nom;
	cout<<"Indique cant de jugadores : ";cin>>cantJ;
	
	cout<<"El equipod de futbol "<<f.VerNombre(nom)<<", en la localidad de "
		<<f.VerLocalidad("Lourdez")<<" posee una cantidad de "
		<<f.VerCantJugadores(cantJ)<<" jugadores y su promesa es "<<f.VerPromesa("Matias")<<endl;
	
	//datos de voley
	string nomV;
	int cantJV;
	cout<<"Indique nombre del equipo de voley: ";cin>>nomV;
	cout<<"Indique cant de jugadores : ";cin>>cantJV;
	
	cout<<"El equipod de voleybol "<<v.VerNombre(nomV)<<", en la localidad de "
		<<v.VerLocalidad("Rincon")<<" posee una cantidad de "
		<<v.VerCantJugadores(cantJV)<<" jugadores y su capitan es "<<v.VerCapitan("Duki")<<endl;
	return 0;
}

//Nota: En herencia las clases no pueden acceder a lo provado de su clase madre.

/* ***********************************************************************************************************/
///HERENCIA Y CONSTRUCTORES.
#include <iostream>
using namespace std;

class Equipo {
	string m_nom;
public:
	Equipo(string nom){
		m_nom = nom;
	}
};

class EquipoBasquet : public Equipo {
	int m_cantJ;
public:
	EquipoBasquet(string nom,int cantJ) : Equipo(nom){// si o si el constructor de EquipoBasquet debe recibir los mismos datos 
		m_cantJ = cantJ;					          //   que el constructor de Equipo.(más los que se quieran agregar)
	}
};

int main() {
	EquipoBasquet A(), B("Spurs",15);
	return 0;
}



/* ***********************************************************************************************************/
///POLIMORFISMO Y MÉTODO VIRTUAL.
#include <iostream>
using namespace std;

class Personaje {
public:
	virtual void Mover() = 0;//método que se dirige hacia los Mover de otras clases(se le puede dar una funcion acá si lo desea)
	//							->ej: virtual void Mover(){cout<<"no se que hacer"<<endl;}.(sería un método virtual no puro)
	
	virtual ~Personaje() {} //destructor virtual para aplicar a las demás clases.
};

class Fantasma : public Personaje {
public:
	void Mover() override { cout<< "Buhhhh" << endl; }//se coloca OVERRIDE si la clase base tiene métodos virtuales no puros.(no es obligatorio, evita crear basura)
};

class PacMan : public Personaje {
public:
	void Mover() { cout<< "waka-waka" <<endl; }
};

int main() {
	Personaje *v[2];//dos punteros personajes
	v[0] = new PacMan();//uno apunta a PacMan
	v[1] = new Fantasma();//y el otro aounta a Fantasma
	
	//Los punteros Personajes se mueven dependiendo su Clase apuntada
	v[0] -> Mover();
	v[1] -> Mover();
	
	delete v[0];//delete a un Personaje y un Pacman.
	delete v[1];//delete a un Personaje y un Fantasma.
	
	return 0;
}


/* ***********************************************************************************************************/
//Método para no perder la memoria del puntero luego de agrandar la misma.(Agregado/no pertenece al video)
#include <iostream>
using namespace std;

int main() {
	string *p;
	string nom = "Matias";
	p = &nom;
	cout<<*p<<endl;
	string *aux = p;
	p = new string [2];
	p[0] = aux[0];
	p[1] = "Lucas";
	cout<<p[0]<<" "<<p[1];
	return 0;
}


/* ***********************************************************************************************************/


















