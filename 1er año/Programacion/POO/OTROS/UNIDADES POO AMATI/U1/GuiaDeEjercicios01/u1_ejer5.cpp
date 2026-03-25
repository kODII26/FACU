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

int main() {
	int N = 5;
	int *v = new int[N];
	for(int i=0;i<N;++i) {
		v[i] = 1000+rand()%501;
		cout<<v[i]<<" ";
	}
	
	cout<<endl<<endl<<"El mayor es: "<<*BuscarMayor(v,N)<<endl;
	cout<<"Direccion en memoria: "<<BuscarMayor(v,N)<<endl;
	
	delete [] v;
	
	return 0;
}

