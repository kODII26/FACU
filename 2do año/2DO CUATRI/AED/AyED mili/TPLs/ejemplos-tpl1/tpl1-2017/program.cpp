#define USECHRONO
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include "eval.hpp"

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool esta_antes(list<int> &L,list<int>::iterator it1, list<int>::iterator it2){
  list<int>::iterator it_end = L.end();
  while(it1!=it_end && it2!=it_end){
    it1++;it2++;
  }
  if(it1==it_end) return false;
  return true;
}
void extract_range(list<int> &L1, list<int>::iterator p, 
                   list<int>::iterator q, list<int> &L2) 
{
  if(esta_antes(L1,p,q) && p!=L1.end()){
    while(p!=q){
      L2.push_back(*p);
      p=L1.erase(p);
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int contar_reps(list<int> L){
  int cont =0;
  list<int>::iterator it = L.begin();
  while(it!=--L.end()){
    if(*it==*next(it)){
      cont++;
      while(*it==*next(it) && next(it)!=L.end()){
          it++;
      }
    }else{
      it++;
    }
  }
  /*for(list<int>::iterator)*/
  return cont;
}
int add_elements(list<int>& L, stack<int> &S) {
  while(!S.empty()){
    int x = S.top(); S.pop();
    list<int>::iterator it = L.begin();
    while(it!=L.end() && *it<x){
      it++;
    }
    L.insert(it,x);
  }
  return contar_reps(L);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void divisors(int x, list<int> &divs){
  for(int i=2; i<=x ; i++){
    if(x%i==0) divs.push_back(i);
  }
}
bool coprimos(int x, int y){
  list<int> divs_x;
  divisors(x,divs_x);
  list<int> divs_y;
  divisors(y,divs_y);
  for(int &xi: divs_x){
    for(int &yi: divs_y){
      if(xi==yi) return false;
    }
  }
  return true;
}
bool coprimos(list<int>&L) {
  list<int>::iterator it = L.begin();
  while(it!=L.end()){
    list<int>::iterator it2 = L.begin();
    while(it2!=L.end()){
      if(it!=it2 && !coprimos(*it,*it2)) return false;
      it2++;
    }
    it++;
  }
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  //ev.eval<1>(extract_range,vrbs);
  //h1 = ev.evalr<1>(extract_range,seed,vrbs);
  
  //ev.eval<2>(add_elements,vrbs);
  //h2 = ev.evalr<2>(add_elements,seed,vrbs);
  
  
  ev.eval<3>(coprimos,vrbs);
  h3 = ev.evalr<3>(coprimos,seed,vrbs);

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);
  
  return 0;
}
