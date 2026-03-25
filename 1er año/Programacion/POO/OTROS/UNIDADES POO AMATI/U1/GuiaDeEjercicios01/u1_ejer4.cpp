#include <iostream>
#include <vector>
using namespace std;

int *buscar(vector<int> &v,int N,int num) {
	for(int i=0;i<N;++i) {
		if(v[i] == num) {
			return &v[i];
		}
	}
	
	return nullptr;
}

int main() {
	vector<int> v(10);
	for(size_t i=0;i<v.size();++i) {
		v[i] = rand()%11;
		cout<<v[i]<<" ";
	}
	
	int x;
	cout<<endl<<"ingrese num a busacar: ";cin>>x;
	
	int *b = buscar(v,10,x);
	
	if ( b == nullptr ) {
		cout<<"El numero "<<x<<" no existe en el arreglo"<<endl;
	}else {
		cout<<"El numero "<<x<<" existe en la dirección: "<<b<<endl;
	}
	return 0;
}

