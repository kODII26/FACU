#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Par {
	int *rep1 = nullptr;
	int *rep2 = nullptr;
};

vector<Par> EncontrarReps(vector<int> &v) {
	vector<Par> r;
	size_t pos=0;
	
	while( pos<v.size() ){
		for(size_t i=pos+1;i<v.size();++i){
			if(v[pos]==v[i]){
				Par p;
				p.rep1 = &v[pos];
				p.rep2 = &v[i];
				r.push_back(p);
			}
		}
		++pos;
	}
	
	return r;
}

int main() {
	vector<int> v(10);
	for(size_t i=0; i<v.size(); ++i) {
		v[i] = rand()%10;
		cout<<v[i]<<" ";
	}
	cout<<endl;
	
	vector<Par> r  = EncontrarReps(v);
	
	cout<<"Repetidos: "<<endl;
	for(size_t i=0; i<r.size(); ++i) {
		cout<<"Rep1: "<<r[i].rep1<<"["<<*r[i].rep1<<"]"<<endl;
		cout<<"Rep2: "<<r[i].rep2<<"["<<*r[i].rep2<<"]"<<endl;
	}
	
	cout<<endl<<"ARREGLO SIN REPETIDOS: "<<endl;
	size_t pos = 0;
	while( pos<v.size() ) {
		for(size_t j=pos+1; j<v.size(); ++j) {
			if(v[pos]==v[j]) {
				v[j] = v[v.size()-1];
				v.resize(v.size()-1);
			}
		}
		++pos;
	}
	
	pos = 0;
	while( pos<v.size() ) {
		for(size_t j=pos+1; j<v.size(); ++j) {
			if(v[pos]==v[j]) {
				v[j] = v[v.size()-1];
				v.resize(v.size()-1);
			}
		}
		++pos;
	}
	
	
	for(size_t i=0; i<v.size(); ++i) {
		cout<<v[i]<<" ";
	}
	
	return 0;
}
