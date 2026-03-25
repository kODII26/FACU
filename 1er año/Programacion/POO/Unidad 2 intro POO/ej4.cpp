#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;
class VectorDinamico {
	int *m_p;
	int m_n;
	vector<int> v;
public: 
	VectorDinamico (int n): m_n(n) {
		v.resize(m_n);
		m_p = &v[0];
		for (int i=0;i<n;i++){
			m_p[i]= rand()%100;
		}
	}
	void Duplicar() {
		int c= v.size();
		v.resize(m_n*2);
		m_p = new int[v.size()];
		m_p = &v[0];
		for (size_t i=c;i<m_n*2;i++){
			m_p[i] = rand()%5;
		}
	}
	int verElemento (int pos) {
		return *(m_p+pos);
	}
	
	void mostrarV () {
		for ( size_t i=0;i<v.size();i++){
			cout<<m_p[i]<<setw(4);
		}
	}
	
	~VectorDinamico() {
		delete [] m_p;
	};
};

int main() {
	int n;
	cout<<"ingrese cantidad"<<endl;
	cin>>n;
	VectorDinamico p1(n);
	p1.mostrarV();
	cout<<endl;
	p1.Duplicar();
	p1.mostrarV();
	cout<<endl<<" elemento "<<endl;
	cout<<p1.verElemento(2);
	return 0;
}

