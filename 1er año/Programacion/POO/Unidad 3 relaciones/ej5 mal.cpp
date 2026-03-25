#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class Monomio {
	int m_coef,m_base,m_exp;
public:
	Monomio (int coef, int base, int exp): m_coef(coef),m_base(base),m_exp(exp) {} 
	 int evaluar () {
		return m_coef*pow(m_base,m_exp);
	}
	int getCoef() {return m_coef;}
	int getBase() {return m_base;}
	int getExp() {return m_exp;}
};
class Polinomio {
	int m_grado;
	vector<Monomio> m_v;
public: 
	Polinomio (int grado): m_grado(grado){ }
	void agregarMon (Monomio x) {
		m_v.push_back(x);
	}
	int evaluar() {
		int r=0;
		for (size_t i=0;i<m_v.size();i++){
			r += m_v[i].getCoef()*pow(m_v[i].getBase(),m_v[i].getExp());
		}
		return r;
	}
};
int main() {
	int coef,base,exp;
	cout<<"Ingrese coef base y exp"<<endl;
	cin>>coef>>base>>exp;
	Monomio q(coef,base,exp);
	cout<<q.evaluar();

	int cant;
	cout<<endl<<"Cuantos terminos tiene el polinomio"<<endl;
	cin>>cant;
	Polinomio f(cant);
	for (int i=0;i<cant;i++){
		cout<<"Ingrese coef base y exp"<<endl;
		cin>>coef>>base>>exp;
		Monomio q(coef,base,exp);
		f.agregarMon(q);
	}
	cout<<"El polinomio da:"<<f.evaluar();
	return 0;
}
// El resultado da mal nose pq
