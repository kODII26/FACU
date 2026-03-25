#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int rand10() { return rand()%21-10; }

bool es_par(int x) { return ( x%2 == 0 ); }

bool menor_abs(int a,int b){
	if( abs(a)<abs(b) )
		return true;
	return false;
}

int main() {
	vector<int> v(20);
	
	for(size_t i=0; i<v.size(); ++i) {
		v[i] = rand10();
		cout<<v[i]<<" ";
	}
	
	int cant = count_if(v.begin(),v.end(),es_par);
	cout<<endl<<"Cant de pares: "<<cant<<endl;
	
	cout<<"VECTOR ORDENADO(segun abs()): "<<endl;
	sort(v.begin(),v.end(),menor_abs);
	
	for(size_t i=0; i<v.size(); ++i) {
		cout<<v[i]<<" ";
	}
	
	cout<<endl<<"VECTOR MODIFICADO(sin reps): "<<endl;
	sort(v.begin(),v.end());
	auto it_elim = unique(v.begin(),v.end());
	v.erase(it_elim,v.end());
	
	for(auto it=v.begin(); it!=v.end(); ++it) {
		cout<<*it<<" ";
	}
	return 0;
}

