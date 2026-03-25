#include <iostream>
#include <vector>
using namespace std;
struct Alumno {
	string nombre;
	float nota;
};
class Curso {
	string m_nombre;
	vector<Alumno> m_v;
public: 
	Curso (string nombre) : m_nombre (nombre){}
	void agregarAl (Alumno a) {
		m_v.push_back(a);
	}
	float promCurso () {
		float prom=0;
		for (size_t i=0;i<m_v.size();i++) {
		prom += m_v[i].nota;
		}
	return prom/m_v.size();
	}
	Alumno getMayor (){
		Alumno may;
		may.nota = 1;
		for (size_t i=0;i<m_v.size() ;i++){
			if (m_v[i].nota > may.nota){
				may.nota = m_v[i].nota;
				may.nombre = m_v[i].nombre;
			}
		}
		return may;
	}
	
	~Curso (){};
};
	
int main() {
	cout<<"cant"<<endl;
	int n;
	cin>>n;
	Curso poo("POO");
	for (int i=0;i<n;i++){
		Alumno a;
		cout<<"nombre y nota"<<endl;
		cin>>a.nombre>>a.nota;
		poo.agregarAl(a);
	}
	cout<<endl<<"El promedio del curso es: "<<poo.promCurso()<<endl;
	Alumno may = poo.getMayor();
	cout<<"El alumno con mayor nota es: "<<may.nombre<<" con: "<<may.nota;
	
	return 0;
}

