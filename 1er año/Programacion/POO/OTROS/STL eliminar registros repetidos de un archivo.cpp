#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
template<typename T>
int eliminarReps (string nom_archi){
	ifstream archi(nom_archi,ios::binary|ios::ate);
	vector<T> v;
	int n=archi.tellg()/sizeof(T);
	archi.seekg(0);
	for (int i=0;i<n;++i){
		T x;
		archi.read(reinterpret_cast<char*>(&x),sizeof(T));
		v.push_back(x);
	}
	
//	//El unique necesita del sort y el sort desordena todo el vector.
//	sort(v.begin(),v.end());
//	auto it= unique(v.begin(),v.end()); 
//	//unique deja los valores no repetidos al principio del vector y los repetidos en el final,
//	// devuelve un iterador apuntando al primer elemento a borrar
//	int cant_elim = v.end()-it;//distance(it,v.end());
//	v.erase(it,v.end()); //borras desde dicho iterador hasta el final del vector 
//	
	//forma de borrar elem. repetidos sin desordenador el vector 
	int cant_elim=0;
	for (size_t i=0;i<v.size();++i){
		auto it2= remove(v.begin()+i+1,v.end(),v[i]);
			//Si esta parado sobre un 3, busca el proximo 3 hasta el final del vector y lo "borra"
		cant_elim+= v.end()-it2;
		v.erase(it2,v.end());
	}

	
	
	ofstream archi2(nom_archi,ios::binary|ios::trunc);
	for (T &x:v){
		archi2.write(reinterpret_cast<char*>(&x),sizeof(T));
	}
	return cant_elim;
}

int main() {
	cout<<"nombre arch"<<endl;
	string a; cin>>a;
	cout<<eliminarReps<int>(a);
	return 0;
}

