#include <iostream>
#include <vector>
using namespace std;

struct Punto {
	float x,y;
};

class Recta {
	float a,b,c,m;
public:
	
	Recta(Punto p,Punto q, string tipo) {
		if( tipo=="RectaGeneral" ){
			a = p.y - q.y;
			b = p.x - q.x;
			c = -a*p.x - b*p.y;
		}else { 
			if( tipo=="RectaExplicita" ) {
				m = (q.y-p.y)/(q.x-p.x);
				b = p.y - m*p.x;
			}
			
		}
	}
	
	float VerA() { return a; }
	float VerB() { return b; }
	float VerC() { return c; }
	
	float verM() { return m; }
	float verB() { return b; }
	
	virtual string obtenerEcuacion()=0;
	virtual float pertenece()=0;
};

class RectaGeneral : public Recta {
	float a,b,c;
public:
	RectaGeneral(Punto p, Punto q) : Recta(p,q,"RectaGeneral") {}
	
	
	string obtenerEcuacion() {
		string ecu = to_string(a)+"*x +"+to_string(b)+"*y + "+to_string(c)+" = 0";
		return ecu;
	}
	
	float pertenece(Punto pto) {
		float resultado = VerA();
		return resultado;
	}
	
	
};

class RectaExplicita : public Recta {
	float m,b;
public:
	RectaExplicita(Punto p,Punto q) : Recta(p,q,"RectaExplicita") {}
	
	string obtenerEcuacion() {
		string func = "y = "+to_string(m)+"*x + "+to_string(b);
		return func;
	}
	

};

int main() {
	Punto p,q;
	cout<<"Indique el primer pto en x = ";cin>>p.x;
	cout<<"y = ";cin>>p.y;
	cout<<"Indique el segundo pto en x = ";cin>>q.x;
	cout<<"y = ";cin>>q.y;
	
	vector<Recta*> r;
	
	r.push_back(new RectaGeneral(p,q))

	cout<<r[0]->obtenerEcuacion()<<endl;
	
	return 0;
}

