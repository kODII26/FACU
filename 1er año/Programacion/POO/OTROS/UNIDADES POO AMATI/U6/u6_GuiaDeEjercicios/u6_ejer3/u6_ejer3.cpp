#include <iostream>
#include <fstream>
using namespace std;

int main() {
	//creamos lista
	ofstream archi("lista.dat",ios::binary);
	int num =0;
	for(int i=0;i<10;++i) {
		archi.write(reinterpret_cast<char*>(&num), sizeof(num));
		num+=5;
	}	
	archi.close();
	
	//solicitamos nuevo num y calculamos su posible posicion.
	int nuevo_num;
	cout<<"Ingrese nuevo numero para el arreglo: ";cin>>nuevo_num;
	//leemos y mostramos.
	ifstream archi2("lista.dat",ios::binary);
	int numero, pos=0;
	for(int i=0;i<10;++i) {
		archi2.read(reinterpret_cast<char*>(&numero), sizeof(numero));
		if( numero < nuevo_num ) {
			++pos;
		}
		cout<<numero<<endl;
	}
	archi2.close();
	
	
	cout<<"***********************************************"<<endl;
	
	//reescribimos el arreglo con el numero nuevo.
	ofstream arch("lista.dat",ios::binary|ios::out);
	num = 0;
	
	for(int i=0;i<pos;++i) {
		arch.write(reinterpret_cast<char*>(&num), sizeof(num));
		num += 5;
		
	}
	
	arch.write(reinterpret_cast<char*>(&nuevo_num), sizeof(nuevo_num));
	
	for(int i=11;i>pos;--i) {
		arch.write(reinterpret_cast<char*>(&num), sizeof(num));
		num += 5;
	}
	arch.close();
	
	//leemos y mostramos.
	ifstream arch2("lista.dat",ios::binary);
	int n;
	for(int i=0;i<11;++i) {
		arch2.read(reinterpret_cast<char*>(&n), sizeof(n));
		
		cout<<n<<endl;
	}
	arch2.close();
	
	return 0;
}

