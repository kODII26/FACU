#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
vector<int> cargar_notas(int cant,int max) {     // Para llenar con valores random un vector de una funcion
	vector<int> v(cant);						// 	tenes que mandar el valor maximo que vas a poner en el random tambien
	for(int i=0; i<cant; i++) {					//	sino no funciona
		v[i] = rand()%(max+1);	
	}		
	return v;
}

int porcentaje(vector<int> notas) {
	int cantaprob=0;
	for (int x:notas) {
		if (x>=60) 
			cantaprob = cantaprob + 1;
	}
	return cantaprob;
}

int prom(vector<int> notas){
	int suma=0;
	for (int x:notas) {
		suma = suma+x;
	}
	return suma;
}
	int mejor(vector<int> notas) { 
		int mej=0;
		for (int x:notas) {
			if (x>mej)
				mej = x;
		}
		return mej;
	}
	
int main(int argc, char *argv[]) {
	int promedio;
	vector<int> notas = cargar_notas(60,100);
	
	prom(notas);
	promedio = prom(notas) / 60;
	cout<<"La calificacion media fue: "<<promedio<<endl;
	mejor(notas);
	cout<<"La mejor nota fue: "<<mejor(notas)<<endl;
	porcentaje(notas);
	cout<<"La cantidad de alumnos aprobados son: "<<porcentaje(notas)<<" de 60";
		
	return 0;
}
	
	
