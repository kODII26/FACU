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

void stack2queue(stack<int> &S, queue<int> &Q,
                    bool (*pred)(int)) {
  std::vector<int> v1;   //vector de los q cumplen  
  std::vector<int> v2;  // los q no cumplen
  
  while (!S.empty()) {
    int aux = S.top();
    S.pop();
    
    if (pred(aux)) {
      v1.push_back(aux); 
    } else {
      v2.push_back(aux); 
    }
  }
  std::reverse(v2.begin(), v2.end());
  
  for (int i=0;i<v1.size();++i) {
    Q.push(v1[i]);
  }
  for (int i=0;i<v2.size();++i) {
    Q.push(v2[i]);
  }
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(stack2queue,vrbs);
  return 0;
}
