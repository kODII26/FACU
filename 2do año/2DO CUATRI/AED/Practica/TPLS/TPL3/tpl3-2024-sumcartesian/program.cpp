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

// Funcion principal que calcula la sumatoria del producto cartesiano
int sumcartesian(set<int> &A, set<int> &B) {
  int suma=0;
  for (int i:A){
    for(int j:B){
      suma = suma+abs(i-j);
    }
  }
  return suma;
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(sumcartesian,vrbs);
  return 0;
}
