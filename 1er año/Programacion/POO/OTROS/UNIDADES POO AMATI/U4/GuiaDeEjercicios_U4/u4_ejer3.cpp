#include <iostream>
using namespace std;

class Racional {
	int num, den;
public:
	Racional(int n, int d) : num(n), den(d) {}
	
	void CargarNum(int n) { num = n; }
	void CargarDen(int d) { den = d; }
	
	int VerNum() { return num; }
	int VerDen() { return den; }
	
};

istream &operator>>(istream &i, Racional &x){
	int n,d;
	cout<<"Ingrese el valor del numerador: ";i>>n;
	cout<<"Ingrese el valor del denominador: ";i>>d;
	x.CargarNum(n);
	x.CargarDen(d);
	return i;
}

ostream &operator<<(ostream &o,Racional &x) {
	o<<x.VerNum()<<"/"<<x.VerDen();
	return o;
}

int main() {
	Racional a(0,1);
	
	cin>>a;
	cout<<a;
	
	
	return 0;
}


