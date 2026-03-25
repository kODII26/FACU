#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
int* buscaMay(int *v, int n){
	int may=0;
	int* z;
	for (int i=0;i<n;i++){
		if (*(v+i)>may){
			may = *(v+i);
			z= v+i;
		}
	}
	return z;
}
	
void insertar(int *v, int n, int val, int pos){
	for (int i=0;i<n;i++){
		if (i==pos){
			*(v+i)= val;
		}
	}
}
int main() {
	int n,pos,val;
	cin>>n;
	int *v = new int[n];
	for (int i=0;i<n;i++){
		*(v+i) = 1000+rand()%(1500-1000+1);
	}
	for (int i=0;i<n;i++){
		cout<<"  "<<*(v+i); 
	}
	int *p= buscaMay(v,n);
	cout<<endl<<"la direccion del mayor es: "<<p<<" y esta en la pos: "<<p-v+1<<endl;
	cout<<"ingrese el valor a añadir y la posicion"<<endl;
	cin>>val>>pos;
	pos--;
	insertar(v,n,val,pos);
	for (int i=0;i<n;i++){
		cout<<"  "<<*(v+i); 
	}
	
	
	delete []v;
	return 0;
}

