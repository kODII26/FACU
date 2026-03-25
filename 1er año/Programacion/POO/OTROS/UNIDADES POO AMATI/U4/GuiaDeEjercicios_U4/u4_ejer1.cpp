#include <iostream>
using namespace std;

class Racional {
	int num, den;
public:
	Racional(int n, int d) : num(n), den(d) {}
	
	int VerNum() { return num; }
	int VerDen() { return den; }
	
	Racional operator+(Racional x) const {
		Racional suma(
			this->num*x.den + this->den*x.num ,
			this->den * x.den );
		return suma;
	}
	
	Racional operator*(Racional entero) const {
		Racional mult(
			this->num*entero.num ,
			this->den*entero.den );
		return mult;
	}
	
	Racional operator++() {
		num = num + den;
		return *this;
	}
};

int main() {
	Racional a(3,5),b(2,3), c(0,1);//c = 0/1
	
	c = a+b;
	cout<<c.VerNum()<<"/"<<c.VerDen()<<endl;

	c = a*b*c;
	cout<<c.VerNum()<<"/"<<c.VerDen()<<endl;
	
	++a;
	cout<<a.VerNum()<<"/"<<a.VerDen()<<endl;
	
	
	
	return 0;
}

