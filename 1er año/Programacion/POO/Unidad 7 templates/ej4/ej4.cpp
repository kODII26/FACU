#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
template<typename T>
class ManejadorArchivo {
	fstream archi;
	vector<T> m_v;
	int m_cant;
public:
	ManejadorArchivo (string nombre) : archi(nombre,ios::binary|ios::in|ios::out) {
		archi.seekg(0,ios::end);
		int cant= archi.tellg()/sizeof(T);
		m_cant=cant;
		archi.seekg(0);
		for (int i=0;i<m_cant;++i) {
			T f;
			archi.read(reinterpret_cast<char*> (&f),sizeof(T));
			m_v.push_back(f);
		}
	}
	int Cant(){return m_cant;}

	T verElemento (int i){
		return m_v[i];
	}
	void modElemento (int i, T f){
		m_v[i] = f;
	}
	void saveArchivo (){
		archi.seekg(0);
		for (int i=0;i<m_cant;++i){
			archi.write(reinterpret_cast<char*>(&m_v[i]),sizeof(T));
		}
	}
	
};
int main() {
	ManejadorArchivo<int> q("TablaPuntuaciones.poo");
	cout<<"Hay: "<<q.Cant()<<" enteros"<<endl;
	for (int i=0;i<q.Cant();++i){
		cout<<q.verElemento(i)<<endl;
	}
	q.modElemento(2,900);
	cout<<"------------------------"<<endl;
	for (int i=0;i<q.Cant();++i){
		cout<<q.verElemento(i)<<endl;
	}
	q.saveArchivo();
	cout<<"------------------------"<<endl;
	for (int i=0;i<q.Cant();++i){
		cout<<q.verElemento(i)<<endl;
	}
	return 0;
}

