#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> v(15);
	for(size_t i=0; i<v.size(); ++i){
		v[i] = 10+rand()%90;
	}
	
	cout<<"Mostrar nmr1: "<<endl;
	for(size_t i=0; i<v.size(); ++i){
		cout<<v[i]<<" ";
	}
	
	cout<<endl<<"Mostrar nmr2: "<<endl;
	for(vector<int>::iterator it= v.begin(); it!=v.end(); ++it) {
		cout<<*it<<" ";
	}
	
	cout<<endl<<"Mostrar nmr3: "<<endl;
	for(int &x:v) { //for basado en rangos???
		cout<<x<<" ";
	}
	
	
	int mayor=0,menor=0,suma=0;
	for(int &x:v){
		if( mayor < x ){
			mayor = x;
		}
		if( menor > x ){
			menor = x;
		}
		suma += x;
	}
	
	float prom = suma/v.size();
	cout<<"MAYOR: "<<mayor<<"	MENOR: "<<menor<<"	PROMEDIO: "<<prom<<endl;
	
	int val;
	cout<<"INGRESE VALOR A BUSCAR: ";cin>>val;
	for(size_t i=0; i<v.size(); ++i) {
		if(val == v[i]) {
			cout<<"El valor "<<val<<" se encunetra en este arreglo."<<endl;
			cout<<"POS = "<< i;
		}
	}
	
	return 0;
}

