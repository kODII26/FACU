#include <iostream>
#include <vector>
using namespace std;
class Color {
	float m_r, m_g,m_b;
public:
	Color (float r, float g, float b) : m_r(r),m_g(g),m_b(b){}
	float getRed () {return m_r;}
	float getGreen () {return m_g;}
	float getBlue () {return m_b;}
	Color operator+ (Color b) {
		this->m_r= this->m_r+b.getRed();
		this->m_g= this->m_g+b.getGreen();
		this->m_b= this->m_b+b.getBlue();
		return *this;
	}
	void Normalizar () {
		if (this->m_r>1){ m_r=1;}
		if (this->m_g>1){ m_g=1;}
		if (this->m_b>1){ m_b=1;}
	}
};

ostream &operator<<(ostream &o,Color c){
	o<<"r="<<c.getRed()<<" g="<<c.getGreen()<<" b="<<c.getBlue()<<endl;
	return o;
}

class Personaje {
	string m_nom;
	Color m_c;
	vector<string> m_poderes;
public:
	Personaje (string nom, Color c) : m_nom(nom),m_c(c){}
	bool tienePoder (string nombre){
		for (size_t i=0;i<m_poderes.size();++i){
			if (nombre==m_poderes[i]){
				return true;
			}
		}
		return false;
	}
	bool agregarPoder (string nombree, Color p) {
		if (this->tienePoder(nombree)) {return false;}
		m_poderes.push_back(nombree);
		m_c+p;
		m_c.Normalizar();
		return true;
	}
	Color verColor () {return m_c;}
	string verNombre () {return m_nom;}
};

int main() {
	Color q (1,0,0);
	Color c (0.1,0,1);
	
	Personaje p("Justo",q);
	p.agregarPoder("Rayo laser",c);
	cout<<p.verColor()<<" "<<p.verNombre();
	return 0;
}

