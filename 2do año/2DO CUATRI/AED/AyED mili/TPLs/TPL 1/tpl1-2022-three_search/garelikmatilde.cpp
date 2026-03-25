#define USECHRONO
#undef HAVE_MPI
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

bool div_3(int x){
  if(x%3==0) return true;
  return false;
}

void ordenar_lista(list<int> &L){// de mayor a menor
  list<int>::iterator it= L.begin();
  while(it!=L.end()){
    swap(*it,*max_element(it,L.end()));
    it++;
  }
}
  
void three_search(list<int> &L,stack<int> &P){
 ordenar_lista(L);
 list<int>::iterator it= L.begin();
 while(it!=L.end()){
   if(div_3(*it)) P.push(*it);
   it++;
 }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  ev.eval<1>(three_search,vrbs);

  return 0;
}
