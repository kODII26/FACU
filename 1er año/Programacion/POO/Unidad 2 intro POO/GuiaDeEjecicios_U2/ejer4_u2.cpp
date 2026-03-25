#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

class VectorDinamico {
	int *m_p;
	int m_n;
	vector<int> v;
public:
	VectorDinamico(int n) : m_n(n) {
		v.resize(m_n);
		m_p = & v[0]; 
		for(int i=0; i<m_n; ++i) {
			*(m_p+i) = rand()%90 +10;
		}
	}
	
	void Duplicar() {
		int comienzo = v.size();//desde donde se agregan los nuevos valores.
		v.resize(v.size()*2);//agrandamos el vector.
		m_p = new int[v.size()];//le damos la cantidad de espacio apuntada nueva.(se borra la anterior)
		m_p = &v[0];//le asignamos-> la priimera direccion a la primera pos del vector.
		
		for(size_t i=comienzo; i<v.size(); ++i) {//se arranca desde comienzo para no aplastar los valores anteriores.
			m_p[i] = rand()%90+10;
		}
	}
	
	void VerElemento(int i) {
		cout<<m_p[i]<<" ";
	}
	
	void VerVector() {
		for(size_t i=0; i<v.size(); ++i) {
			cout<<v[i]<<" ";
		}
		cout<<endl;
	}
	
	~VectorDinamico() {
		delete [] m_p;
	}
};

int main() {
	int n;
	cout<<"Indique el tamanio del vector: ";cin>>n;
	VectorDinamico v(n);
	
	for(int i=0; i<n; ++i) {
		v.VerElemento(i);
	}
	cout<<endl;
	
	v.Duplicar(); n = n*2;//se duplica n para darle el límite acordado al for(...).
	
	for(int i=0; i<n; ++i) {
		v.VerElemento(i);
	}
	cout<<endl;
	
	v.VerVector();
	
	return 0;
}


