#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
int calcProm (double **v, int fila) {
	int suma=0;
	for (int c=0;c<6;c++){
		suma += *(*(v+fila)+c);
	}
	return suma/6;
}

int main() {
	double **v= new double*[10];	// 
	for (int i=0;i<10;i++){ 		// Guarda lugar para una matriz de 10 filas x 6 columnas
		*(v+i)= new double[6];		//
	}
	for (int f=0;f<10;f++){			//
		for (int c=0;c<6;c++){		//  Asigna valores random a la matriz dinamica
			*(*(v+f)+c)= rand()%10;	//
		}
	}
	for (int f=0;f<10;f++){			//
		for (int c=0;c<6;c++){		//   Muestra la matriz
			cout<<setw(5)<<*(*(v+f)+c);	//
		}
		cout<<endl;
	}
	int fila;
	cout<<"ingrese fila para calcular promedio"<<endl;
	cin>>fila;
	int promedio= calcProm(v,fila);
	cout<<" el promedio de la fila: "<<fila<<" es: "<<promedio<<endl;
	
	cout<<"La suma de cada columna es: "<<endl;
	for (int c=0;c<6;c++){
		double suma=0;
		for (int f=0;f<10;f++){
			suma += *(*(v+f)+c);
		}
		cout<<"La columna "<<c<<" suma: "<<suma<<endl;
	}
	
	
	for (int i=0;i<10;i++){		//
		delete [] v[i];			// Borra la matriz de a partes
	}							//
	delete []v;					//
	return 0;
}

