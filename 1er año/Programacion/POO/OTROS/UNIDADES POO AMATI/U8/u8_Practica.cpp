#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

struct Medalla {
	int oro,plata,bronce;
};

void actualizar_medallas( string nom_arch ) {
	ifstream arch(nom_arch,ios::binary|ios::in);
	map<string,Medalla> v;
	int o,p,b;
	string nomP;
	while( arch>>o>>p>>b>>nomP ) {
		v[nomP].oro = o;
		v[nomP].plata = p;
		v[nomP].bronce = b;
	}
	arch.close();
	
	string nom1,nom2,nom3;
	cout<<"Ingrese el nombre del Pais que salio primero: ";cin>>nom1;
	cout<<"Ingrese el nombre del Pais que salio segundo: ";cin>>nom2;
	cout<<"Ingrese el nombre del Pais que salio tercero: ";cin>>nom3;
	
	v[nom1].oro++;
	v[nom2].plata++;
	v[nom3].bronce++;

	ofstream archi(nom_arch,ios::binary|ios::trunc);
	
	for( auto p=v.begin(); p!=v.end(); ++p ) {
		archi<< p->second.oro <<" "<< p->second.plata <<" "<< p->second.bronce <<" "<< p->first <<endl;
	}
	archi.close();
}

int main() {
	actualizar_medallas("ArchivoPrueba.poo");
	return 0;
}
