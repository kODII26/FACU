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
// Nombre: Bob Esponja
int DNI=98765432;
/*
  bool es_primo (int n){
    int div =1;
    int c=0;
    
    while (div<=n){
      if (n % div ==0) c++;
      div++;
    }
    
    if (c==2){
        return true;
  } else{
      return false;
    }
  }
  */
  bool es_primo (int x){
    for (int i=2;i<x;i++){
      if(x%i==0) return false;
    }
    return true;
  }
void set_prime(vector<set<int>> &VS, set<int> &S)
{
  //COMPLETAR
  for(size_t i=0;i<VS.size();i++) {     auto it = VS[i].begin();    while(it!=VS[i].end()){      if(es_primo(*it)){        S.insert(VS[i].begin(),VS[i].end());        break;      }      it++;    }
  }
}


//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(set_prime,vrbs);
  return 0;
}
