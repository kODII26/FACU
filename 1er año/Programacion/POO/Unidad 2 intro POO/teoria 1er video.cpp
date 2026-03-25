/* **********************************************************************************************/
///PRIMER EJEMPLO DE CLASS(incompleto).
#include <iostream>
using namespace std;

class Vector {
	int *m_p;//puntero para trabajar con arreglo.
	int m_n;//variable que se utilizará para su tamanio.
public:
	void DefinirTamanio(int n) {//funcion principal donde se les da valores a las variables privadas
		m_p = new int[n];
		m_n = n;
	}
	void Cargar(int i, int x) {
		m_p[i] = x;//puntero[posicion] = valor enviado por el usuario.
	}
	int Ver(int i) {
		return m_p[i];//devuelve el contenido del puntero en una determinada posicion.
	}
	int VerTamanio() {
		return m_n;
	}
	
	void LiberarMemoria() {
		delete [] m_p;
	}
	
};

int main() {
	Vector v;
	int n; cin>>n;
	v.DefinirTamanio(n);
	
	for(int i=0; i<v.VerTamanio(); ++i) {
		int x;
		cin>>x;
		v.Cargar(i,x);
	}
	cout<<endl;
	for(int i=0; i<v.VerTamanio(); ++i) {
		cout<<v.Ver(i)<<" ";
	}
	
	v.LiberarMemoria();
	return 0;
}

/* **********************************************************************************************/
///SEGUNDO EJEMPLO DE CLASS(completo).
#include <iostream>
using namespace std;

class Vector {
	int *m_p;//puntero para trabajar con arreglo.
	int m_n;//variable que se utilizará para su tamanio.
public:
	
	//CONSTRUCTOR: donde se les da valores a las variables privadas.
	Vector(int n) {
		m_p = new int[n];
		m_n = n;
	}
	
	//CONSTRUCTOR(vacío): por si se quiere utilizar un vector sin basura y luego indicar sus cualidades dentro de DefinirTamanio.
	Vector() {
		m_p = nullptr;
		m_n = 0;
	}
	
	void DefinirTamanio(int n) {
		if( m_p != nullptr ){/* error */ }//si al puntero ya se le asignó un espacio, no podrá inicializarse por segunda vez.
		m_p = new int[n];
		m_n = n;
	}
	
	void Cargar(int i, int x) {
		m_p[i] = x;//puntero[posicion] = valor enviado por el usuario.
	}
	int Ver(int i) {
		return m_p[i];//devuelve el contenido del puntero en una determinada posicion.
	}
	int VerTamanio() {
		return m_n;
	}
	
	
	//DESTRUCTOR: libera memoria una vez finaliza el programa.
	~Vector() {
		delete [] m_p;
	}
	
};

int main() {
	int n; cin>>n;
	Vector v(n);//dar valor al constructor de copia.
	v.DefinirTamanio(n);
	
	for(int i=0; i<v.VerTamanio(); ++i) {
		int x;
		cin>>x;
		v.Cargar(i,x);
	}
	cout<<endl;
	for(int i=0; i<v.VerTamanio(); ++i) {
		cout<<v.Ver(i)<<" ";
	}
	
	return 0;
}




/* **************************************************************************************************/
///CONSTRUCTORES "MOVE" Y DE COPIA
#include <iostream>
using namespace std;

class Vector {
	int *m_p;
	int m_n;
public:
	Vector(int n) {
		m_p = new int[n];
		m_n = n;
	}
	
	//CONSTRUCTOR DE COPIA 
	Vector(const Vector &v2) {//tomamos al vector original como v2
		m_n = v2.m_n;//m_n  =  tamanio de v2.
		m_p = new int[m_n];//le asignamos un nuevo espacio.
		
		
		//copiar los valores del vector viejo al nuevo:
		for(int i=0; i<m_n; ++i) {
			m_p[i] = v2.m_p[i]+100;
		}
	}
	
	//CONSTRUCTOR DE "MOVE"->Nota: Solo el compilador elije cuando usarlo.(cuando le conviene).<-( !¡ ) 
	Vector(Vector &&v2) {
		m_n = v2.m_n;
		m_p = v2.m_p+10;//  roba el puntero
		v2.m_p = nullptr;// para luego desecharlo y así evitar doble delete(un error).
	}
	
	void Cargar(int i, int x) {
		m_p[i] = x;
	}
	int Ver(int i) {
		return m_p[i];
	}
	
	~Vector() {
		delete [] m_p;
	}
};

int main() {
	int n;
	cout<<"Indique tamaño del vector: "; cin>>n;
	Vector v(n);
	for(int i=0; i<n; ++i) {
		int x;
		cin>>x;
		v.Cargar(i,x);
	}
	cout<<endl;
	
	
	
	cout<<"primer vector: ";
	for(int i=0; i<n; ++i) {
		cout<<v.Ver(i)<<" ";
	}
	cout<<endl;
	
	
	Vector w(v);//nueva variable de tipo Vector para trabajar con la copia.
	cout<<"vector de copia: ";
	for(int i=0; i<n; ++i) {
		cout<<w.Ver(i)<<" ";//se le sumó 100 para diferenciarlos mejor.
	}
	cout<<endl;
	cout<<"vector de copia: ";
	Vector v2 = v;// copiado diferente.
	for(int i=0; i<n; ++i) {
		cout<<v2.Ver(i)<<" ";
	}
	
	return 0;
}
