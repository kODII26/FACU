#include <iostream>
#include <sstream>
using namespace std;
struct Punto {
	float x;
	float y;
};
class RectaExplicita {
	float m,b;
public:
	RectaExplicita (Punto p, Punto q){
		m= (q.y-p.y)/(q.x-p.x);
		b=p.y-m*p.x;
	}
	string obtenerEcuacion (){
		string w= "y="+to_string(m)+"x+"+to_string(b);
		return w;
	}
	float verM(){
		return m;
	}
	float verB(){
		return b;
	}
	~RectaExplicita () {}
};
int main() {
	Punto x1;
	x1.x=-2;
	x1.y=4;
	Punto x2;
	x2.x=-9;
	x2.y=0;
	RectaExplicita m( x1,  x2);
	cout<<m.obtenerEcuacion();
	cout<<endl;
	
	return 0;
}

