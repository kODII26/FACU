#include <iostream>
#include <vector>
#include <tuple>
using namespace std;
class Transporte {
protected:
	float m_distanc, m_cost, m_durac;
public:
	Transporte (float  distanc) : m_distanc(distanc){}
	virtual float  getCost () =0;
	virtual float  getDurac () =0;
	virtual~ Transporte() {}
};
class TransporteBarco :public Transporte{
	
public:
	TransporteBarco (int distanc) : Transporte(distanc){}
	float  getDist () {return m_distanc;}
	float  getCost ()override {
		m_cost= 20+m_distanc*10.0;
		return m_cost;
	}
	float getDurac ()override {
		m_durac=4+m_distanc/30.0;
		return m_durac;
	}
};
class TransporteTren :public Transporte{
	
public:
	TransporteTren (int distanc) : Transporte(distanc){}
	float getDist () {return m_distanc;}
	float getCost ()override {
		m_cost= m_distanc*6.0;
		return m_cost;
	}
	float getDurac ()override {
		m_durac=1+m_distanc/120.0;
		return m_durac;
	}
};
class TransporteColectivo :public Transporte{
	
public:
	TransporteColectivo (int distanc) : Transporte(distanc){}
	float getDist () {return m_distanc;}
	float getCost ()override {
		m_cost= 2+m_distanc*3.0;
		return m_cost;
	}
	float getDurac ()override {
		m_durac=m_distanc/80.0;
		return m_durac;
	}
};
tuple<int,int> viaje (const vector<Transporte*> &v){
	float cost, durac;
	cost= v[0]->getCost()+v[1]->getCost()+v[2]->getCost();
	durac= v[0]->getDurac()+v[1]->getDurac()+v[2]->getDurac();
	return make_tuple(cost,durac);
}
int main() {
	vector<Transporte*> v(3);
	v[0]= new TransporteTren(100);
	v[1]= new TransporteColectivo(5);
	v[2]= new TransporteBarco(10);
	float cost, durac;
	tie(cost,durac) = viaje(v);
	cout<<"Costo total del viaje:" << cost<<endl;
	cout<<"Duracion total del viaje: "<<durac<<endl;
	
	for (int i=0;i<3;++i){
		delete v[i];
	}
	return 0;
}

