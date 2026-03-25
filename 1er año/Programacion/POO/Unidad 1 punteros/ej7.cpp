#include <iostream>
#include <cstdlib>
using namespace std;
int* redimensionar (int *v, int cant, int ceros){
	int *f= new int[cant];
	for (int i=0;i<cant-ceros;i++){
		*(f+i)= *(v+i);
	}
	for (int i=cant-ceros;i<cant;i++){
		*(f+i)= 0;
	}
	return f;
}

int main() {
	int n,ceros;
	cout<<"cant"<<endl;
	cin>>n;
	int *v= new int[n];
	for (int i=0;i<n;i++){
		*(v+i)= rand()%100;
	}
	for (int i=0;i<n;i++){
		cout<<" "<<*(v+i);
	}
	cout<<endl<<"cuantos ceros queres ingresar"<<endl;
	cin>>ceros;
	int cant= n+ceros;
	int *F= redimensionar (v,cant,ceros);
	for (int i=0;i<cant;i++){
		cout<<" "<<*(F+i);
	}
	return 0;
}

