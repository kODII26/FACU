#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

int main() {
	ifstream archi("inscriptos.txt");
	if( !archi.is_open() ) {
		cout<<"No se pudo abrir el archivo."<<endl;
		return 1;
	}
	
	vector<string> v;
	string x;
	while( archi>>x ){
		v.push_back(x);
	}
	
	//el ejercicio dice que hay que hacer comisiones de 30 alumnos, pero las hago de 10.
	int numC=1;
	size_t i=0;
	while( i < v.size() ) {
		ostringstream oss;
		oss<<numC;
		string numComision = oss.str();
		ofstream archi2("comision("+numComision+").txt",ios::trunc);
		
		int cont=0;
		while( cont<10 and i<v.size() ){
			archi2<< v[i] <<endl;
			cont++;
			++i;
		}
		
		++numC;
	}

	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}






