#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class VectorDinamico {
	int *m_p;
	int m_n;
public:
	VectorDinamico(int n) {
		m_n = n;
		m_p = new int[m_n];
	}
	
	VectorDinamico(VectorDinamico &v1){
		m_n = v1.m_n;
		m_p = v1.m_p;
		v1.m_p = nullptr;
	}
		
	void GenerarValores(VectorDinamico &w) {
		for(int i=0; i<w.m_n; ++i) {
			w.m_p[i] = rand()%90+10;
		}
	}
	
	void MostrarVector(VectorDinamico &w) {
		for(int i=0; i<w.m_n; ++i) {
			cout<<w.m_p[i]<<" ";
		}
	}
};

int main() {
	VectorDinamico v1(5);
	v1.GenerarValores(v1);
	cout<<"1er: "<<endl;
	v1.MostrarVector(v1);
	cout<<endl;
	
	VectorDinamico v2(v1);
	
	cout<<"2do: "<<endl;
	v2.MostrarVector(v2);
	cout<<endl<<"1ro(fue robado por 2do): "<<endl;
	v1.MostrarVector(v1);
	
	return 0;
}







