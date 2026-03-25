#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {
	vector<string> v;
	ifstream archi("lista1.txt");
	int c=1;
	string x;
	while (archi>>x){
		v.push_back(x);
		c++;
	}

	cout<<"Se leyeron "<<c<<" palabras del archivo"<<endl;
	sort(v.begin(),v.end());
	archi.close();
	ofstream archi2("lista.txt",ios::trunc);
	for (size_t i=0;i<v.size();++i){
		archi2<<v[i]<<endl;
	}
	
	return 0;
}

