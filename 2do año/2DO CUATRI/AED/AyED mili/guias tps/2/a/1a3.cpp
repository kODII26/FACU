#include <iostream>
using namespace std;

void basic_sort(list<int> &L){
	list<int> L2;
	while(!L.empty()){
		list<int>::iterator it = min_element(L.begin(), L.end());
		L2.push_back(*it);
		it = L.erase(it);
	}
	L=L2;
}
	
void selection_sort(list<int> &L){
	list<int>::iterator it = L.begin();
	while(it!=L.end()){
		list<int>::iterator min = min_element(it, L.end());
		swap(*it,*min);
		it++;
	}
}
	
void concatena_a(list<int> &L1, list<int> &L2, list<int> &L){
	for(auto x: L1) L.insert(L.end(),x);
	for(auto x: L2) L.insert(L.end(),x);
}

int main(int argc, char *argv[]) {
	
	return 0;
}

