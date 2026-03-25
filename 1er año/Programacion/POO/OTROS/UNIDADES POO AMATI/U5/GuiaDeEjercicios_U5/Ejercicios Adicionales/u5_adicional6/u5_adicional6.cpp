#include <iostream>
#include <fstream>
using namespace std;

void Reemplazar(string nomArchivo,string p,string p_nueva) {
	ifstream archi(nomArchivo);
	
	string texto,x;
	while( getline(archi,x) ) {
		texto += x;
	}
	
	bool encontrado = false;
	
	size_t pos = 0;
	while( texto.find(p,pos) != string::npos ) {
		pos = texto.find(p,pos);
		
		texto.replace(pos,p.size(),p_nueva);
		
		encontrado = true;
	}
	
	if( encontrado ){
		ofstream archi2(nomArchivo,ios::trunc);
		
		archi2<<texto;
	} else {
		cout<<"No se encontró coincidencias."<<endl;
	}
}

int main() {
	
	Reemplazar("texto.txt","Moreno","ElMasPeronista");//no funciona si a Moreno se lo reemplaza por Moreno(...)

	return 0;
}

