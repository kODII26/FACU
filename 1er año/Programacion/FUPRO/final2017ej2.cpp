#include <iostream>
#include <vector>
using namespace std;
struct Evento {
	string tipo;
	int jugador;
};
void resumen_partido (const vector<Evento> &v, int num_jug){
	cout<<"Resumen del jugador "<<num_jug<<" : "<<endl;
	for (size_t i=0;i <v.size();++i){
		if (v[i].jugador==num_jug){
			cout<<"El jugador tuvo un "<<v[i].tipo<<endl;
		}
	}
}

int main() {
	vector<Evento> v;
	Evento x;
	cout<<"Cuando el partido termine ingrese -termino-"<<endl;
	cout<<"Accion"<<endl;
	getline(cin,x.tipo);
	while (x.tipo!="termino"){
		cout<<"Jugador num?"<<endl;
		cin>>x.jugador;
		v.push_back(x);
		cout<<"Accion"<<endl;
		cin.ignore();
		getline(cin,x.tipo);
	}
	resumen_partido(v,0);
	resumen_partido(v,1);
	return 0;
}

