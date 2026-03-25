#define USECHRONO
#undef HAVE_MPI

typedef int (*mapfun_t)(int);

int f1(int a) { return a%2; }
int f2(int a) { return a; }
int f3(int a) { return 2*a; }
int f4(int a) { return a*a; }

#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;

// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Matilde Garelik
int DNI=43426677;

bool es_primo(int x){
  for(int i=2; i<x; i++){
    if(x%i==0) return false;
  }
  if(x==0 || x==1) return false;
  return true;
}

int primer_primo(list<int>&L){
  for(int &x: L){
    if(es_primo(x)) return x;
  }
  return *(--L.end());
}

bool dist(int primo, int n1, int n2){
  int dist_n1 = primo-n1;
  if(dist_n1<0) dist_n1=-dist_n1;
  int dist_n2 = primo-n2;
  if(dist_n2<0) dist_n2=-dist_n2;
  return dist_n2>dist_n1;
}

void prime_distance(list<int> &L){
  int primo = primer_primo(L);
  if(L.empty()) return;
  /*list<int>::iterator it = L.begin();
  while(it!=L.end()){
    list<int>::iterator it2 = it;
    while(it2!=L.end()){
      if(dist(primo,*it,*it2)){
        swap(*it,*it2);
      }
      it2++;
    }
    it++;
  }*/
  // bubble sort
  for( list<int>::iterator it=L.begin(); it!=L.end(); it++ ) { 
    for( list<int>::iterator it2=prev(L.end()); it2!=it; it2-- ) { 
      if( dist(primo,*it2,*prev(it2)) ){
        int tmp = *prev(it2);
        *prev(it2) = *it2;
        *it2 = tmp;
      }
    }
  }
}


//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(prime_distance,vrbs);
  return 0;
}
