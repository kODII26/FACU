#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
struct Punto {
	float x;
	float y;
};

class Recta {
	
public:
	virtual string obtenerEcuacion () =0;
	virtual bool pertenece (Punto g) =0;
	virtual ~Recta () {}
};

class RectaExplicita : public Recta {
	float m_m,m_b;
public:
	RectaExplicita (Punto p, Punto q){
		m_m= (q.y-p.y)/(q.x-p.x);
		m_b=p.y-m_m*p.x;
	}
	string obtenerEcuacion ()override {
		string w= "y="+to_string(m_m)+"x+("+to_string(m_b)+")";
		return w;
	}
	bool pertenece (Punto g) override {
		if (g.y==m_m*g.x+m_b) {
			return true;
		} else {
			return false;
		}
	}
	float verM(){return m_m;}
	float verB(){return m_b;}
	~RectaExplicita () {}
};

class RectaGeneral : public Recta {
	float m_a,m_b,m_c;
public:
	RectaGeneral (Punto p, Punto q){
		m_a=q.y - p.y;
		m_b=p.x - q.x;
		m_c=-m_a*p.x - m_b*p.y;
	}
	string obtenerEcuacion ()override {
		string w= "y="+to_string(m_a)+"x+("+to_string(m_b)+")y+("+to_string(m_c)+")=0";
		return w;
	}
	bool pertenece (Punto g) override {
		if (g.y*m_b== m_a*g.x+m_c){
			return true;
		} else { return false ;}
	}
	float verA(){return m_a;}
	float verB(){return m_b;}
	float verC(){return m_c;}
	~RectaGeneral () {}
};
int main() {
	Punto x1,x2,g;
	x1.x=1; x1.y=-2; x2.x=3; x2.y=4;
	RectaExplicita m(x1,x2);
	cout<<m.obtenerEcuacion()<<endl;
	g.x=1; g.y=-2;
	if (m.pertenece(g)) {
		cout<<"El punto ingresado pasa por la recta"<<endl;
	} else {
		cout<<"El punto ingresado no pasa por la recta"<<endl;
	}
	
	RectaGeneral f(x1,x2);
	cout<<f.obtenerEcuacion()<<endl;
	g.x=1; g.y=2;
	if (f.pertenece(g)) {
		cout<<"El punto ingresado pasa por la recta"<<endl;
	} else {
		cout<<"El punto ingresado no pasa por la recta"<<endl;
	}
	
	return 0;
}

