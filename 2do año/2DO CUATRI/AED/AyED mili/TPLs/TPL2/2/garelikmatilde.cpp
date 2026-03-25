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

void findmaxdepth(tree<int> &T,tree<int>::iterator n, 
                           bool (*pred)(int),int curr_depth,pair<int,int>&par){
  if(n==T.end()) return;
  if(pred(*n) && curr_depth>par.second){
    par.first=*n; par.second=curr_depth;
  }
  auto c = n.lchild();
  curr_depth++;
  while(c!=T.end()){
    findmaxdepth(T,c,pred,curr_depth,par);
    c++;
  }
  curr_depth--;
}

pair<int,int> findmaxdepth(tree<int> &T,bool (*pred)(int)) {
  pair<int,int> par={0,-1};
  findmaxdepth(T, T.begin(),pred,0,par);
  return par;
}

//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(findmaxdepth,vrbs);
  return 0;
}
