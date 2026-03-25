#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
//en el archivo hay 20 alumnos y los voy a dividir en comisiones de 5 alumnos max


int main() {
	vector<string> v;
	ifstream archi("inscriptos.txt");
	string x;
	int c=0;
	while (getline(archi,x)){
		c++;
		v.push_back(x);
	}
	int cant= v.size();
	int cantCom;
	if (cant%5==0){
		cantCom= cant/5;
	} else {
		cantCom= cant/5;
		cantCom++;
	}
	cout<<"Para los "<<cant<<" alumnos, se van a necesitar "<<cantCom<<" comisiones"<<endl;
	archi.close();
	int inicio=0, final=5;
	
	for (int i=1;i<cantCom+1;++i){
		string a="comision";
		string b= a+to_string(i);
		ofstream archi2(b,ios::trunc);
		for (int i=inicio;i<final;++i){
			archi2<<v[i]<<endl;
		}
		inicio += 5;
		final +=5;
		
	}
	return 0;
}

