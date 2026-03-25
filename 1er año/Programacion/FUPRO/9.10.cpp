#include <iostream>
#include <matrix>
#include <cstdlib>
#include <iomanip>
using namespace std;
void mostrarMatriz( const matrix<int> &datos){
	for (size_t f=0;f<datos.size(0);f++){
		for (size_t c=0;c<datos.size(1);c++){
			cout<<setw(3)<<datos[f][c];
		}
		cout<<endl;
	}
}
	
int sumaFilas(const matrix<int> &datos, int f_pos){
	int total=0;
	for (size_t c=0;c<datos.size(1);c++) {
		total += datos[f_pos][c];
	}
	return total/11;
}

void rellenaMatriz (matrix<int> &datos){
	
	for (size_t f=0;f<datos.size(0);f++){
		for (size_t c=0;c<datos.size(1);c++){
			if (datos[f][c]==-1) {
				int promedio= sumaFilas(datos,f);
				datos[f][c]= promedio;
			}
		}
	}
}
	
void getTotales(matrix<int> &datos){
	datos.resize(5,13);
	for (size_t f=0;f<datos.size(0);f++){
		int suma=0;
		for (size_t c=0;c<datos.size(1)-1;c++){
			suma += datos[f][c];
		}
		datos[f][12]= suma;
	}
}
int main() {
	matrix<int> datos(5,12);
	for (size_t f=0;f<datos.size(0);f++){
		for (size_t c=0;c<datos.size(1);c++){
			datos [f][c]= rand()%10;
		}
	}
	mostrarMatriz(datos);
	datos[2][3]= -1;
	cout<<endl;
	mostrarMatriz(datos);
	cout<<endl;
	rellenaMatriz(datos);
	mostrarMatriz(datos);
	getTotales(datos);
	cout<<endl;
	mostrarMatriz(datos);
	
	
	
	
	return 0;
}

