#include <iostream>
#include <cmath>
using namespace std;

class EcuacionCuadratica {
	float m_a,m_b,m_c,m_valor,x1,x2;
public:
	EcuacionCuadratica(float a,float b,float c) {
		m_a = a;
		m_b = b;
		m_c = c;
	};
	bool TieneRaicesReales() {
		m_valor = (m_b*m_b)-4*m_a*m_c;
		
		if( m_valor<0 ){ return false; }
		else{ return true;	}
	}
	float VerRaiz1() {
		x1 = (-m_b + sqrt(m_valor))/(2*m_a);
		return x1;
	}
	float VerRaiz2() {
		x2 = (-m_b - sqrt(m_valor))/(2*m_a);
		return x2;
	}
	
	float VerParteReal() {
		return -m_b/(2*m_a);
	}
	float VerParteImag() {
		return sqrt(-(m_b*m_b)+4*m_a*m_c)/(2*m_a);
	}
};

int main() {
	float a,b,c;
	cout<<"valor de a = ";cin>>a;
	cout<<"valor de b = ";cin>>b;
	cout<<"valor de c = ";cin>>c;
	
	EcuacionCuadratica e(a,b,c);
	
	if( e.TieneRaicesReales() ) {
		cout<<"Posee raices reales: "<<endl;
		cout<<"X1 = "<<e.VerRaiz1()<<endl;
		cout<<"X2 = "<<e.VerRaiz2()<<endl;
		
	}else{
		cout<<"Posee raices complejas: "<<endl;
		cout<<"X1 = "<<e.VerParteReal()<<"+"<<e.VerParteImag()<<"*i"<<endl;
		cout<<"X2 = "<<e.VerParteReal()<<"-"<<e.VerParteImag()<<"*i"<<endl;
	}

	return 0;
}

