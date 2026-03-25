#include <iostream>
using namespace std;

int *BuscarMayor(int *v,int N) {
	int mayor_pos=0;
	for(int i=1;i<N;++i) {
		if(v[mayor_pos]<v[i]) {
			mayor_pos = i;
		}
	}
	return &v[mayor_pos];
}

int *Insertar(int *v,int N,int P,int M) {
	int *v2 = new int[N];
	v2 = v;
	for(int i=N-1;i>=P;--i) {
		v2[i] = v2[i-1];
	}
	v2[P] = M;
	
	return v2;
}

int main() {
	int N = 5;
	int *v = new int[N];
	for(int i=0;i<N;++i) {
		v[i] = 1000+rand()%501;
		cout<<v[i]<<" ";
	}
	
	cout<<endl<<"El mayor es: "<<*BuscarMayor(v,N)<<endl;
	cout<<endl<<"Direccion en memoria: "<<BuscarMayor(v,N)<<endl;
	
	int M,P;
	cout<<endl<<"Ingrese numero a insertar: ";cin>>M;
	cout<<"Y en que pos: ";cin>>P;
	
	N++;
	v = Insertar(v,N,P,M);
	
	cout<<endl<<"Nuevo Arreglo: "<<endl;
	for(int i=0;i<N;++i) {
		cout<<v[i]<<" ";
	}
	
	delete [] v;
	
	return 0;
}





