#include <iostream>
using namespace std;

float coniva(float precio){
	float pconiva = precio+(precio*0.21);
	return pconiva;
}

int main(int argc, char *argv[]) {
	float precio, pconiva;
	cout<<"Ingrese el valor del producto"<<endl;
	cin>>precio;
	pconiva =coniva(precio);
	cout<<pconiva;
	
	return 0;
}

