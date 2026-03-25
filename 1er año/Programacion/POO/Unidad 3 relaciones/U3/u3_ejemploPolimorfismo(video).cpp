#include <iostream>
#include <vector>
using namespace std;

class Animal {
	string m_especie, m_nombre;
public:
	Animal(string especie, string nombre) {
		m_especie = especie;
		m_nombre = nombre;
	}
	string VerEspecie() { return m_especie; }
	string VerNombre() { return m_nombre; }
	virtual string Hablar() = 0;
	virtual ~Animal() {}
};

class Pulga {}; // para crear las pulgas en perro y demostrar la importancia de un destructor virtual.

class Perro : public Animal {
	Pulga *v;
public:  
	Perro(string nombre) : Animal("perro",nombre) {
		v = new Pulga[200];
	}
	string Hablar() { return "guau!"; } 
	
	~Perro() { 
		cout<<"El perro se sacude sus pulgas"<<endl;
		delete [] v; 
	}
	
};

class Gato : public Animal{
public:
	Gato(string nombre) : Animal("gato",nombre) {}
	string Hablar() { return "miau!";}
};

class TortugaNinja : public Animal {
public:
	TortugaNinja(string nombre) : Animal("tortuga",nombre) {}
	string Hablar() { return "kawabunga!"; }
};


int main() {
	vector<Animal*> v;
	
	v.push_back(new Perro("Dante"));
	v.push_back(new Perro("Coraje"));
	v.push_back(new Gato("Bola de Nieve"));
	v.push_back(new TortugaNinja("DonatoFreefire"));
	v.push_back(new TortugaNinja("Michelangelo"));
	v.push_back(new TortugaNinja("Leonardo"));
	
	do {
		
	int i= rand()%v.size();
	cout<<"El "<<v[i]->VerEspecie()<<" "<<v[i]->VerNombre()<<" dice: "<<v[i]->Hablar()<<endl;
	
	} while(cin.get()=='\n');  //si quiere q se repita ingrese enter.
	
	for(Animal *p:v) delete p;//p apunta al puntero v que contiene los espacios de Animal.
	
	return 0;
}

