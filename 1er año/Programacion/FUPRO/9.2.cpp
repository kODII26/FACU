#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
vector<int> generar(int cant) {
	vector<int> v(cant);
	for (int i=0; i<cant; i++) {
		v[i] = 100+rand()%(150-100+1);
	}
	return v;
}
void mostrarVector (const vector<int> generar) {
	for (int x:generar) {
		cout<<x<<setw(4);
	}
}
void mostrarVectorArreglado (vector<int>generar, int m ,int p){
	generar.resize(generar.size()+1);
	//for (size_t i=p;i<20;i++) {
	//	generar[i]= generar[i+1];
	//}
	
	
	for(int i=generar.size()-1;i>=p;--i){
		generar[i]=generar[i-1];
	}
	generar[p] = m;
	for (int x:generar) {
		cout<<x<<setw(4);
	}
}
int main() {
	int m, p;
	int cant= 20;
	generar(cant);
	vector<int> v = generar(cant);
	mostrarVector(v);
	cout<<endl<<"Ingrese el valor que quiere insertar y su posicion"<<endl;
	cin>>m>>p;
	--p;
	mostrarVectorArreglado(v,m,p);
	return 0;
}

