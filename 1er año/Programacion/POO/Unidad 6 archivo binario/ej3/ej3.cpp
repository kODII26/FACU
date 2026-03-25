#include <iostream>
#include <fstream>
using namespace std;

int main() {
	ofstream archi("creciente.poo",ios::binary);
	int cont=0;
	for (int i=0;i<10;++i){
		archi.write(reinterpret_cast<char*>(&cont),sizeof(cont));
		cont = cont +5;
	}
	archi.close();
	
	ifstream archi2("creciente.poo",ios::binary);
	for (int i=0;i<10;++i){
		int f;
		archi2.read(reinterpret_cast<char*>(&f),sizeof(f));
		cout<<f<<endl;
	}
	archi2.close();
	
	ifstream archi10("creciente.poo",ios::binary);
	int num;
	cout<<"Que numero desea ingresar a la lista"<<endl;
	cin>>num;
	int pos=0;
	int f;
	for (int i=0;i<10;++i){
		archi10.read(reinterpret_cast<char*>(&f),sizeof(f));
		if (f<num){
			pos++;
		}
	}
	cout<<"POSICION: "<<pos<<endl;
	archi10.close();

	ofstream arch("creciente.poo",ios::binary);
	cont=0;
	for (int i=0;i<pos;++i){
		arch.write(reinterpret_cast<char*>(&cont),sizeof(cont));
		cont = cont +5;
	}
	arch.write(reinterpret_cast<char*>(&num),sizeof(num));
	for (int i=11;i>pos;--i){
		arch.write(reinterpret_cast<char*>(&cont),sizeof(cont));
		cont = cont +5;
	}
	arch.close();
	
	ifstream archi4("creciente.poo",ios::binary);
	for (int i=0;i<11;++i){
		int c;
		archi4.read(reinterpret_cast<char*>(&c),sizeof(c));
		cout<<c<<endl;
	}
	return 0;
}

