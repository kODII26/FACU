#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
struct Alumno {
	int dni, nota1,nota2,nota3;
	char nombre[50],apellido[50];

	
};
bool operator== (const Alumno &a, const Alumno &b){
	if (a.dni==b.dni)
		return true;
	else return false;
}

class Curso {
	fstream archi;
	vector<Alumno> m_v;
	int m_n;
public:
	Curso (string nombre_arch): archi(nombre_arch,ios::binary|ios::in|ios::out) {
		archi.seekg(0,ios::end);
		int m_n= archi.tellg()/sizeof(Alumno);
		archi.seekg(0);
		for (int i=0;i<m_n;++i){
			Alumno x;
			archi.read(reinterpret_cast<char*> (&x),sizeof(Alumno));
			m_v.push_back(x);
		}
	}

	
public:
	void eliminarReps () {
		for (size_t i=0;i<m_v.size();++i){
			auto it=remove(m_v.begin()+i+1,m_v.end(),m_v[i]);
			m_v.erase(it,m_v.end());
		}
	}
	int getProm (int i){
		int prom=(m_v[i].nota1+m_v[i].nota2+m_v[i].nota3)/3;
		return prom;
	}
	int getProm () {
		int promgen=0;
		for (size_t i=0;i<m_v.size();++i){
			promgen+=m_v[i].nota1+m_v[i].nota2+m_v[i].nota3;
		}
		return promgen/m_v.size();
	}
};

int main() {
	

	return 0;
}

