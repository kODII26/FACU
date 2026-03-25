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
// Nombre: Matilde Garelik
int DNI=43426677;

void fillbalance(btree<int> &B,list<int> L, btree<int>::iterator it) {
  if(L.size()==0) return;
  if(L.size()==1){
    it = B.insert(it,*L.begin());
    return;
  }
  
  int n = L.size();
  int nleft = n/2;
  int nright=n-1-nleft;
  
  list<int> Lleft, Lright;
  int cont=0;
  
  list<int>::iterator aux = L.begin();
  while(cont<nleft && aux!=L.end()){
    Lleft.push_back(*aux);
    aux++; cont++;
  }
  it = B.insert(it,*aux); aux++;
  cont =0;
  while(cont<nright && aux!=L.end()){
    Lright.push_back(*aux);
    aux++;cont++;
  }
  
  fillbalance(B, Lleft,it.left());
  fillbalance(B, Lright,it.right());
}

void fillbalance(btree<int> &B,list<int> &L) {
  fillbalance(B,L,B.begin());
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(fillbalance,vrbs);
  
  return 0;
}
