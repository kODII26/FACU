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
  
void reemplaza_promedio(tree<int> &T, map<int,int> &M, tree<int>::iterator p, int prom){
  if(p==T.end()) return;
  if(M.find(*p)!=M.end()){
    *p=M[*p];
  }else{
    *p=prom;
  }
  tree<int>::iterator c = p.lchild();
  while(c!=T.end()){
    reemplaza_promedio(T,M,c,prom);
    c++;
  }
}

void reemplaza_promedio(tree<int> &T, map<int,int> &M) {
  map<int,int>::iterator it = M.begin();
  int sum=0;
  while(it!=M.end()){
    sum+=M[it->first];
    it++;
  }
  int prom = sum/M.size();
  reemplaza_promedio(T,M,T.begin(),prom);
}
  
    
//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(reemplaza_promedio,vrbs);
  
  
  return 0;
}
