#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Monomio {
protected:
	float m_coef,m_exp;
public:
	Monomio(float c,float e) : m_coef(c),m_exp(e) {}
	
	float Evaluar(float num) { return m_coef*pow(num,m_exp); }
	
	virtual ~Monomio() {}
};

class Polinomio : public Monomio{
	vector<Monomio> v;
	int m_n;
public:
	Polinomio(float exp) : Monomio(0,exp) {
		m_n = exp+1;
		
		for(int i=0;i<m_n;++i){
			float coef;
			cout<<"Ingrese coef de grado["<<i<<"]: ";cin>>coef;
			Monomio m(coef,i);
			v.push_back(m);
		}
	}
	
	float Evaluar(float num){
		float suma = 0;
		for(size_t i=0; i<v.size(); ++i) {
			suma += v[i].Evaluar(num);
		}
		return suma;
	}
		
	~Polinomio() {}
};

int main() {
	float coef,exp,num;
	cout<<"Coef para monomio: ";cin>>coef;
	cout<<"Exp para monomio: ";cin>>exp;
	Monomio m(coef,exp);
	cout<<"Indique numero real para evaluar: ";cin>>num;
	cout<<"Resultado: "<<m.Evaluar(num)<<endl;
	
	cout<<"Ingrese grado del polinomio: ";cin>>exp;
	Polinomio p(exp);
	cout<<"Ingrese numero para evaluar polinomio: ";cin>>num;
	cout<<"Resultado: "<<p.Evaluar(num)<<endl;
	
	return 0;
}

