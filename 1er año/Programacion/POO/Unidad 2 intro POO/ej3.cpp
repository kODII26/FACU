#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
class Polinomio {
	int m_t;
	vector<int> v;
public: 
	Polinomio (int grado): m_t(grado),v(grado,0){};
	void MostrarPolinomio () {
		for (int i=m_t-1;i>-1;i--){
			cout<<v[i]<<"^"<<i<<"+" ;
		}
		
	}
	void cambiaCoef (int coef,int i){
		v[i]=coef;
	}
	int evaluar(int x){
		int res=0;
		for (int i=0;i<m_t;i++){
			res += v[i]*pow(x,i);
		}
		return res;
	}
	Polinomio Sumar(Polinomio p1, Polinomio p2){
		Polinomio suma(3);
		if (p1.m_t > p2.m_t) {
			suma.m_t=p1.m_t;
			int c=0;
			for (int i=0;i<p2.m_t;i++){
				suma.v[i] = p1.v[i]+p2.v[i];
				c++;
			}
			for (int i=c ; i<p1.m_t;i++){
				suma.v[i]= p1.v[i];
			}
		}
		else {
			suma.m_t=p2.m_t;
			int c=0;
			for (int i=0;i<p1.m_t;i++){
				suma.v[i] = p1.v[i]+p2.v[i];
				c++;
			}
			for (int i=c ; i<p2.m_t;i++){
				suma.v[i]= p2.v[i];
			}
		}
		return suma;
	}
	~Polinomio(){}
};
int main() {
	int grado,coef,x;
	cout<<"grado"<<endl;
	cin>>grado ;
	Polinomio p1(grado+1);
	cout<<endl;
	for (int i=grado;i>-1;i--){
		cout<<"Asigne valor al coef de grado "<<i<<":";cin>>coef;
		p1.cambiaCoef(coef,i);

	}
	p1.MostrarPolinomio();
	cout<<endl<<" x para evaluar"<<endl;
	cin>>x;
	cout<<"El polinomio evaluado con "<<x<<" da : "<<p1.evaluar(x)<<endl;
	cout<<"Ingrese grado de 2do polinomio para sumar"<<endl;
	cin>>grado;
	Polinomio p2(grado+1);
	for (int i=grado;i>-1;i--){
		cout<<"Asigne valor al coef de grado "<<i<<":";cin>>coef;
		p2.cambiaCoef(coef,i);
	}
	p2.MostrarPolinomio();
	Polinomio resultado= resultado.Sumar(p1,p2);
	cout<<endl<<"El polinomio resultante es: "<<endl;
	resultado.MostrarPolinomio();
	return 0;
}

