#include <iostream>
using namespace std;

int main() {
	a) float *v;
	   double *v;
	
	b) int (*v)[15] = new int[10][15]; // Puntero a un arreglo
	
	c) float **v= new float*v[10];  //Arreglo de punteros
		for (int i=0;i<10;i++){
			*(v+i) = new float[30];
		}


	return 0;
}

