#include <iostream>
using namespace std;

struct vector_int_dinamico {
	int n;
	int *p;
};

vector_int_dinamico redimensionar(vector_int_dinamico &v,int c) {
	vector_int_dinamico v2;
	v2.p = new int[v.n+c];

	for(int i=0; i<v.n; ++i) {
		v2.p[i] = v.p[i];
	}	
	
	v2.n = v.n+c;
	
	for(int i=v.n; i<v2.n; ++i) {
		v2.p[i] = 0;
	}
	
	delete [] v.p;
	return v2;
	
}

int main() {
	vector_int_dinamico v;
	cout<<"Ingrese tamaño del vector: ";cin>>v.n;
	v.p = new int[v.n];
	
	for(int i=0; i<v.n; ++i) {
		v.p[i] = rand()%90+10;
		cout<<v.p[i]<<" ";
	}
	
	int c;
	cout<<endl<<"Ingrese la cantidad de ceros a insertar: ";cin>>c;
	v = redimensionar(v,c);
	
	for(int i=0; i<v.n; ++i) {
		cout<<v.p[i]<<" ";
	}
	
	delete [] v.p;
	return 0;
}

