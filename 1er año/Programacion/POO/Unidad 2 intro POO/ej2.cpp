#include <iostream>
#include <cmath>
using namespace std;
class EcuacionCuadratica {
	float m_a,m_b,m_c;
	float m_r1,m_r2;
	float m_d;
public:
	EcuacionCuadratica (float a, float b, float c){
		m_a= a; m_b= b; m_c= c;
	}
	bool TieneRaicesReales() {
		m_d= m_b*m_b-4*m_a*m_c;
		if (m_d>0) {return true;}
		return false; 
	}
	float VerRaiz1() {
		if (TieneRaicesReales()) {
			m_r1= (-m_b+sqrt(m_d))/2*m_a;
			return m_r1;
		}
		return -1;
	}
	float VerRaiz2(){
		if (TieneRaicesReales()){
			m_r2= (-m_b-sqrt(m_d))/2*m_a;
			return m_r2;
		}
	return -1;
	}
	float VerParteReal () {
		m_r1= -m_b/(2*m_a);
		return m_r1;
	}
	float VerParteImag () {
		m_r2= sqrt(-m_d)/(2*m_a);
		return m_r2;
	}
	~EcuacionCuadratica (){}
};
int main() {
	float a,b,c;
	cin>>a>>b>>c;
	EcuacionCuadratica x(a,b,c);
	if (x.TieneRaicesReales()){
		cout<<" Tiene raices reales"<<endl;
		cout<<"r1: "<<x.VerRaiz1()<<endl;
		cout<<"r2: "<<x.VerRaiz2()<<endl;
	} else {
		cout<<" Tiene raices imaginarias"<<endl;
		cout<<"r1: "<<x.VerParteReal()<<"+"<<x.VerParteImag()<<"i"<<endl;
		cout<<"r2: "<<x.VerParteReal()<<"-"<<x.VerParteImag()<<"i"<<endl;
	}
	
	return 0;
}

