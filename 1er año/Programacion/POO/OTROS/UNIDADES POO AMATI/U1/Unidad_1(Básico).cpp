/* UNIDAD {1}*/

///PUNTEROS:
#include <iostream>
using namespace std;
int main() {
	/*
	int x=42;
	int *p;
	
	p = &x;//direccion de puntero es igual a direccion de la variable x.
	cout<<*p;//mostrar contenido de la direccion p.
	*/
	
	int n;
	cin>>n;
	int *p = new int[n];//un puntero q apunta la primer direccion de un conjunto de ellas(p,p+1,p+2,...,p+n-1)
	int *f = new int;
	cout<<p; //direccion de la primera pos del nuevo arreglo.
	delete [] p;//con [] por ser un vector.
	cout<<f;//direccion de la única pos.
	delete f;
	
	
	return 0;
}


///ARREGLOS DINÁMICOS:
#include <iostream>//Una forma de generar N nums aleatorios:
using namespace std;

int main() {
	int N;
	cin>>N;
	int* p = new int[N];
	
	for(int i=0; i<N; ++i) {
		*(p+i) = rand()%501+1000;
	}
	
	for(int i=0; i<N; ++i) {
		cout<<*(p+i)<<endl;
	}
	
	
	delete [] p;
	return 0;
}



#include <iostream>//Ejemplo del prof(generar un arreglo con punteros)
using namespace std;

int *generar(int n) {//atencion a la forma de la funcion.
	int *v = new int[n];
	for(int i=0; i<n; ++i) {
		v[i] = rand()%501+1000;// v[i] y *(v+i) son lo mismo.
	}
	
	return v; //retorna la primera direccion del vector.
}

int main() {
	int n;cin>>n;
	int *p = generar(n);//primera direccion.
	for(int i=0; i<n; ++i) {
		cout<< p[i] <<endl;//muestra el contenido de las direcciones.
	}
	delete [] p;
	return 0;
}


#include <iostream>//Buscar elemento en un arreglo de punteros:
using namespace std;


int *buscar(int *v,int n,int x) {
	for(int i=0;i<n;++i) {
		if(v[i] == x) return v+i;
	}
	
	return nullptr;
}

int main() {
	int n;cin>>n;
	int *p = new int[n];
	for(int i=0;i<n; ++i) {
		*(p+i) = rand()%500+1000;
	}
	for(int i=0;i<n; ++i) {
		cout<<*(p+i)<<" ";
	}
	
	int x;
	cout<<"Ingrese valor a busccar: ";cin>>x;
	int *p2 = buscar(p,n,x);//(direccion 1° de p, tamanio del arreglo, x).
	
	if( p2==nullptr){
		cout<<"el valor no existe en este arreglo."<<endl;
	}else{
		cout<<"el valor "<<*p2<<" se encuentra en la pos "<<(p2-p)+1<<endl;//se restan direcciones dando lugar a numeros reales:
     //                                                                     (primer direccion de p - direccion de p2 en pos) = num Real.
	}
	
	return 0;
}

/* Si busca eliminar elemento,crear matriz u otros ejemplos, ver la Guia de ejercicios resuelta o en esta misma carpeta*/

