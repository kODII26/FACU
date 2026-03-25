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

void mkmono(tree<int> &T,tree<int>::iterator n,int &last){
  if (n==T.end()) return;
  
  auto h= n.lchild(); 
  
  if (*n>last){
    last=*n;
  } else {
    *n=last+1;
    last=*n;
  }
  
  while (h!=T.end()){ 
    mkmono(T,h,last);	
    h=h.right();
  }
}

void mkmono(tree<int> &T) {
  auto n=T.begin();
  int last=-1;
  mkmono(T,n,last);
}


//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(mkmono,vrbs);
  return 0;
}
