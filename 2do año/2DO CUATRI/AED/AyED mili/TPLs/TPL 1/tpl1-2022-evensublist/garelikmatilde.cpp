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

bool par(int x){
  if(x==0) return true;
  if(x%2==0) return true;
  return false;
}

void evensublist(list<int> &L,list<int> &subl) {
  list<int>::iterator it = L.begin();
  list<int> aux;
  while(it!=L.end()){
    if(par(*it)){
      aux.push_back(*it);
      if(it==--L.end()){
        if(aux.size()>subl.size()){
          subl = aux;
        }
      }
    }else{
      if(aux.size()>subl.size()){
        subl = aux;
      }
      aux.clear();
    }
    it++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0,seed=123;
  ev.eval<1>(evensublist,vrbs);
  ev.evalr<1>(evensublist,seed,vrbs);
  return 0;
}
