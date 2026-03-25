#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;
struct Alumno {
	string nyp;
	int n1;
	int n2;
};
void getProm (const vector<Alumno> &v){
	ofstream archi3("promedios2.txt", ios::trunc);
	if (!archi3.is_open()) {
		cerr<<"no se pudo abrir"<<endl;
	} else {
		for (size_t i=0;i<v.size();++i){
			int prom=0;
			prom += (v[i].n1+v[i].n2)/2;
			archi3<<v[i].nyp;
			archi3<<setw(10)<<v[i].n1<<setw(3)<<v[i].n2;
			if (v[i].n1+v[i].n2>=60){
				archi3<<" Aprobado"<<endl;
			} else {
				archi3<<" Desaprobado"<<endl;
			}
		} // NO SE COMO DARLE FORMATO DE TABLA 
	}
}
void modifica (vector<Alumno> &v, string nyp, int a1, int a2){
	for (size_t i=0;i<v.size();++i){
		if (v[i].nyp==nyp) {
			v[i].n1=a1; 
			v[i].n2=a2;
		}
	}
}
int main() {
	vector<Alumno> v;
	ifstream archi("lista2.txt");
	if (!archi.is_open()) {
		cerr<<"no se pudo abrir"<<endl;
		return 1;
	} 
	Alumno x;
	while (getline(archi,x.nyp) and archi>>x.n1>>x.n2){
		cout<<x.nyp<<endl;
		cout<<x.n1<<" "<<x.n2<<" "<<endl;
		v.push_back(x);
		archi.ignore();
	}
	archi.close();
	cout<<"Nombre de alumno al cual va a cambiar las notas"<<endl;
	string nyp;
	getline(cin,nyp);
	cout<<"Notas nuevas"<<endl;
	//cin.ignore();
	int a1,a2;
	cin>>a1>>a2;
	modifica(v,nyp,a1,a2);
	ofstream archi2("lista2.txt",ios::trunc);
	for (size_t i=0;i<v.size();++i){
		archi2<<v[i].nyp<<endl;
		archi2<<v[i].n1<<" "<<v[i].n2<<endl;
	}
	getProm(v);
	return 0;
}

