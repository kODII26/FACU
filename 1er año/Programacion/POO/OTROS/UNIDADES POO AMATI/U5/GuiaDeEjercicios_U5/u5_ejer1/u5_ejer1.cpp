#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int Estar(const vector<string> &v2, string palabra) {
	
	for(size_t i=0; i<v2.size(); ++i) {
		if ( v2[i] == palabra ){
			return 1;
		}
	}
	
	return 0;
}

int main() {
	ifstream archi("palabras.txt");
	if( !archi.is_open() ){
		cout<<"El archivo no se pudo abrir."<<endl;
		return 1;
	}
	
	vector<string> v;
	
	string x; 
	int cont =0;
	while( archi>>x ){
		cont++;
		v.push_back(x);
	}
	// de a - z
	
	vector<string> v2;
	int pos;
	while( v2.size() < v.size() ) {
		string primero = "zzzzzzzzzz";
		
		for(size_t i=0; i<v.size(); ++i) {
			if( v[i] < primero and Estar(v2,v[i])==0 ){
				primero = v[i];
				pos = i;
			}
		}
		v2.push_back(v[pos]);
	}
	
	for(size_t i=0; i<v2.size(); ++i) {
		cout<<v2[i]<<" ";
	}
	
	
	return 0;
}

