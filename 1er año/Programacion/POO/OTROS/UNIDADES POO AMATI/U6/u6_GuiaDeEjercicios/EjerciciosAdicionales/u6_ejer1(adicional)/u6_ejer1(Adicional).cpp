#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
using namespace std;

int Tamanio(string n) {
	int num;
	if( n.find("Mb") != string::npos ) {
		n.erase(n.find("Mb"));
		stringstream iss(n);
		iss >> num;
		num = num*1000000;
	}else{
		if( n.find("Kb") != string::npos ){
			n.erase(n.find("Kb"));
			stringstream iss(n);
			iss >> num;
			num = num*1000;
		}else{
			if( n.find("b") != string::npos ){
				n.erase(n.find("b"));
				stringstream iss(n);
				iss >> num;
			}else{
				cout<<"tamanio no válido."<<endl;
				return 0;
			}
		}
	}
	return num;
}

void CreateDummyFile(string nomArchi,string n) {

	int N = Tamanio(n);
	
	ofstream arch(nomArchi,ios::binary);
	
	for(int i=0; i<N ;++i){
		int val = rand()%10;
		arch.write(reinterpret_cast<char*>(&val),sizeof(val));
	}
	
	arch.close();
	
}

void LeerArchivo(string nomArchi,string n) {
	ifstream archi(nomArchi,ios::binary);
	int N = Tamanio(n);
	
	for(int i=0; i<N ;++i){
		int val;
		archi.read(reinterpret_cast<char*>(&val),sizeof(val));
		cout<<val<<" ";
	}
	archi.close();
}



int main() {
	string nomArchi = "Archivo.poo";
	string n;
	cout<<"Ingrese tamanio(Mb,Kb,b): ";cin>>n;
	
	CreateDummyFile(nomArchi,n);
	
	LeerArchivo(nomArchi,n);

	return 0;
}

