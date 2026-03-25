#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class  Tanque {
	float m_p;
public:
	Tanque (float p) : m_p(p) {}
	//void AsignarPeso (float p) {m_p=p;}
	virtual float CalcularVolumen () =0;
	float VerPeso () {return m_p;}
	virtual ~Tanque() {} 
};
class Cilindro : public Tanque {
	float m_r, m_h;
public:
	Cilindro (float p, float r, float h) : Tanque(p),m_r(r),m_h(h) {}
	float CalcularVolumen ()override{
		float areabase = 3.14*m_r*m_r;
		float m_v = areabase*m_h;
		return m_v;
	}
};
class Esfera : public Tanque{
	float m_r;
public:
	Esfera (float p, float r) :Tanque(p),m_r(r){}
	float CalcularVolumen ()override{
		float m_v= 4/3.0*3.14*m_r*m_r*m_r;
		return m_v;
	}
};
int main() {
	Tanque *p= new Cilindro(500,5,10);
	cout<<p->CalcularVolumen()<<endl;
	delete p;
	p= new Esfera(1,15);
	cout<<p->CalcularVolumen()<<endl;
	return 0;
}

