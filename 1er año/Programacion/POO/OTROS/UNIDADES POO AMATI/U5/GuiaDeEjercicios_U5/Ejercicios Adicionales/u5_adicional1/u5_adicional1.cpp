#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

bool no_es_letra(char c) {
	if((c>='a' and c<='z') or (c>='A' and c<='Z')) {
		return false;
	}else{
		return true;
	}
	
}

int main() {
	
	ifstream archi("DonQuijote.txt");
	if( !archi.is_open() ) {
		cout<<"No se pudo abrir el archivo."<<endl;
		return 1;
	}
	
	int cont=0;
	string x;
	string cadena;
	while( archi>>x ){
		cadena += x+" ";
	}
	
	string palabra = "molinos de vientos";
	
	size_t pos = cadena.find(palabra);
	
	while( pos != string::npos ) {
		
		if ( no_es_letra(cadena[pos+palabra.size()]) and no_es_letra(cadena[pos-1]) ) {
		++cont;
		}
		pos = cadena.find(palabra,pos+2);
	}
	
	cout<<cont;
	return 0;
}

