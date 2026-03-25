#include <iostream>
using namespace std;

class Cilindro {
	float m_h, m_r, pi, m_volumen;
public:
	
	Cilindro(float h, float r) {
		m_h = h;
		m_r = r;
		pi = 3.14;
	}
	
	void AsignarDatos(float h, float r) {
		m_h = h;
		m_r = r;
		pi = 3.14;
	}
	float ObtenerVolumen() {
		m_volumen = pi*m_r*m_h;
		return m_volumen;
	}
};

int main() {
	
	float h,r;
	cout<<"ingrese radio de la base del cilindro: ";cin>>r;
	cout<<endl<<"ingrese altura del cilindro: ";cin>>h;
	
	Cilindro c1(h,r),c2(10.2,5.3);//c)el error se produce al no inicializar c1 y c2.
	c1.AsignarDatos(h,r);
	c2.AsignarDatos(10.2,5.3);
	
	cout<<endl<<endl;
	cout<<"El Volumen del cilindro[1] es = "<<  c1.ObtenerVolumen() <<endl;
	cout<<"El Volumen del cilindro[2] es = "<<  c2.ObtenerVolumen() <<endl;
	return 0;
}

