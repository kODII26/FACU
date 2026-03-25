#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;
int* buscaPos(int *v, int cant, int busca) {
	int *z= nullptr;
	for (int i=0;i<cant;i++){
		if (busca==v[i]){
			z=v+i;
			break;
		}
	}
	return z;
}


int main() {
	int cant,busca;
	cout<<"cant" <<endl;
	cin>>cant;
	
	int *v = new int[cant];
	for (int i=0;i<cant;i++){
		v[i] = rand()%100;
	}
	for (int i=0;i<cant;i++){
		cout<<setw(4)<<v[i];
	}
	cout<<endl<<"valor a buscar"<<endl;
	cin>>busca;
	int *res= buscaPos(v, cant, busca);
	if (res==nullptr) {
		cout<<"no se encontro"<<endl;
		
	} else {
		cout<<res<<endl;
		cout<<" posicion: "<<res-v+1<<endl;
	}

	delete [] v;
	return 0;
}

