#include <iostream>
using namespace std;

template<typename T>
T Clamp(T &val,T max,T min){
	if( val > max ) {
		val = max;
	}
	if( val < min ) {
		val = min;
	}
	
	return val;
}

int main() {
	int min,max,val;
	cout<<"Ingrese valor mínimo: ";cin>>min;
	cout<<"Ingrese valor máximo: ";cin>>max;
	cout<<"Ingrese valor a depositar: ";cin>>val;
	cout<<endl<<"****Resultado del valor -> "<< Clamp(val,max,min) <<endl;
	return 0;
}

