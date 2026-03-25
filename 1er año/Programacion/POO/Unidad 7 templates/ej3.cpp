#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
template<typename T>
class VectorDinamico {
	int m_n;
	T *m_p;
public:
	VectorDinamico(int n): m_n(n){
		m_p= new T[n];
		for (int i=0;i<n;++i){
			*(m_p+i)= rand()%101;
		}
	}
	int verElemento(int i){
		return *(m_p+i);
	}
	T operator[] (int i) const {
		return *(m_p+i);
	}
	T& operator[] (int i){
		return *(m_p+i);
	}
	~VectorDinamico(){
		delete[] m_p;
	}
};
int main() {
	VectorDinamico<int> q(10);
	for (int i=0;i<10;++i){
		cout<<q.verElemento(i)<<endl;
	}
	cout<<"-----------------"<<endl;
	cout<<q[2]<<endl; //Sobrecarga de [] para ver el elemento
	q[2]=100; //Sobrecarga de [] para modificar el elemento
	cout<<q[2]<<endl;
	return 0;
}

