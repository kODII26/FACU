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
// Nombre: Da Silva Catela Justo 
int DNI=45507013;

int cubrimientos(list<set<int>> &L) {
  
  if (L.empty())return 1;
  
  //consigo el conjunto univ.
  set<int> U;
  auto itL = L.begin();
  while (itL != L.end()) {
    U.insert((*itL).begin(), (*itL).end()); 
    ++itL; 
  }
  
  
  //consigo el conj. pot.
  vector<set<int>>P={{}};
  
  vector<set<int>>V1(L.begin(),L.end());
  
  for (auto it = V1.begin(); it != V1.end(); ++it) {
    set<int> i = *it;
    vector<set<int>>V2;
    for (auto it = P.begin(); it != P.end(); ++it) {
      auto j = *it;
      set<int> auxS = j;
      auxS.insert(i.begin(),i.end());
      V2.push_back(auxS);
    }
    P.insert(P.end(),V2.begin(),V2.end());
  }
  int n=0;
  
  for (auto V2 : P){
    if (V2==U){
      n++;
    }
  }
  return n;
  
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(cubrimientos,vrbs);
  return 0;
}
