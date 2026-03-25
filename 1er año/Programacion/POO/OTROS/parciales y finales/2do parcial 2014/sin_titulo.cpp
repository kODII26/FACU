#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;
struct Persona {
	int dni,altura;
	string apellido;

};
template<typename T> 
void escribir (vector<T> v, int n){
	ofstream archi("arreglo.dat",ios::binary|ios::trunc);
	for (int i=0;i<n;++i){
		//string s="DaSilva";
		char aux[15];
		strcpy(aux,v[i].apellido.c_str());
		archi.write(reinterpret_cast<char*> (&v[i]),sizeof(v[i]));
		
	}
}
int main() {
	cout<<"cant"<<endl;
	int n;cin>>n;
	vector<Persona> p(n);
	for (int i=0;i<n;++i){
		Persona x;
		cin>>x.dni>>x.altura>>x.apellido;
	}
	escribir(p,n);
	return 0;
}

