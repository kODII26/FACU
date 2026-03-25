#include <iostream>
using namespace std;

int main() {
	int f,c;
	cout<<"Indique numero de filas: ";cin>>f;
	cout<<"Indique numero de columnas: ";cin>>c;
	
	//RESERVAR MEMORIA
	int **puntero_matriz = new int*[f];
	for(int i=0; i<f; ++i) {
		puntero_matriz[i] = new int[c];
	}
	
	
	//INGRESAR ELEMENTOS DE LA MATRIZ
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			cout<<"Indique el numero de ["<<i<<"]["<<j<<"]:";
			cin>>*(*(puntero_matriz+i)+j);  //preste atención a la lectura de elementos.
		}
	}
	
	//MOSTRAR MATRIZ
	cout<<"Imprimiendo matriz"<<endl<<endl;
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			cout<<*(*(puntero_matriz+i)+j)<<" ";
		}
		cout<<endl;
	}
	
	
	//LIBERAR ESPACIO
	for(int i=0; i<f; ++i) {
		delete [] puntero_matriz[i];
	}
	
	delete [] puntero_matriz;
	
	return 0;
}


///MATRIZ ALEATORIA:
#include <iostream>
#include <cstdlib>
using namespace std;
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
			v[i][j] = rand()%90+10;    //sabiendo que *(*(v+i)+j) se puede expresar así: *(v[i]+j), entonces tmb así: v[i][j] <--//
		    //                           forma original: *(*(v+i)+j) = rand()%90+10;
		}
	}
	
	//MOSTRAR
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			cout<<*(*(v+i)+j)<<" ";
		}
		cout<<endl;
	}
	
	//LIBERAR ESPACIO
	for(int i=0; i<f; ++i) {
		delete [] v[i];
	}
	
	delete [] v;
	
	return 0;
}




