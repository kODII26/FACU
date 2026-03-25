/// SOBRECARGA DE OPERADORES

///Primer ejemplo video
//Se pueden declarar como metodo de clase o como funcion libre
class Complejo {
public:
	Complejo operator+ (Complejo c2){  // miembro de clase 
		Complejo suma= (c1.preal + c2.vpreal, c1.pimag + c2.pimag);
		return suma;
	}
};
Complejo operator+ (Complejo c1, Complejo c2); // funcion global
	Complejo suma= (c1.verParteReal() + c2.verParteReal(), c1.verParteImag() + c2.verParteImag());
	return suma;

int main() {
	Complejo c1(1,3), c2(4,5), suma;
	suma = c1+c2;
	return 0;
}

///Sobrecarga y puntero this->
// Los operadores que modifican al primer operando suelen retornar
// al mismo objeto (por referencia) para permitir la aplicacion en cadena
class Complejo {
	... // El = se puede aplicar en cadena (ej a=5=b) por lo tanto si lo sobrecargas tenes 
		//que hacerlo con las mismas reglas
	Complejo& operator=(const Complejo &b) { //Devuelve A con referencia pq modifica al operando
		this->m_preal= b.m_preal;			// El complejo B va con const pq no se modifica
		this->m_pimag= b.m_pimag;			// a=b modifica a A no a B	
		return *this; //A se modifica y se devuelve a si mismo con el *this
	}	
	
	Complejo a,b,c,d(1,1);
	a = b = c = d; // Es equivalente a:
					//a.operator=(b.operator=(c.operator=(d)));		
};	
/// Operador de asignación para vectores con memoria dinamica
Cuando la clase utiliza memoria dinamica el operador de asignacion debe sobrecargarse
class VectorDbl{
	double *m_p; // vector dinamico
	int m_n; // tamaño del vector a
public:
	VectorDbl () {...}
	VectorDbl(VectorDbl &v2) {...} //Constructor de copia porque tiene puntero
	VectorDbl& operator= (VectorDbl &v2){ //Operador de copia
		delete[] this->m_p; //  <---Esta es la diferencia con el constructor de copia
		m_p = new double[v2.m_n];
		for (int i=0;i<v2.m_n;++i)
			this->m_p[i] = v2.m_p[i];
		this->m_n = v2.m_n;
		return *this;
	}
};
/// Función global vs método de clase 
Funcion miembro: (método)
	Recomendado: operadores asimetricos (Cuando haces sobrecarga de operadores y hay un operando
	que es mas importante que el otro)
	Obligatorios: = () [] -> ->*
Función global:
	Recomendado: operadores simétricos (suma, resta, multiplicacion)
	Obligatorio: clases ajenas o tipos fundamentales (clases ajenas como el cout y cin)
/* **********************************************************************************************/
	*cout / cin son instancias de las clases ostream / istream
	*Estas clases ya tienen sobrecargas para los tipos de datos fundamentales (int float string)
	
/// Sobrecarga de << y >> para entrada/salida
ostream &operator<<(ostream &o, const Complejo &c){ //El ostream se modifica el complejo 
													//no ya que solo lo vamos a mostrar
	o<< c.VerParteReal() <<"+";
	o<< c.VerParteImag() <<"i";
	return o; 
}
istream &operator>>(istream &i, Complejo &c){
	float a; i>> a; c.CargarParteReal(a);
	float b; i>> b; c.CargarParteReal(b);
	return i;
}

///Casos especiales: pre y post incremento
class Fraccion {
	int m_num, m_den;
public:
	... //Para sumarle 1 a una fraccion se le suma el denominador al numerador
	Fraccion &operator++() { // en el preinc le aumento 1 a la variable y luego la devuelvo
		m_num += m_den;
		return *this;
	}
	// Este ejemplo va con & porque retorna *this (cuando pones eso podes decidir si va con & o no)
	Fraccion operator++(int) { //en el postinc, me guardo la variable vieja, le incremento 1
		Fraccion aux= *this;   // y luego devuelvo la variable vieja
		m_num += m_den;
		return aux;
	}
	// Este no va con referencia ya que devuelve una variable creada en el mismo metodo
	// Nunca hay que devolver con referencia una variable local, porque cuando la funcion 
	// termine la variable va a desaparecer y le estas haciendo referencia a algo que no existe
};
/// Uso de const en operandos
	// Si queres buscar el mayor promedio de un alumno sin sobrecarga es asi:
class Alumno {
	string nombre;
	float promedio;
public:
	...
	float VerProm () const { //const ya que no modifica nada, solo queremos ver el promedio
		return promedio;
	}
};
...
int MejorAlumno (const vector<Alumno>&v){
	...
		if (v[i].VerProm()<v[m].VerProm())
			...
}
	//Y si lo haces con sobrecarga, lo podes escribir simplemente asi
struct Alumno {
	string nombre;
	float promedio;
	bool operator<(const Alumno &o) const { //Podes instriurlo a que busque por dni,
		return promedio < o.promedio;		// edad, alfabeticamente, etc
	}
};
...
int MejorAlumno (const vector<Alumno> &v){
	...
	if (v[i] < v[m]) ...
}
/// Operador []
	//Para mostrar o modificar un complejo de forma facil con sintaxis de vector
class Complejo {
	float m_preal, m_pimag;
public:
	float operator[] (int i) const { //para ver (retorna el valor por copia)
		if (i==0) return m_preal;
		else return m_pimag;
	}
	float& operator[] (int i) { //para modificar (retorna la variable por referencia)
		if (i==0) return m_preal;
		else return m_pimag;
	}
	// El compilador diferencia las dos sobrecargas por el const, si le pones const 
	//llama a la primera, sino a la segunda.
};
int main () {
	Complejo c;
	c[0] = 1; c[1]=5;
	cout<<c[0]<< "+" <<c[1]<<"i"<<endl;
}
	
	
	
	
	
	
	
	
	
	
	
