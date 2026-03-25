#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;


double Promedio(int **v, int a, int c) {
	double prom=0;
	
	for(int j=0; j<c; ++j) {
		prom += v[a][j];
	}
	return prom/c;
}

vector<int> SumaColumnas(int **v, int f, int c) {
	vector<int> s(c,0);
	for(int j=0; j<c; ++j) {
		for(int i=0; i<f; ++i) {
			s[j] += v[i][j];
		}
	}
	
	return s;
}

int main() {
	int f,c;
	cout<<"Ingrese numero de filas: ";cin>>f;
	cout<<"Ingrese numero de columnas: ";cin>>c;
	
	//RESERVAR MEMORIA
	int **v = new int*[f];
	for(int i=0; i<f; ++i) {
		*(v+i) = new int [c];//recuerde que v[i] y *(v+i) son lo mismo.
	}
	
	//DAR VALORES.
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			v[i][j] = rand()%90+10;//*(v[i]+j) = v[i][j]
		}
	}
	
	//MOSTRAR
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			cout<<*(*(v+i)+j)<<" ";
		}
		cout<<endl;
	}
	
	cout<<"HOLA..."<<endl;
	int a;
	cout<<"se solicita indicar numero de fila a promediar: ";cin>>a;
	double p = Promedio(v,a,c);
	cout<<"El promedi de la fila "<<a<<" es: "<<p<<endl;
	cout<<"------------------------------"<<endl;
	cout<<"La suma de cada columna: "<<endl;
	
	vector<int> s = SumaColumnas(v,f,c);
	for(size_t i=0; i<s.size(); ++i) {
		cout<<s[i]<<" ";
	}
	
	//LIBERAR ESPACIO
	for(int i=0; i<f; ++i) {
		delete [] v[i];
	}
	
	delete [] v;
	
	return 0;
}





