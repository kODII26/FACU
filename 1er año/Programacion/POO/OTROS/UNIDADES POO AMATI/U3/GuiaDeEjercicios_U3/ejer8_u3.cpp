#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class  Tanque {
protected:
	float m_v, m_p;
public:
	Tanque (float p) : m_p(p) {}
	//void AsignarPeso (float p) {m_p=p;}
	virtual void CalcularVolumen () =0;
	float VerVolumen () {return m_v;}
	float VerPeso () {return m_p;}
	virtual ~Tanque() {} 
};
class Cilindro : public Tanque {
	float m_r, m_h;
public:
	Cilindro (float p, float r, float h) : Tanque(p) {
		m_r=r, m_h=h;	
	}
	void CalcularVolumen ()override{
		float areabase = 3.14*m_r*m_r;
		m_v = areabase*m_h;
	}
};


class Esfera : public Tanque{
	float m_r;
public:
	Esfera (float p, float r) :Tanque(p)   {
		m_r=r;
	};
	void CalcularVolumen ()override{
		m_v= (4/3)*3.14*pow(m_r,3);
	}
};


int main() {
	vector<Tanque*> p;
	p.push_back(new Cilindro(500,2,3));
	p[0]->CalcularVolumen();
	cout<<"El volumen del tanque con forma de Cilindro es de :"<<p[0]->VerVolumen()<<endl;
	p.push_back(new Esfera(500,2));
	p[1]->CalcularVolumen();
	cout<<"El volumen del tanque con forma de Esfera es de :"<<p[1]->VerVolumen()<<endl;
	
	for( Tanque *x: p ) delete x;
	
	return 0;
}

