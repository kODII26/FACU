#include <iostream>
#include <iomanip>
#include <list>
#include <algorithm>
using namespace std;

void ascendente1(list<int> &L, list<list<int>> &LL){
	if(L.empty()) return;
	list<int> sublista;
	list<int>::iterator it= L.begin();
	list<int>::iterator it2= next(it);
	
	while(it!=L.end()){
		sublista.push_back(*it);
		if(*it > *it2){
			LL.push_back(sublista);
			sublista.clear();
		}
		
		it++;it2++;
		if(it == prev(L.end())){
			sublista.push_back(*it);
			LL.push_back(sublista);
		}
	}
}

void showl(list<int> &L){
	for(int &x: L) cout<<x<<", ";
	cout<<endl;
}
	
void showll(vector<list<int>> &VL,const char *label=NULL) {	for (auto x : VL) showl(x,label);	}void ascendente2(list<int> &L, vector<list<int>> &VL){	if(L.empty()) return;	auto it = L.begin();	list<int> lAux;	while(it!=L.end()){		lAux.push_back(*it);		if(!(next(it) != L.end() && *it <= *next(it))){			VL.push_back(lAux);			lAux.clear();		}		it++;	}	}
	

	
int main(int argc, char *argv[]) {
	list<int> L1 = {1,2,3,4,5,23,4,4,3,34,3,32,2,2,2,9};
	showl(L1);
	list<list<int>> LL;
	ascendente1(L1,LL);
	for(list<int> &aux: LL) showl(aux);
	return 0;
}

