#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
int busca_pos(vector<string> v, string nueva) {
	int pos=0;
	for (size_t i=0; i<v.size(); i++) {
		if (nueva>v[i]) {
			++pos;
		} 
	}
	return pos;
}
void inserta(vector<string> &v, string nueva, int pos) {
	v.resize(v.size()+1);
	for (size_t i=pos+1;i<v.size();i++){
		v[i+1] = v[i];
	}
//	for (int i=v.size()-1;i>pos;i--) {
//		v[i] = v[i-1];
//	}
	v[pos] = nueva;
}
int main() {
	int pos;
	vector<string> v(4);
	cout<<"ingrese las palabras"<<endl;
	for (size_t i=0;i< v.size();i++) {
		cin>>v[i];
	} 
	string nueva;
	cout<<"ingrese la nueva palabra"<<endl;
	cin>>nueva;
	pos = busca_pos(v, nueva);
	inserta(v,nueva,pos);
	for(size_t i=0; i<v.size();i++) {
		cout<<v[i]<<setw(4);
	}
	return 0;
}

