#define USECHRONO
#undef HAVE_MPI

#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;

//---:---<*>---:---<*>- COMIENZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Da Silva Catela, Justo.
int DNI=45507013;

void neg2pos(list<int>& L, map<int,list<int>>& M){
  // COMPLETAR AQUI...
  int pos;
  for (auto it=L.begin();it!=L.end();++it){
    if (*it<0){
      list<int> aux;
      pos=*it;
      for (auto it2=next(it);it2!=L.end() and *it2>=0;++it2){
        aux.push_back(*it2);
      }
      
      if (M.find(pos) != M.end()) {
        M[pos].insert(M[pos].end(), aux.begin(), aux.end());
      } else {
        M[pos] = aux;
      }
      
      
      it = next(it, aux.size());
    } 
  }
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(neg2pos,vrbs);
  return 0;
}
