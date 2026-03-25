#include <iostream>
#include <fstream>
using namespace std;
struct Persona {
	int dni,altura;
	char apellido[15];
	
};
ostream &operator<< (ostream &o, Persona a){
	o<<a.apellido<<endl<<a.dni<<"-"<<a.altura<<endl;
	return o;
}
int main() {
	ifstream archi("arreglo.dat",ios::binary);
	Persona x;
	archi.read(reinterpret_cast<char*> (&x),sizeof(Persona));
	cout<<x;
	return 0;
}

