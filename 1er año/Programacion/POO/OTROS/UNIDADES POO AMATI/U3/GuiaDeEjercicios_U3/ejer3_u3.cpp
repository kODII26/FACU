#include <iostream>
using namespace std;

struct Punto {
	int x,y;
};

class RectaExplicita {
	float m,b;
public:
	RectaExplicita(Punto p,Punto q) {
		m = (q.y-p.y)/(q.x-p.x);
		b = p.y - m*p.x;
	}
	
	string obtenerEcuacion() {
		string func = "y = "+to_string(m)+"*x + "+to_string(b);
		return func;
	}
	
	float verM() { return m; }
	float verB() { return b; }
};

int main() {
	Punto p,q;
	cout<<"x1 = ";cin>>p.x;
	cout<<"y1 = ";cin>>p.y;
	cout<<"x2 = ";cin>>q.x;
	cout<<"y2 = ";cin>>q.y;
	
	RectaExplicita r(p,q);
	
	cout<<r.obtenerEcuacion();
	
	return 0;
}

