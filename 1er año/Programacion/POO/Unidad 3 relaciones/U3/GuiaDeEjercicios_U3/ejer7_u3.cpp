#include <iostream>
#include <vector>
using namespace std;

class Instrumento {
public:
	virtual string VerTipo() { return "sin_nombre"; }
};

class Guitarra : public Instrumento {
	
};

class Piano : public Instrumento {
public:	
	
	string VerTipo() { return "piano"; }
	
	virtual void Apretar() {cout<<"...";};
	
	virtual string VerNota() { return "pedal"; }

	virtual void Soltar() {cout<<"suelto";}
	
	virtual bool Apretada() { return false; }
	
	virtual void ModificarPresion(float presion) {cout<<"modificada"; }
	
	virtual float  VerPresion() { return 0.0; }
	
};

class Tecla : public Piano {
	string m_nombre, m_estado;
public:
	Tecla(string nombreN) {
		m_nombre = nombreN;
	}
	
	string VerNota() { return m_nombre; }
	void Apretar() { m_estado = "apretada"; }
	void Soltar() { m_estado = "no apretada"; }
	bool Apretada() { 
		if(m_estado == "apretada") {
			return true;
		}else { return false; }
	}
};

class Pedal : public Piano {
	float m_presion;
public:
	Pedal() {
		m_presion = 0;
	}
	
	void ModificarPresion(float presion) {
		m_presion += presion;
	}
	
	void Soltar() { m_presion=0; }
	
	float VerPresion() { return m_presion; }
};

int main() {
	vector<Instrumento*> x;
	x.push_back(new Piano());
	vector<Piano*> p;
	
	string nom_nota;
	for(int i=0; i<7; ++i) {
		cout<<"Indique nombre de la Nota["<<i<<"]: ";cin>>nom_nota;
		p.push_back(new Tecla(nom_nota));
	}
	
	p.push_back(new Pedal());
	
	float presion;
	int pos_nota;
	string op="si";
	while( op != "no"){
		cout<<"Indique presion a asignar al pedal(- o +) : ";cin>>presion;p[7]->ModificarPresion(presion);
		
		cout<<"teclas del "<<x[0]->VerTipo()<<": "<<endl;
		for(int i=0; i<7; ++i) {
			cout<<i<<")"<<p[i]->VerNota()<<"  ";
		}
		cout<<endl;
		cout<<"Indique nro de nota a presionar(0-6): ";cin>>pos_nota;p[pos_nota]->Apretar();
		cout<<"NOTAS SONANDO con una presion del pedal igual a "<<p[7]->VerPresion()<<": "<<endl;
		for(int i=0; i<7; ++i) {
			if(p[i]->Apretada()){
				cout<<p[i]->VerNota()<<"! 	";
			}
		}
		cout<<endl;
		cout<<"Indique la nota(0-6) a soltar: ";cin>>pos_nota;p[pos_nota]->Soltar();
		
		cout<<"sigo?: ";cin>>op;
	} 

	for(Instrumento *a: x) delete [] a;
	for(Piano *b: p) delete [] b;
	
	
	return 0;
}

