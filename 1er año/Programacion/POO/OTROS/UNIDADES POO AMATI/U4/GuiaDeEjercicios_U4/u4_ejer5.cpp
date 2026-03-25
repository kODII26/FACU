#include <iostream>
using namespace std;

class Complejo {
	float preal, pimag;
public:
	
	Complejo(float pr,float pi) : preal(pr), pimag(pi) {}
	
	float operator[]( int i ) const {
		if ( i==0 ) return preal;
		else return pimag;
	}
	
	float &operator[]( int i ) {
		if ( i==0 ) return preal;
		else return pimag;
	}
};

int main() {
	Complejo a(0,0);
	float pr,pi;
	cout<<"Ingrese parte real: ";cin>>pr;
	cout<<"Ingrese parte imaginaria: ";cin>>pi;
	
	a[0] = pr;
	a[1] = pi;
	
	cout<<a[0]<<"+"<<a[1]<<"i"<<endl;
	
	return 0;
}

