#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Ficha {
	string nombre;
	int dni,edad,altura;
};

template<typename T>
class Reordenar {
	string m_nomArch;
	int m_pos1,m_pos2;
	fstream archi;
	vector<T> m_v;
	
public:
	Reordenar(string nom_arch,int pos1,int pos2) : archi(nom_arch,ios::trunc|ios::binary|ios::in|ios::out) {
		m_nomArch = nom_arch;
		m_pos1 = pos1;
		m_pos2 = pos2;
		
	}
	
	void OrdenarDeMenorAMayorPos1() {
		
		int min;
		T aux;
		for(int i=0;i<m_pos1;++i) {
			min = i;
			for(int j=i+1;j<m_pos1;++j) {
				if(m_v[min] > m_v[j]) {
					min = j;
				}
			}
			aux = m_v[i];
			m_v[i] = m_v[min];
			m_v[min] = aux;
		}
		
		for(size_t i=0; i<m_v.size(); ++i) {
			archi.seekp(sizeof(T)*i);
			archi.write(reinterpret_cast<char*>(&m_v[i]), sizeof(T));
			cout<<m_v[i]<<" ";
		}
		cout<<endl;
	}
	
	void OrdenarDeMayorAMenorPos2() {
		
		int max;
		T aux;
		for(int i=0;i<m_pos2;++i) {
			max = i;
			for(int j=i+1;j<m_pos2;++j) {
				if(m_v[max] < m_v[j]) {
					max = j;
				}
			}
			aux = m_v[i];
			m_v[i] = m_v[max];
			m_v[max] = aux;
		}
		
		for(size_t i=0; i<m_v.size(); ++i) {
			archi.seekp(sizeof(T)*i);
			archi.write(reinterpret_cast<char*>(&m_v[i]), sizeof(T));
			cout<<m_v[i]<<" ";
		}
		cout<<endl;
	}
	
	
	void CargarValores(){
		T val;Ficha a;
		if() {
			cout<<"Es FICHA"<<endl;
		}else{
			for(int i=0;i<5;++i) {
				T val;
				cout<<"Ingrese valor["<<i<<"]: ";cin>>val;
				archi.write(reinterpret_cast<char*>(&val),sizeof(T));
			}	
		}
	}
		
	void LeerArchivo() {
		T val;
		int i=0;
		archi.seekg(sizeof(T)*i);
		while(archi.read(reinterpret_cast<char*>(&val), sizeof(T))) {
			m_v.push_back(val);
			++i;
			archi.seekg(sizeof(T)*i);
			cout<<val<<" ";
		}
		cout<<endl;
	}
};

int main() {
	Reordenar<int> r("Archivo.poo",5,3);
	r.CargarValores();
	
	r.LeerArchivo();
	r.OrdenarDeMenorAMayorPos1();
	r.LeerArchivo();
	r.OrdenarDeMayorAMenorPos2();
	r.LeerArchivo();
	
	
	
	return 0;
}

