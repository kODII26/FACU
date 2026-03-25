#include <iostream>
#include <vector>
using namespace std;
class Tecla {
	bool m_estado;
	string m_nota;
public:
	Tecla (string nota){
		m_nota=nota;
		m_estado= false;
	}
	string verNota () {return m_nota;}
	void apretar () {m_estado = true;}
	void soltar () {m_estado = false;}
	bool estaApretada () {
		if (m_estado){
			return true;
		} else {
			return false;
		}
	}
};
class Pedal {
	float m_presion;
public:
	Pedal () : m_presion(0) {}
	void modPresion (float presion) {m_presion=presion;}
	float verPresion () {return m_presion;}
};
class Piano {
	vector<Tecla*> m_v;
	Pedal m_p;
public:
	Piano (){
		m_v.push_back( new Tecla("do"));
		m_v.push_back( new Tecla("re"));
		m_v.push_back( new Tecla("mi"));
		m_v.push_back( new Tecla("fa"));
		m_v.push_back( new Tecla("sol"));
		m_v.push_back( new Tecla("la"));
		m_v.push_back( new Tecla("si"));
	}
	string apretarTecla (int n){
		m_v[n]->apretar();
		return m_v[n]->verNota();
	}
	void soltarTecla (int n) {
		m_v[n]->soltar();
	}
	void apretarPedal (float n) {
		m_p.modPresion(n);
	}
	float verPresion() {
		return m_p.verPresion();
	};
	string estadoTecla (int n) {
		if (m_v[n]->estaApretada()) {
			return "esta apretada";
		} else {
			return "no esta apretada";
		}
	}
	~Piano() {
		for (size_t i=0;i<m_v.size();i++){
			delete m_v[i];
		}
	};
};

int main() {
	Piano p;
	cout<<p.apretarTecla(2)<<endl;
	cout<<p.estadoTecla(2)<<endl;
	p.soltarTecla(2);
	cout<<p.estadoTecla(2)<<endl;
	p.apretarPedal(0.5);
	cout<<p.verPresion();
	return 0;
}

