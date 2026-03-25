/* **********************************************************************************************************/
///SUMA MEDIANTE FUNCION GLOBAL.
#include <iostream>
using namespace std;

class Complejo {
	float m_preal,m_pimag;
public:
	Complejo(float pr=0, float pi=0){
		m_preal = pr;
		m_pimag = pi;
	}
	
	float VerParteReal() { return m_preal; }
	float VerParteImag() { return m_pimag; }
};

Complejo sumar (Complejo c1, Complejo c2) {
	Complejo suma(
		c1.VerParteReal() + c2.VerParteReal() ,
		c1.VerParteImag() + c2.VerParteImag() 
	);
	return suma;	
}

int main() {
	Complejo c1(1,3), c2(4,5);
	
	Complejo suma = sumar(c1,c2);
	
	cout<<suma.VerParteReal()<<" + "<<suma.VerParteImag()<<"*i"<<endl;
	return 0;
}


/* **********************************************************************************************************/
///SUMA COMO MÉTODO DE LA CLASE.
#include <iostream>
using namespace std;

class Complejo {
	float m_preal,m_pimag;
public:
	Complejo(float pr, float pi){
		m_preal = pr;
		m_pimag = pi;
	}
	
	Complejo sumar (Complejo c2) const {
		Complejo suma(
			this->m_preal+c2.m_preal ,
			this->m_pimag+c2.m_pimag );
		return suma;
	}
	
	float VerParteReal() { return m_preal; }
	float VerParteImag() { return m_pimag; }
};

int main() {
	Complejo c1(1,3), c2(4,5);
	
	Complejo suma = c1.sumar(c2);
	
	cout<<suma.VerParteReal()<<" + "<<suma.VerParteImag()<<"*i"<<endl;
	return 0;
}


/* **********************************************************************************************************/
///SOBRECARGA DEL OPERADOR (+).
#include <iostream>
using namespace std;

class Complejo {
	float m_preal,m_pimag;
public:
	Complejo(float pr, float pi){
		m_preal = pr;
		m_pimag = pi;
	}
	
	Complejo operator+ (Complejo c2) const {
		Complejo suma(
			this->m_preal+c2.m_preal ,
			this->m_pimag+c2.m_pimag );
		return suma;
	}
	
	float VerParteReal() { return m_preal; }
	float VerParteImag() { return m_pimag; }
};

int main() {
	Complejo c1(1,3), c2(4,5);
	
	Complejo suma = c1+c2;
	
	cout<<suma.VerParteReal()<<" + "<<suma.VerParteImag()<<"*i"<<endl;
	return 0;
}



/* **********************************************************************************************************/
///COPIA CON OPERADOR (=).
#include <iostream>
using namespace std;

class Complejo {
	
	
	float m_preal,m_pimag;
public:
	Complejo(float pr,float pi) {
		m_preal = pr;
		m_pimag = pi;
	}
	
	Complejo operator= (const Complejo &c) {
		this->m_preal = c.m_preal;
		this->m_pimag = c.m_pimag;
		return *this;
	}
	
	float VerParteReal() { return m_preal; }
	float VerParteImag() { return m_pimag; }
};

int main() {
	Complejo a(0,0),b(0,0),c(0,0),d(1,1);
	
	a = b = c = d;
	
	cout<<a.VerParteReal()<<" + "<<a.VerParteImag()<<"*i"<<endl;
	return 0;
}



/* **********************************************************************************************************/
//MERIOA DINÁMICA SOBRECARGADA (=).
#include <iostream>
#include <cstdlib>
using namespace std;

class Cambiar {
	int *m_p;
	int m_n;
public:
	
	Cambiar& operator=(Cambiar &v2) {
		delete[] this->m_p;
		m_p = new int[v2.m_n];
		for(int i=0; i<v2.m_n;i++) {
			this->m_p[i] = v2.m_p[i];
		}
		this->m_n = v2.m_n;
		return *this;
	}
};

int main() {
	int n;
	int* p = new int[10];
	cout<<"Indique tamaño del vector: ";cin>>n;
	for(int i=0; i<n; ++i) {
		p[i] = rand()%89+10;
		cout<<" "<<p[i];
	}
	
	cout<<endl;
	
	int *nuevo = p;
	
	for(int i=0; i<n; ++i) {
		cout<<" "<<nuevo[i];
	}
	
	return 0;
}



/* **********************************************************************************************************/
///SOBRECARGA DE << Y >> PARA ENTRADA/SALIDA.
#include <iostream>
using namespace std;

class Complejo {
	
	
	float m_preal,m_pimag;
public:
	Complejo(float pr,float pi) {
		m_preal = pr;
		m_pimag = pi;
	}
	
	Complejo operator= (const Complejo &c) {
		this->m_preal = c.m_preal;
		this->m_pimag = c.m_pimag;
		return *this;
	}
	
	void CargarParteReal(float pr) { m_preal = pr; }
	void CargarParteImag(float pi) { m_pimag = pi; }
	
	float VerParteReal() { return m_preal; }
	float VerParteImag() { return m_pimag; }
};

ostream	&operator<<(ostream &o,Complejo &c) { //SOBRECARGA DEL COUT.
	o << c.VerParteReal() <<"+"<< c.VerParteImag() <<"i";// la "o" es el cambio de nombre del cout recibido
	return o;											//(puede ser cout si lo desea, lo mismo con el cin).
}

istream &operator>>(istream &i,Complejo &d) {//SOBRECARGA DEL CIN.
	float pr;cout<<"Indique parte real: ";i>>pr;
	float pi;cout<<"Indique parte imag.: ";i>>pi;
	d.CargarParteReal(pr);
	d.CargarParteImag(pi);
	return i;// se retorna el i por si se quiere realizar acciones en cadena.
}

int main() {
	Complejo a(0,0),b(0,0),c(0,0),d(0,0);
	
	cin>>d;
	a = b = c = d;
	
	cout<<a;
	
	return 0;
}



/* **********************************************************************************************************/
///SOBRECARGA DE PRE Y POS INCREMENTO.
#include <iostream>
using namespace std;

class Fraccion {
	int m_num,  m_den;
public:
	Fraccion(int num,int den) : m_num(num), m_den(den) {}
	
	Fraccion &operator++() {// PRE incremento.
		m_num += m_den;
		return *this;
	}
	
	Fraccion operator++(int) {// POS incremento.
		Fraccion aux = *this;
		m_num += m_den;
		return aux;
	}
	
	void VerFraccion() { cout<<"("<<m_num<<"/"<<m_den<<") = "<<m_num/m_den<<endl; }
};

int main() {
	int a,b;
	cout<<"valor de a = ";cin>>a;
	cout<<"valor de b = ";cin>>b;
	Fraccion f(a,b);
	f.VerFraccion();
	++f;
	f.VerFraccion();
	f++;
	f.VerFraccion();
	
	return 0;
}




/* **********************************************************************************************************/
SOBRECARGA DEL OPERADOR MAYOR Y MENOR( < > ).
#include <iostream>
#include <vector>
using namespace std;

struct Alumno {
string nombre;
float promedio;

bool operator<(const Alumno &a) const {
cout<<promedio<<" < "<<a.promedio<<" ? "<<endl;
return (promedio < a.promedio);
}
};

int main() {
vector<Alumno> a(3);
for(size_t i=0; i<a.size(); ++i) {
cout<<"Ingrese el nombre del alumno["<<i<<"]: ";cin>>a[i].nombre;
cout<<"Ingrese su promedio: ";cin>>a[i].promedio;
}

cout<<endl<<"tamnio del vector = "<<a.size()<<endl;
for(size_t i=0; i<a.size(); ++i) {
cout<<a[i].nombre<<": "<<a[i].promedio<<endl;
}
cout<<endl;

int m=0;
for(size_t i=1; i<a.size(); ++i) {
if( a[m] < a[i] ) {
m = i;
}
}

cout<<endl<<"El alumno con mejor prom es: "<<a[m].nombre<<"--> "<<a[m].promedio<<endl;
return 0;
}




/* **********************************************************************************************************/
///SOBRECARGA DEL OPERADOR [].
#include <iostream>
using namespace std;

class Complejo {
	float m_preal, m_pimag;
public:
	
	float operator[] ( int i ) const {// para ver.
		if( i==0 ) return m_preal;
		else	return m_pimag;
	}
	
	float& operator[] ( int i ) {// para modificar/ rompe el principio de ocultación.
		if( i==0 ) return m_preal;
		else	return m_pimag;
	}
};


int main() {
	Complejo c;
	c[0] = 1;
	c[1] = 5;
	cout<< c[0] << "+" << c[1] << "i"<<endl;
	
	c[0] = 4;
	c[1] = 99;
	cout<< c[0] << "+" << c[1] << "i"<<endl;
	return 0;
}



/* **********************************************************************************************************/
