#include <iostream>
using namespace std;

class CuentaObjetos {
	static int cont;
public:
	CuentaObjetos() { ++cont; }
	
	~CuentaObjetos() { --cont; }
	
	static VerContador() { return cont; }
};

int CuentaObjetos :: cont = 0;

int main() {
	
	CuentaObjetos *p = new CuentaObjetos[10];
	
	cout<<CuentaObjetos::VerContador()<<endl;
	
	delete [] p;
	
	cout<<CuentaObjetos::VerContador()<<endl;
	
	return 0;
}

