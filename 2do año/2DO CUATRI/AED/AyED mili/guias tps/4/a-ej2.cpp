#include <iostream>
#include <set>
#include <vector>
using namespace std;

// ejercicio 2
bool es_disjunto(set<int> A, set<int> B){
	for(auto it = A.begin(); it!=A.end();it++){
		if(B.find(*it)!=B.end()) return false;
	}
	return true;
}
bool disjuntos(vector<set<int>> &v){
	for(size_t i=0; i<v.size(); i++){
		for(size_t j=i+1; j<v.size(); j++){
			if(!es_disjunto(v[i],v[j])) return false;
		}
	}
	return true;
}

int main() {
	set<int> A = {1,2,3,4};
	set<int> B = {3,4,5,6};
	set<int> C;
	vector<set<int>> v;
	v.push_back(A); v.push_back(B);
	
	cout<<disjuntos(v);
	
	return 0;
}







