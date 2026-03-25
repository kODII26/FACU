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
// Nombre: Matilde Garelik
int DNI=43426677;

void tree2pmap(tree<int> &T, map<int,int> &M, tree<int>::iterator p){
  if(p==T.end()) return;
  if(*p%2==0){
    int cantHijos =0;
    tree<int>::iterator it = p.lchild();
    while(it!=T.end()){
      it++;cantHijos++;
    }
    M[*p] = cantHijos;
  }
  auto c = p.lchild();
  while(c!=T.end()){
    tree2pmap(T,M,c);
    c++;
  }
  
  
}

void tree2pmap(tree<int> &T, map<int,int> &M){
  tree2pmap(T,M,T.begin());
  return;
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(tree2pmap,vrbs);
  
  
  return 0;
}
