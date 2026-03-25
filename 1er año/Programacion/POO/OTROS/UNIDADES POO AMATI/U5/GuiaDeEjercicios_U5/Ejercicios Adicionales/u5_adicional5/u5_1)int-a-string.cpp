#include <iostream>
#include <sstream>
using namespace std;

int main() {
	int n1 = 20;
	int n2 = 80;
	
	int n3 = n1+n2;
	
	stringstream ss;//stringstream sirve para entrada/salida de datos.
	ss<<n3;//en este caso es salida(<<), por lo que se podría utilizar un ostringstream.
	
	string t3 = ss.str();//convertir a string y pasarlo a una nueva variable de tipo string.
	
	cout<<"el numero "<<t3<<" tiene "<<t3.size()<<" caracteres."<<endl;
	
	return 0;
}

