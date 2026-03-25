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
	int fil,col;
	cin>>fil>>col;
	double **v= new double*[fil];	// 
	for (int i=0;i<fil;i++){ 		// Guarda lugar para una matriz de 10 filas x 6 columnas
		*(v+i)= new double[col];		//
	}
	for (int f=0;f<fil;f++){			//
		for (int c=0;c<col;c++){		//  Asigna valores random a la matriz dinamica
			*(*(v+f)+c)= rand()%10;	//
		}
	}
	for (int f=0;f<fil;f++){			//
		for (int c=0;c<col;c++){		//   Muestra la matriz
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
	for (int c=0;c<col;c++){
		double suma=0;
		for (int f=0;f<fil;f++){
			suma += *(*(v+f)+c);
		}
		cout<<"La columna "<<c<<" suma: "<<suma<<endl;
	}
	
	
	for (int i=0;i<fil;i++){		//
		delete [] v[i];			// Borra la matriz de a partes
	}							//
	delete []v;					//
	return 0;
}

