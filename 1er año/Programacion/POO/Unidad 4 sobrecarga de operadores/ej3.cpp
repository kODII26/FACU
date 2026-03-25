#include <iostream>
using namespace std;
class Racional {
	float num, den;
public:
	Racional (float n,float d) : num(n), den(d) {}
	float VerNum ()const {return num;}
	float VerDen ()const {return den;}
	void cargarNum (float n) {num=n;}
	void cargarDen (float d) {den=d;}
};
istream &operator>>( istream &i, Racional &c) {
	float n; i>>n; c.cargarNum(n);
	float d; i>>d; c.cargarDen(d);
	return i;
}
ostream &operator<<(ostream &o, const Racional &c){
	o<<c.VerNum()<<"/", o<<c.VerDen();
	return o;
}
int main() {
	Racional a(3,4);
	cout<<a<<endl;
	cin>>a;
	cout<<a<<endl;
	
	return 0;
}

