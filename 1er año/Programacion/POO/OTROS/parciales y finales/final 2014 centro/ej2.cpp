#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
	ifstream archi("parcial.txt");
	string x;
	vector<string> v;
	while (archi>>x){
		cout<<x<<endl;
		v.push_back(x);
	}

	for (size_t i=0;i<v.size();++i){
		auto it= remove(v.begin()+i+1,v.end(),v[i]);
		v.erase(it,v.end());
	}
	
	
	for (size_t i=0;i<v.size();++i){
		int pos=v[i].find("-");
		int pos2=v[i].find("-",pos+1);
		int p= pos2-pos;
		if (pos!=-1){
			v[i].erase(pos,p);
		}
	}
cout<<"---------------------"<<endl;
	sort(v.begin()+2,v.end());
	for (size_t i=0;i<v.size();++i){
		cout<<v[i]<<endl;
	}
	return 0;
}

