#include <iostream>
using namespace std;

template<typename T,typename T2>
class Rect {
	T x1,y1;
	T2 x2,y2;
public:
	Rect(T a1,T b1,T2 a2,T2 b2) : x1(a1),y1(b1),x2(a2),y2(b2) {}
	
	T2 VerAltura() {
		if(y1 > y2){
			return y1-y2;
		}
		return y2-y1;
	}
	
	T2 VerAncho() {
		if(x1 > x2){
			return x1-x2;
		}
		return x2-x1;
	}
};

int main() {
	int x1,y1;
	double x2,y2;
	cout<<"Ingrese primera cord: "<<endl;
	cout<<"x1 = ";cin>>x1;
	cout<<"y1 = ";cin>>y1;
	cout<<"Ingrese segunda cord: "<<endl;
	cout<<"x2 = ";cin>>x2;
	cout<<"y2 = ";cin>>y2;
	Rect<int,double> r(x1,y1,x2,y2);
	
	cout<<"Altura del rectangulo = "<< r.VerAltura() <<endl;
	cout<<"Ancho del rectangulo = "<< r.VerAncho() <<endl;
	return 0;
}

