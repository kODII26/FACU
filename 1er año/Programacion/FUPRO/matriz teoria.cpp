#include <iostream>
#include <matrix>
#include <iomanip>
using namespace std;

int main() {
	int max=0;
	matrix<int>m(5,4);
	
	//genera matriz con valores aleatorios
	for (int f=0;f<5;f++){
		for (int c=0; c<4; c++) {
			m[f][c] = rand()%101;
		}
	}
	// muestra la matriz
	for (int f=0;f<5;f++){
		for (int c=0; c<4; c++) {
			cout<< setw(5) << m[f][c];
		}
		cout<<endl;
	}
	
	// obtiene el mayor numero en la matriz
	for (int f=0;f<5;f++){
		for (int c=0; c<4; c++) {
			if (m[f][c]>max) {
				max = m[f][c];
			}
		}
	}
	cout<<"el valor maximo es :"<<max;
	
	return 0;
}

