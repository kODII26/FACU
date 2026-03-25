#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Punto {
	float x,y;
};

class Recta{
public:
	virtual string ObtenerEcuacion()=0;
	virtual bool Pertenece(Punto g)=0;
	
	virtual ~Recta() {}
};

class RectaExplicita : public Recta {
	float m_m,m_b;
public:
	RectaExplicita (Punto p, Punto q){
		m_m= (q.y-p.y)/(q.x-p.x);
		m_b=p.y-m_m*p.x;
	}
	string ObtenerEcuacion ()override {
		string w= "y="+to_string(m_m)+"x+("+to_string(m_b)+")";
		return w;
	}
	bool Pertenece (Punto g) override {
		if (m_m*g.x+m_b-0.35 <= g.y <= m_m*g.x+m_b+0.35) {
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
	float a, b, c;
public:
	RectaGeneral(Punto p,Punto q) {
		a = p.y - q.y;
		b = p.x - q.x;
		c = -a*p.x - b*p.y;
	}
	string ObtenerEcuacion ()override {
		string w= "y = "+to_string(a)+"x^2 +("+to_string(b)+")x+("+to_string(c)+")";
		return w;
	}
	
	bool Pertenece (Punto g) override {
		if (a*pow(g.x,2)+b*g.x+c-0.35 <= g.y <= a*pow(g.x,2)+b*g.x+c+0.35){
			return true;
		}
		return false;
	}
	
	float VerA() { return a; }
	float VerB() { return b; }
	float VerC() { return c; }
	
	~RectaGeneral() {}
};

int main() {
	Punto p,q,g;
	cout<<"Indique el primer pto en x = ";cin>>p.x;
	cout<<"y = ";cin>>p.y;
	cout<<"Indique el segundo pto en x = ";cin>>q.x;
	cout<<"y = ";cin>>q.y;
	
	vector<Recta*> v;
	
	v.push_back(new RectaGeneral(p,q));
	v.push_back(new RectaExplicita(p,q));
	
	cout<<"Ecuacion de la recta General: "<<v[0]->ObtenerEcuacion()<<endl;
	cout<<"Ecuacion de la recta Explícita: "<<v[1]->ObtenerEcuacion()<<endl;
	
	
	cout<<endl<<"Ingrese nuevo punto (x): ";cin>>g.x;
	cout<<"en (y): ";cin>>g.y;
	if( v[0]->Pertenece(g) ) {
		cout<<"El punto pertenece a la recta General."<<endl;
	}else{
		cout<<"El punto NO pertenece a la recta General."<<endl;
	}
	
	if( v[1]->Pertenece(g) ) {
		cout<<"El punto pertenece a la recta Explícita."<<endl;
	}else{
		cout<<"El punto NO pertenece a la recta Explícita."<<endl;
	}
	
	for(Recta *z:v) delete z;
	return 0;
}

