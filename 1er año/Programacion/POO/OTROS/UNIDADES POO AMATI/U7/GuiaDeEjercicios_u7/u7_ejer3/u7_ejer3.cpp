#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

template<typename T>
class VectorDinamico {
	T *m_p;
	int m_n;
public:
	VectorDinamico(int n) {
		m_p = new T[n];
		m_n = n;
		
		for(int i=0; i<m_n; ++i) {
			m_p[i] = rand();
		}
	}
	
	T operator[] ( int i ) const {
		return m_p[i];
	}
	
	
	T& operator[] ( int i ) {
		return m_p[i];
	}
	
	void Ver(){
		for(int i=0; i<m_n; ++i) {
			cout<<m_p[i]<<"  ";
		}
	}
	
	~VectorDinamico(){
		delete [] m_p;
	}
};

int main() {
	srand(time(NULL));//permite que halla string dentro de rand().
	VectorDinamico<string> v(3);
	v.Ver();
	cout<<endl;
	v.Ver();
	return 0;
}

