#include <iostream>
#include <map>
#include <list>
#include <iomanip>
using namespace std;

void showl(list<int> &L){
	for(int &x: L) cout<<x<<", ";
	cout<<endl;
}

void show_map(map<int, list<int>> &M){
	cout<<"M={";
	for(typename map<int,list<int>>::iterator it =M.begin(); it!=M.end(); it++){
		cout<<"["<<(*it).first<<"->";
		showl((*it).second);
		cout<<"],";
	}
	cout<<"]"<<endl;
}

// EJERCICIO 5
void cutoffmap(map<int, list<int>> &M, int p, int q){
	map<int, list<int>>::iterator it = M.begin();
	while(it!= M.end()){
		if((*it).first<p || (*it).first>=q){
			it = M.erase(it);
			continue;
		}else{
			list<int>::iterator it_aux = (*it).second.begin();
			while(it_aux!=(*it).second.end()){
				if(*it_aux<p || *it_aux>=q){
					it_aux = (*it).second.erase(it_aux);
				}
				it_aux++;
			}
			if((*it).second.empty()){
				it = M.erase(it);
				continue;
			}
		}
		it++;
	}
}
	
// EJERCICIO 6
void apply_map2(list<int> &L, map<int,int> &M,list<int> &ML){	while(L.size()){		if(M.find(*L.begin())  != M.end() ){			ML.push_back(M[*L.begin()]);		}		L.erase(L.begin());	}}

// EJERCICIO 7
bool es_camino(map<int,list<int>> G, list<int> L){
	list<int>::iterator it = L.begin();
	while(it!=prev(L.end())){
		list<int> aux = G[*it];
		it++;
		bool sigue= false;
		list<int>::iterator it_aux = aux.begin();
		while(it_aux!=aux.end()){
			if(*it_aux==*it) sigue=true;
			it_aux++;
		}
		if(!sigue) return false;
	}
	return true;
}

int main(int argc, char *argv[]) {
	map<int, list<int>> M={{1,{2,5,4}},{5,{6,7,8}},{8,{4,5,1}},{3,{1,3}}};
	//show_map(M);
	//cutoffmap(M,1,6);
	//show_map(M);
	cout<<es_camino(M,{1,5,8,1});
	return 0;
}

