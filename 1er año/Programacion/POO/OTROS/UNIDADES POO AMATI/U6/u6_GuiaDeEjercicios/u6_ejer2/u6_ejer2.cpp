#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Par{
	int ent;
	double dou;
};

void Mostrar() {
	ifstream archi2("grupo.dat",ios::binary);
	for(int i=0;i<10;++i) {
		Par p2;
		archi2.read(reinterpret_cast<char*>(&p2), sizeof(p2));
		cout<<p2.ent<<" "<<p2.dou<<endl;
	}
	archi2.close();
}

void Generar() {
	ofstream archi("grupo.dat",ios::binary);
	
	for(int i=0;i<10;++i) {
		Par p;
		p.ent = rand()%90+10;
		p.dou = (rand()%90+10)/100.0; 
		
		archi.write(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archi.close();
}

int main() {
	Generar();
	Mostrar();
	
	Par x;
	cout<<"Ingrese nuevo entero: ";cin>>x.ent;
	cout<<"Ingrese nuevo double: ";cin>>x.dou;
	int pos;
	cout<<"Ingrese posición para reemplazar: ";cin>>pos;
	
	ofstream arch("grupo.dat",ios::binary|ios::in);
	arch.seekp(pos*sizeof(Par));
	arch.write(reinterpret_cast<char*>(&x), sizeof(x));
	arch.close();
	cout<<"******nuevo arreglo******"<<endl<<endl;
	ifstream arch2("grupo.dat",ios::binary);
	for(int i=0; i<10; ++i) {
		arch2.read(reinterpret_cast<char*>(&x), sizeof(x));
		cout<<x.ent<<" "<<x.dou<<endl;
	}
	return 0;
}
