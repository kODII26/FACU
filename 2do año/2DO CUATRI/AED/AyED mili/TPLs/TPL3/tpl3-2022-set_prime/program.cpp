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

bool es_primo(int n){
  bool primo = true;
  if (n==0 || n==1) return false;

  for (int i = 2; i <= n / 2; ++i) {
    if (n % i == 0) return false;
  }
  
  return true;
}

bool has_prime(set<int> &S){
  for(int x: S){
    if(es_primo(x)) return true;
  }
  return false;
}
  
void set_prime(vector<set<int>> &VS, set<int> &S)
{
  S.clear();
  for(set<int> x: VS){
    if(has_prime(x)) S.insert(x.begin(),x.end());
  }
}


//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(set_prime,vrbs);
  return 0;
}
