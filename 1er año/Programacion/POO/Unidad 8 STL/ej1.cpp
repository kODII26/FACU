#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main() {
	vector<int> v(15);
	for (auto it=v.begin();it!=v.end();++it){
		*it=rand()%101;
	}
	for (auto it=v.begin();it!=v.end();++it){
		cout<<*it<<endl;
	}
	int max=0,min=100;
	for (int &x: v){
		if (x>max)
			max=x;
	}
	cout<<"max:"<<" "<<max<<endl;
	for (int &x: v){
		if (x<min)
			min=x;
	}
	cout<<"min:"<<" "<<min<<endl;
	int c=0;
	for (int &x: v){
		c+=x;
	}
	cout<<"suma total: "<<c<<endl;
	cout<<"prom: "<<c/15<<endl;
	cout<<"ingrese valor para chequear si esta en el vector"<<endl;
	int opc;cin>>opc;
	for (int i=0;i<15;++i){
		if (v[i]==opc){
			cout<<"el valor ingresado se encuentra en el vector en la pos: "<<++i<<endl;
			break;
		}
	}
	return 0;
}

