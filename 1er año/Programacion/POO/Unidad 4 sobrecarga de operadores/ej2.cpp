#include <iostream>
using namespace std;
class Racional {
	float num, den;
public:
	Racional (float n,float d) : num(n), den(d) {}
	float VerNum ()const {return num;}
	float VerDen ()const {return den;}
};
bool operator< (const Racional &r1, const Racional &r2)  {
	if (r1.VerNum()/r1.VerDen() < r2.VerNum()/r2.VerDen()) 
		return true;
	else return false;
}
bool operator<= (const Racional &r1,const Racional &r2) {
	if (r1.VerNum()/r1.VerDen() < r2.VerNum()/r2.VerDen() or r1.VerNum()/r1.VerDen() == r2.VerNum()/r2.VerDen()) 
		return true;
	else return false;
}
bool operator> (const Racional &r1,const Racional &r2) {
	if (r1.VerNum()/r1.VerDen() > r2.VerNum()/r2.VerDen())
		return true;
	else return false;
}
bool operator>= (const Racional &r1,const Racional &r2) {
	if (r1.VerNum()/r1.VerDen() > r2.VerNum()/r2.VerDen() or r1.VerNum()/r1.VerDen() == r2.VerNum()/r2.VerDen()) 
		return true;
	else return false;
}
bool operator== (const Racional &r1,const Racional &r2) {
	if (r1.VerNum()/r1.VerDen() == r2.VerNum()/r2.VerDen())
		return true;
	else return false;
}
bool operator!= (const Racional &r1,const Racional &r2) {
	if (r1.VerNum()/r1.VerDen() != r2.VerNum()/r2.VerDen())
		return true;
	else return false;
}
int main() {
	Racional a(3,4),b(3,4);
	if (a<=b) 
		cout<<"es menor o igual"<<endl;
	else cout<<"no es menor"<<endl;
	return 0;
}

