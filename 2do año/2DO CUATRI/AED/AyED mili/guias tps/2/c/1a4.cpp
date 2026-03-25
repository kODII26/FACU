#include <iostream>
using namespace std;

void show_map(map<int,int> &M){
	map<int,int>::iterator it = M.begin();
	cout<<"[ ";
	while(it!=M.end()){
		cout<<it->first<<"->";
		cout<<it->second<<" ";
		it++;
	}
	cout<<" ]"<<endl;
}
	
// EJERCICIO 1
void map2list(map<int,int> &M, list<nt> &Keys, list<int> &Vals){
	map<int,int>::iterator it = M.begin();
	while(it!=M.end()){
		Keys.push_back(it->first);
		Vals.push_back(it->second);
		it++;
	}
}
	
// EJERCICIO 2
void list2map(map<int, int> &M, list<int> &Keys, list<int> &Vals){	auto it_v = Vals.begin();	for( list<int>::iterator it_k = Keys.begin(); it_k!=Keys.end(); ++it_k ) { 		if(it_v != Vals.end()) {			M[*it_k] = *it_v;			it_v++;		} else M[*it_k] = 0;	}}
	
// EJERCICIO 3
bool areinverse(map<int,int> &M1, map<int,int> &M2){
	if(M1.size()!=M2.size())
		return false;
	auto it = M1.begin();
	while(it!=M1.end()){
		if(M2[it->second] != it->first){
			return false;
		}
		it++;
	}
	return true;
}
	
// EJERCICIO 4
void merge_map(map<int, list<int>> &A, map<int, list<int>> &B,
			   map<int, list<int>> &C){
	list<int> tmp;		auto it_a = A.begin();	while (it_a != A.end()) {		if (B.find(it_a->first) != B.end()) {			merge(it_a->second, B[it_a->first], tmp);			C[it_a->first] = tmp;		}		else {			C[it_a->first] = it_a->second;		}		it_a++;	}		auto it_b = B.begin();	while (it_b != B.end()) {		if (C.find(it_b->first) == C.end())			C[it_b->first] = it_b->second;		it_b++;	}
	
}
	

int main(int argc, char *argv[]) {
	
	return 0;
}

