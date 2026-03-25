#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
using namespace std;

struct Archivo {
	string campo, valor;
};

class ConfigFile {
	string nomA;
	vector<Archivo> a;
public:
	ConfigFile(string nombreArch,const vector<string> &v) {
		Archivo z;
		nomA = nombreArch;
		
		for( size_t i=0; i<v.size(); ++i ) {
			int pos = v[i].find("=");
			
			z.campo = v[i].substr(0,pos);
			z.valor = v[i].substr(pos+1);
			
			a.push_back(z);
		}
		
	}
	
	string VerCampo(int i) { return a[i].campo; }
	string VerValor(int i) { return a[i].valor; }
	
	void ModificarValor(int i) { 
		string nuevoV;
		cin.ignore();
		cout<<"Ingrese nuevo valor para el campo: ";getline(cin,nuevoV);
		a[i].valor = nuevoV;
		
	}
	
	void ModificarArchivo() {
		ofstream archi2("NuevoArchivoDeConf.txt",ios::trunc);
		for( size_t i=0; i<a.size(); ++i ) {
			archi2<< a[i].campo <<" -> "<< a[i].valor <<endl;
		}
	}
	
};

int main() {
	
	ifstream archi("archiDeConfiguracion.txt");
	if( !archi.is_open() ){
		cout<<"No se pudo abrir el archivo."<<endl;
		return 1;
	}
	vector<string> v;
	string x;
	
	while( getline(archi,x) ) {
		v.push_back(x);
	}
	

	
	size_t i=0;
	while( i<= v.size() ) {
		if( v[i].find("#") != string::npos ) {
			for( size_t j=i; j<v.size(); ++j) {
				v[j] = v[j+1];
			}
			v.resize(v.size()-1);
			i = -1;
		}
		++i;
	}
	
	for( size_t i=0; i<v.size(); ++i) {
		cout<<v[i]<<endl;
	}
	
	ConfigFile c("archiDeConfiguracion.txt",v);
	
	int op;
	cout<<"***desea modificar un valor del arreglo?***(si-1,no-0): ";cin>>op;
	if( op==1 ){
		int pos;
		cout<<"Ingrese pos del arreglo: ";cin>>pos;
		c.ModificarValor(pos);
	}
	
	c.ModificarArchivo();

	return 0;
}

