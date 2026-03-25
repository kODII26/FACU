#include <iostream>
using namespace std;
class Cilindro {
	float m_r; 
	float m_h;
	float m_vol;
public: 
	Cilindro (float r, float h): m_r(r),m_h(h) {
	}
//	void AsignarDatos (float r, float h) {
//		m_r = r; m_h=h;                      // ya no hace falta esta funcion gracias al constructor
//	}
	float ObtenerVolumen(){
		m_vol= 3.14*m_r*m_r*m_h;
		return m_vol;
	}
	~Cilindro() {cout<<"se borro un cilindro";}
};
int main() {
	int r,h;
	cin>>r>>h;
	Cilindro c1(r,h),c2(5.3,10.2);
//	c1.AsignarDatos(r,h);            // ya no hace falta esta funcion gracias al constructor
//	c2.AsignarDatos(5.3,10.2);
	cout<<"volumen c1 "<<c1.ObtenerVolumen()<<endl;
	cout<<"volumen c2 "<<c2.ObtenerVolumen()<<endl;

	return 0;
}

