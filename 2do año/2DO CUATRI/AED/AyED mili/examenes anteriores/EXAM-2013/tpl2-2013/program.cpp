#include <cstdio>

#include "Evaluar.hpp"
#include "./tree.h"
// #include "./util_tree.h"
// #include "./util.h"

//--------------------------------------------------------------------
void odd2even(list<int> &L,map<int,list<int> > &M) {
	list<int>::iterator it =L.begin();
	while(it!=L.end()){
		if((*it)%2!=0){
			int x = *it;
			M[x]; it++;
			while(it!=L.end() && (*it)%2==0){
				M[x].push_back(*it);
				it++;
			}
		}else{
			it++;
		}
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool pertenece(int n, list<int> L){
	for(auto &x: L){
		if(x==n) return true;
	}
	return false;
}
typedef map<int,list<int>> graph_t;
bool is_shift(graph_t &G1,graph_t &G2,int m) {
  if(G1.size()!=G2.size()) return false;
  graph_t::iterator it = G1.begin();
  while(it!=G1.end()){
	  if(G1[it->first].size()!=G2[it->first].size()) return false;
	  for(int &x: G1[it->first]){
		if(!pertenece(x+m,G2[it->first])) return false;
	  }
	  it++;
  }
  return true;
}


using namespace aed;
int main() {
  Evaluar ev;
  /*ev.evaluar1(count_level);*/
  ev.evaluar2(is_shift);
  ev.evaluar3(odd2even);
  return 0;
}
