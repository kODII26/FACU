#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> v(5);
	v[0] = 3;
	v[1] = 2;
	v[2] = 1;
	v[3] = 5;
	v[4] = 4;
	cout<<"ORDEN ASCENDENTE: "<<endl;
	int aux,min;
	for(int i=0; i<5; ++i) {
		min = i;
		
		for(int j=i+1; j<5; ++j) {
			if( v[min] > v[j] ){
				min = j;
			}
		}
		
		aux = v[i];
		v[i] = v[min];
		v[min] = aux;
	}
	
	for(int i=0; i<5; ++i) {
		cout<<v[i]<<" ";
	}
	
	cout<<endl<<endl<<"ORDEN DESCENDIENTE: "<<endl;
	int may;
	for(int i=0; i<5; ++i) {
		may = i;
		
		for(int j=i+1; j<5; ++j) {
			if( v[may] < v[j] ){
				may = j;
			}
		}
		
		aux = v[i];
		v[i] = v[may];
		v[may] = aux;
	}
	for(size_t i=0; i<v.size(); ++i) {
		cout<<v[i]<<" ";
	}
	cout<<endl;
	
	return 0;
}

