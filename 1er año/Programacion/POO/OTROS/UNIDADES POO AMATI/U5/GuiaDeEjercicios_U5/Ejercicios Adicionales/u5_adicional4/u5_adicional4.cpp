#include <iostream>
#include <fstream>
using namespace std;

string TipoDeCaracter( char c ) {

	if( (c>='a' and c<='z') or (c>='A' and c<='Z') ){
		return "letra";
	}else{
		if( c == ' ' ){
			return "espacio";
		}
	}
	return "signo";
}

class AnalizaTexto {
public:
	
	int ContarCaracteres( string nomArchivo ) {
		ifstream archi(nomArchivo);
		string palabra;
		int cont=0;
		while( archi>>palabra ){
			for(size_t i=0; i<palabra.size(); ++i) {
				++cont;
			}
		}
		return cont;
	}
	
	int ContarParrafos( string nomArchivo ) {
		ifstream archi(nomArchivo);
		string renglon;
		int cont=0;
		while( getline(archi,renglon) ) {
			if(renglon == "") {
				++cont;
			}
		}
		return cont;
	}
	
	int ContarLetras(string nomArchivo) {
		ifstream archi(nomArchivo);
		char c;
		int cont=0;
		while( archi >> c ) {
			if( TipoDeCaracter(c) == "letra" ) {
				++cont;
			}
		}
		return cont;
	}
	
	int ContarEspacios(string nomArchivo) {
		ifstream archi(nomArchivo);
		string c;
		int cont=0;
		while( getline(archi,c) ) {
			
			for( size_t i=0; i<c.size(); ++i ){
				if( TipoDeCaracter(c[i]) == "espacio" ) {
					++cont;
				}
			}
			
		}
		return cont;
	}
	
	int ContarSignos(string nomArchivo) {
		ifstream archi(nomArchivo);
		char c;
		int cont=0;
		while( archi >> c ) {
			if( TipoDeCaracter(c) == "signo" ) {
				++cont;
			}
		}
		return cont;
	}
	
	
};

int main() {
	AnalizaTexto a;
	string nomArchivo = "Parrafos.txt";
	
	cout<<"caracteres: "<<a.ContarCaracteres(nomArchivo)<<endl;//sin contar los espacios entre palabras.
	cout<<"párrafos: "<<a.ContarParrafos(nomArchivo)<<endl;//cuenta espacios vacios de textos(ojo con los enters de más).
	cout<<"letras: "<<a.ContarLetras(nomArchivo)<<endl;
	cout<<"espacios: "<<a.ContarEspacios(nomArchivo)<<endl;
	cout<<"signos: "<<a.ContarSignos(nomArchivo)<<endl;
	return 0;
}

