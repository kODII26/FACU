#include <iostream>
using namespace std;

class Racional {
	int num, den;
public:
	Racional(int n, int d) : num(n), den(d) {}
	
	int VerNum() { return num; }
	int VerDen() { return den; }
	
	bool operator<(const Racional &x) const {
		float resultado1 = (num/den);
		float resultado2 = (x.num/x.den);
		if( resultado1 < resultado2 ) {
			return true;
		}else { return false; }
	}
	
	bool operator<=(const Racional &x) const {
		float resultado1 = (num/den);
		float resultado2 = (x.num/x.den);
		if( resultado1 <= resultado2 ) {
			return true;
		}else{ return false; }
	}
	
	bool operator>(const Racional &x) const {
		float resultado1 = (num/den);
		float resultado2 = (x.num/x.den);
		if( resultado1 > resultado2 ) {
			return true;
		}else { return false; }
	}
	
	bool operator>=(const Racional &x) const {
		float resultado1 = (num/den);
		float resultado2 = (x.num/x.den);
		if( resultado1 >= resultado2 ) {
			return true;
		}else { return false; }
	}
	
	bool operator==(const Racional &x) const {
		float resultado1 = (num/den);
		float resultado2 = (x.num/x.den);
		if( resultado1 == resultado2 ) {
			return true;
		}else { return false; }
	}
	
	bool operator!=(const Racional &x) const {
		float resultado1 = (num/den);
		float resultado2 = (x.num/x.den);
		if( resultado1 != resultado2 ) {
			return true;
		}else { return false; }
	}
};

int main() {
	Racional a(2,1),b(2,1), c(0,1);//c = 0/1
	
	if( a <= b ){
		cout<<a.VerNum()<<"/"<<a.VerDen()<<endl;
	}else{
		cout<<b.VerNum()<<"/"<<b.VerDen()<<endl;
	}
	
	if( a == b ) cout<<"son iguales."<<endl;
	else cout<<"son distintos."<<endl;
	
	if( a != b ) cout<<"son distintos."<<endl;
	else cout<<"son iguales."<<endl;
	return 0;
}
