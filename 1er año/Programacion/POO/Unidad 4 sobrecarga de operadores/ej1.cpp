#include <iostream>
using namespace std;
class Racional {
	int num, den;
public:
	Racional (int n, int d) : num(n), den(d) {}
	int VerNum () {return num;}
	int VerDen () {return den;}
//	Racional operator+ (Racional c) {    //Esta forma crea otro objeto y lo retorna, gastando mas memoria
////		int a_num=(this->num*c.den)+(c.num*this->den);
////		int a_den= this->den*c.den;
//		Racional suma((this->num*c.den)+(c.num*this->den),this->den*c.den); //se pueden hacer los calculos directamente en la declaracion 
//		return suma;
//	}
	Racional &operator+(Racional c) {  //Esta forma modifica y devuelve el objeto, ahorrando memoria 
		this->num=(this->num*c.den)+(c.num*this->den);
		this->den=this->den*c.den;
		return *this;
	}
	Racional operator* (int n) {
		Racional multiplicacion(this->num*n,this->den);
		return multiplicacion;
	}
	Racional &operator++ () { // pre incremento
		num += den;
		return *this;
	}
	Racional operator++ (int) { // post incremento
		Racional aux= *this;
		num +=den;
		return aux;
	}
	
};
int main() {
	Racional a(3,4), b(2,7),c(2,2), suma(0,0), multi(0,0);
	suma= a+b+c; 
	cout<<suma.VerNum () <<"/"<<suma.VerDen()<<endl;
	multi= a*10;
	cout<<multi.VerNum()<<"/"<<multi.VerDen()<<endl;
	++a; // pre
	cout<<a.VerNum()<<"/"<<a.VerDen()<<endl;
	b++; //post
	cout<<b.VerNum()<<"/"<<b.VerDen()<<endl;
	return 0;
}

