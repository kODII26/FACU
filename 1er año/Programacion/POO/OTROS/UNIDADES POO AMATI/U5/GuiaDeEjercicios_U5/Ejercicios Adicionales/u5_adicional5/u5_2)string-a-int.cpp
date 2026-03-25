#include <iostream>
#include <sstream>
using namespace std;

int main() {
	cout<<"Ingrese dos numeros separados por un espacio: ":;
	string str;
	getline(cin,str);
	
	stringstream ss(str);//ss es de entrada/salida.
	double n1,n2;
	ss>>n1>>n2;//ss>> es entrada de datos( se puede utilizar istringstream ).
	cerr<<(n1+n2);//cerr<< es lo mismo que cout<<.
	
	return 0;
}

