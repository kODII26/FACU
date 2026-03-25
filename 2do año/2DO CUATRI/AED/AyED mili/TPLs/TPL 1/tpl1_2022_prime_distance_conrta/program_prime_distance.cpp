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
// Nombre: Bob Esponja
int DNI=23456789;

bool es_primo (int n){
  int div = 1;
  int c = 0;
  while (div<=n){
    if (n % div == 0) c++;
    div++;
  }
  if (c==2) 
    return true;
  else
    return false;
}
  
int primer_primo(list<int> &L){
  
  list<int>::iterator it = L.begin();
  while(it!=L.end()){
    if (es_primo(*it)) return *it;
    it++;
  }
  return *prev(L.end());
  
}

void prime_distance(list<int> &L){

  list<int> L2;
  int v = primer_primo(L);;
  while(!L.empty()){
    list<int>::iterator it = L.begin();
    list<int>::iterator itMin = it;
    while(it!=L.end()){
      if(abs(*it-v)<abs(*itMin-v)){
        itMin = it;
      }
      it++;
    }
    L2.push_back(*itMin);
    L.erase(itMin);
  }
  L = L2;
}


//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(prime_distance,vrbs);
  return 0;
}
