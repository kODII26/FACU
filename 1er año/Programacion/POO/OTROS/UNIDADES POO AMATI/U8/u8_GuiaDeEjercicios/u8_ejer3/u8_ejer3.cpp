#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main() {
	vector<float> v(5);
	for(size_t i=0;i<v.size();++i) {
		cout<<"Ingrese elemento["<<i<<"]: ";cin>>v[i];
	}
	
	for(auto it=next(v.begin());it!=v.end();advance(it,2)) {
		float prom = (*prev(it)+*it)/2;
		it = v.insert(it,prom);
	}
	
	ofstream arch("listafloat.txt",ios::binary|ios::trunc);
	for(size_t i=0;i<v.size(); ++i) {
		arch.write(reinterpret_cast<char*>(&v[i]), sizeof(v[i]));
	}
	arch.close();
	
	
	//verifico...
	ifstream archi("listafloat.txt",ios::binary);
	for(size_t i=0;i<v.size(); ++i) {
		float x;
		archi.read(reinterpret_cast<char*>(&x), sizeof(x));
		cout<<x<<" ";
	}
	archi.close();
	return 0;
}
