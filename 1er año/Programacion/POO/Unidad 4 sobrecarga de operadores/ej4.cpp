#include <iostream>
using namespace std;
class Complejo{
	float preal, pimag;
public:
	Complejo (float real, float imag) : preal(real), pimag(imag) {}
	float verPreal ()const {return preal;}
	float verPimag ()const {return pimag;}
	void cargarPreal (float r) {preal=r;}
	void cargarPimag (float i) {pimag=i;}
	Complejo operator+ (const Complejo &c){
		Complejo suma(this->preal+c.preal, this->pimag+c.pimag);
		return suma;
	}
	bool operator== (const Complejo &c) {
		if (this->preal==c.preal && this->pimag==c.pimag)
			return true;
		else return false;
	}
};

Complejo operator* (const Complejo a,const Complejo b) {
	Complejo multi(a.verPreal()*b.verPreal(),a.verPimag()*b.verPimag());
	return multi;
}
Complejo operator- (const Complejo a,const Complejo b) {
	Complejo resta(a.verPreal()-b.verPreal(),a.verPimag()-b.verPimag());
	return resta;
}
istream &operator>> (istream &i, Complejo &c){
	float p; i>>p; c.cargarPreal(p);
	float imag; i>>imag; c.cargarPimag(imag);
	return i;
}
ostream &operator<< (ostream &o, const Complejo &c) {
	o<<c.verPreal()<<"+";
	o<<c.verPimag()<<"i";
	return o;
}
int main() {
	Complejo a(1,1), b(1,1),suma(0,0),resta (0,0), multi(0,0);
	suma= a+b;
	cout<<suma<<endl;
	resta= a-b;
	cout<<resta<<endl;
	multi = a*b;
	cout<<multi<<endl;
	if (a==b)
		cout<<"son iguales"<<endl;
	return 0;
}

