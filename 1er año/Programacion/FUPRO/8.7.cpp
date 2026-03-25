#include <iostream>
#include <vector>
#include <stdlib.h>
#include <matrix>
#include <tuple>
using namespace std;
vector<string> GetNombres(int cant) {
	string nombre;
	vector<string> n(cant);
	for (int i=0; i<cant; i++) {
		cout<<"Ingrese los nombres"<<endl;
		cin>>nombre;
		n[i] = nombre;
	}
	return n;
}

void MostrarNombre(const vector<string>Nombres) {
	for (size_t i=0;i<Nombres.size(); ++i){ 
		cout<<Nombres[i]<<endl;
	}
}
matrix<int> GetNotas (int cant) {
	int nota;
	matrix<int>v (cant,4);
	for (size_t f=0; f<v.size(0);f++) {
		cout<<"Ingrese las notas"<<endl;
		for (size_t c=0; c<v.size(1);c++) {
			cin>>nota;
			v[f][c] = nota;
		}
	}
	return v;
}
void MostrarNotas(const matrix<int>notas) {
	for (size_t f=0;f<notas.size(0); ++f){ 
		for (size_t c=0;c<notas.size(1); ++c){ 
		cout<<notas[f][c]<<endl;
		}
	}
}
tuple<int,int> GetRegul (matrix<int>notas) {
	int CantRegular= 0;
	int CantProm= 0;
	for (size_t f=0;f<notas.size(0); ++f){
		if (notas[f][0] >= 80 or notas[f][1] >= 80) {
			if (notas[f][2] >=80 or notas[f][3] >= 80) {
				CantProm= CantProm + 1;
			} else {
				if (notas[f][2] >=50 or notas[f][3] >= 50) {
					CantRegular= CantRegular + 1;
				}
			}
		} else {
			if (notas[f][0] >= 50 or notas[f][1] >= 50) {
				if (notas[f][2] >=50 or notas[f][3] >= 50) {
					CantRegular= CantRegular + 1;
				}
			}
		}
		
	}
	return make_tuple(CantProm, CantRegular);
}
void MostrarTodo (const matrix<int>notas, vector<string>nombres, int cant) {
	for (int f=0; f<cant; f++) {
		cout<<nombres[f]<<" Se saco: "<<notas[f][0];
		for (int c=1; c<4; c++) {
			cout<<"-"<<notas[f][c];
		}
		cout<<endl;
	}
}

int main() {
	string nombre;
	int cant, CantProm, CantRegular;
	cout<<"Cuantos alumnos hay"<<endl;
	cin>>cant;
	vector<string> nombres = GetNombres(cant);
	//MostrarNombre(nombres);
	matrix<int> notas = GetNotas(cant);
	//MostrarNotas(notas);
	tie(CantProm,CantRegular) = GetRegul(notas);
	cout<<"Hay "<<CantProm<<" alumnos que promocionaron, y "<<CantRegular<<" alumnos que regularizaron."<<endl;
	MostrarTodo(notas,nombres,cant);
	return 0;
 }
	
	
