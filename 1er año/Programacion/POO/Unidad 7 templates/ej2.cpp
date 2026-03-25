#include <iostream>
using namespace std;
template<typename T>
void Clamp (T &num, T min, T max){
	if (num>max){
		num=max;
	} 
	if (num<min){
		num=min;
	}
}

int main() {
	cout<<"Ingrese un numero entre 0 y 20"<<endl;
	int opc;cin>>opc;
	Clamp(opc,0,20);
	cout<<"Se paso de los limites por lo tanto su numero ahora vale: "<<opc;
	
	return 0;
}

