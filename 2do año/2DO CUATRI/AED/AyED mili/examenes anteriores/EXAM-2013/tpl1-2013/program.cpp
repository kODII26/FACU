#include "Evaluar.hpp"

void split_mod(list<int>&L, int m, vector< list<int> >&VL) {
  for(int i=0;i<m;i++){
	  list<int> aux;
	  for(int &x: L){
		  if(x%m == i) aux.push_back(x);
	  }
	  VL.push_back(aux);
  }
}

bool is_sublist(list<int>&L1, list<int>&L2) {
	list<int>::iterator it1 = L1.begin();
	list<int>::iterator it2 = L2.begin();
  while(it1!=L1.end()){
	  if(*it1==*it2){
		  it2++;
	  }
	  it1++;
	  if(it2==L2.end()) return true;
  }
  return false;
}

void max_sublist(list<int>&L, list<int>&subl) {
  // LLENAR AQUI...
}

int main() {
  aed::Evaluar ev;
  ev.evaluar1(split_mod);
  ev.evaluar2(is_sublist);
  ev.evaluar3(max_sublist);
  return 0;
}
