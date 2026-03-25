#define USECHRONO
#undef HAVE_MPI

#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;

bool even(int x) { return x%2==0; }
bool odd(int x) { return x%2; }
bool ge7(int x) { return x>=7; }
bool le3(int x) { return x<=3; }
bool div4(int x) { return x%4==0; }
bool isprime(int x) { return is_prime(abs(x)); }
bool isnotprime(int x) { return !is_prime(abs(x)); }

//---:---<*>---:---<*>- COMIENZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Bob Esponja
int DNI=98765432;

void fillbalance(btree<int> &B,btree<int>::iterator n,list<int> &L) {
  // COMPLETAR AQUI...
  int m= L.size();
  
  if (m==0){    return;  }  if (m==1){    B.insert(n, *L.begin());    return;  }    int l=m/2;  list<int> Ll;    for (int j=0; j<l; j++) {    Ll.push_back(L.front());    L.pop_front();  }  int root = L.front();  L.pop_front();    n = B.insert(n, root);    fillbalance(B, n.left(),Ll);  fillbalance(B, n.right(),L);  }void fillbalance(btree<int> &B,list<int> &L) {  fillbalance(B,B.begin(),L);
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(fillbalance,vrbs);
  
  return 0;
}
