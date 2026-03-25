#include <iostream>
#include <vector>
using namespace std;
struct Competidor {
	string nyp;
	int m1,s1;
	int m2,s2;
	int m3,s3;
	int mfinal, sfinal;
};
void getSegundos (int &segundos, int &minutos);
void getTfinal(vector<Competidor> &v, int cant){
	int minutos=0, segundos=0;
	for (int i=0;i<cant;++i){
		minutos = v[i].m1+v[i].m2+v[i].m3;
		segundos = v[i].s1+v[i].s2+v[i].s3;
		for (int i=0;i<3;++i){
			getSegundos (segundos,minutos);
		}
		v[i].mfinal=minutos; v[i].sfinal=segundos;
	}
}
void getSegundos (int &segundos, int &minutos){
	if (segundos>60){
		minutos++;
		segundos =segundos - 60;
	}
}
Competidor getGanador (const vector<Competidor> &v, int cant){
	Competidor winner = v[0];
	for (int i=1;i<cant;++i){
		if (v[i].mfinal < winner.mfinal){
			winner = v[i];
		}
		if (v[i].mfinal == winner.mfinal){
			if (v[i].sfinal < winner.sfinal){
				winner = v[i];
			}
		}
	}
	return winner;
}
int main() {
	cout<<"Cuantos competidores corrieron esta carrera"<<endl;
	int cant;
	cin>>cant;
	vector<Competidor> v;
	for (int i=0;i<cant;++i){
		Competidor x;
		cout<<"ingrese nyp"<<endl;
		cin>>x.nyp;
		cout<<"ingrese minutos y segundos de la 1er etapa"<<endl;
		cin>>x.m1>>x.s1;
		cout<<"ingrese minutos y segundos de la 2da etapa"<<endl;
		cin>>x.m2>>x.s2;
		cout<<"ingrese minutos y segundos de la 3ra etapa"<<endl;
		cin>>x.m3>>x.s3;
		v.push_back(x);
	}
	getTfinal(v,cant);
	Competidor x= getGanador(v,cant);
	cout<<"El ganador del torneo es: "<<x.nyp<<" e hizo un tiempo final de "<<x.mfinal<<" minutos y "<<x.sfinal<<" segundos"<<endl;

	return 0;
}

