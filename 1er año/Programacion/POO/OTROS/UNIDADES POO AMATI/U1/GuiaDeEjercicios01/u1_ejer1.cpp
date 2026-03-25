#include <iostream>
using namespace std;

int main() {
	int a = 10;
	
	int *b = new int;
	cout<<"Ingrese el valor de b: ";cin>>*b;
	
	cout<<"A) "<<&a<<endl;
	cout<<"B) "<<*b<<endl;
	
	delete b;

	return 0;
}

