#include <iostream>
using namespace std;

template<typename T>
void Intercambia(T &val,T &val2) {
	cout<<"val1: "<< val <<endl;
	cout<<"val2: "<< val2 <<endl;
	T aux = val;
	val = val2;
	val2 = aux;
	cout<<endl;
	cout<<"val1: "<< val <<endl;
	cout<<"val2: "<< val2 <<endl;
}

int main() {
	string saludo = "hola!";
	string saludo2 = "chau";
	int a = 10;
	int b = 100;
	Intercambia(a,b);

	return 0;
}

