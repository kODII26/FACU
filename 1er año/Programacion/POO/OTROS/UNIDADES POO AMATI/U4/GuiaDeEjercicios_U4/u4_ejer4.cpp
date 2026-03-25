#include <iostream>
using namespace std;

class Complejo {
	float num,den;
public:
	Complejo(float n,float d) : num(n), den(d) {}
	
	void CargarNum(float n) { num = n; }
	void CargarDen(float d) { den = d; }
	
	float VerNum() { return num; }
	float VerDen() { return den; }
	
	Complejo operator+(Complejo x) const {
		Complejo suma(
		this->num*x.den + this->den*x.num ,
		this->den*x.den );
		return suma;
	}
	
	Complejo operator-(Complejo x) const {
		Complejo resta(
		this->num*x.den - this->den*x.num ,
		this->den*x.den );
		return resta;
	}
	
	Complejo operator*(Complejo x) const {
		Complejo mult(
		this->num*x.num ,
		this->den*x.den );
		return mult;
	}
	
	bool operator==(Complejo &x) const {
		float resultado1 = this->num/this->den;
		float resultado2 = x.num/x.den;
		
		if ( resultado1 == resultado2 ) return true;
		else return false;
	}
};


istream &operator>>(istream &i,Complejo &x){
	float n,d;
	cout<<"Ingrese numerador: ";i>>n;
	cout<<"Ingrese denominador: ";i>>d;
	x.CargarNum(n);
	x.CargarDen(d);
	
	return i;
}

ostream &operator<<(ostream &o,Complejo &x) {
	o<< x.VerNum() <<"/"<< x.VerDen()<<"  ";
	return o;
}

int main() {
	Complejo a(0,1),b(0,1),c(0,1);
	cin>>a>>b;
	cout<<a<<b;
	
	c = a+b;
	cout<<endl<<c;
	
	c = a-b;
	cout<<endl<<c;
	
	c = a*b;
	cout<<endl<<c<<endl;
	
	if( a == b ) cout<<"son iguales. ";
	else cout<<"son distintos. ";
	
	return 0;
}

