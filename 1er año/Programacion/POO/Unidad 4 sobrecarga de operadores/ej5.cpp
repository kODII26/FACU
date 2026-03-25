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
	float operator[] (int i) const {
		if (i==0) return preal;
		else return pimag;
	}
	float &operator[] (int i) {
		if (i==0) return preal;
		else return pimag;
	}
};
int main() {
//	Complejo c(1,2);
//	cout<<"parte real:"<<c[0]<<endl;
//	cout<<"parte imag:"<<c[1]<<endl;
	Complejo c(0,0);
	cout<<"Ingrese parte real: "<<endl;
	cin>>c[0];
	cout<<"Ingrese partea imag: "<<endl;
	cin>>c[1];
	cout<<"parte real:"<<c[0]<<endl;
	cout<<"parte imag:"<<c[1]<<endl;
	return 0;
}

