#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
struct Elemento {
	string campo,valor;
};
	
class ConfigFile {
	string m_n;
	vector<Elemento> m_v;
public:
	ConfigFile(string nombre) {
		m_n= nombre;
		ifstream archi(nombre);
		if (!archi.is_open()){
			cerr<<"no se pudo abrir"<<endl;
		}
		string x;
		Elemento a;
		while (getline(archi,x)){
			int pos =-1;
			pos= x.find("#");
			if (pos!=-1){
				continue;
			}
			int pos2= x.find("=");
			a.campo=x.substr(0,pos2);
			a.valor=x.substr(pos2+1);
			m_v.push_back(a);
		}
	}
	string verValor (int i) {return m_v[i].valor;}
	void modValor(int i, string s){
		m_v[i].valor= s;
	}
	void guardarArchivo () {
		ofstream archi2 ("archivoConfigurado.txt",ios::trunc);
		if (!archi2.is_open()){
			cerr<<"No se pudo abrir"<<endl;
		}
		for (size_t i=0;i<m_v.size();++i){
			archi2<<m_v[i].campo<<"="<<m_v[i].valor<<endl;
		}
	}
};
int main() {
	ConfigFile q("archivo.txt");
	cout<<q.verValor(2)<<endl;
	string ss;
	cout<<"ingrese string para cambiar el valor"<<endl;
	getline(cin,ss);
	q.modValor(2,ss);
	cout<<q.verValor(2)<<endl;
	q.guardarArchivo();
	return 0;
}

