#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;
int min(btree<int>&T, btree<int>::iterator n) {
  if (n==T.end()) return INT_MAX;
  auto c=n;
  while (1) {
    c = n.left();
    if (c==T.end()) return *n;
    n=c;
  }
}

// Busca el maximo avanzando por hijo derecho
int max(btree<int>&T, btree<int>::iterator n) {
  // INT_MAX, INT_MIN estan definidos en `climits.h'
  if (n==T.end()) return INT_MIN;
  auto c=n;
  while (1) {
    c = n.right();
    if (c==T.end()) return *n;
    n=c;
  }
}

bool isBST3(btree<int>&T, btree<int>::iterator n){
  // Un arbol vacio es BST
  if (n==T.end()) return true;
  auto ql=n.left(), qr=n.right();
  // Chequea que los subarboles der e izq sean BST
  if (!isBST3(T,ql)) return false;
  if (!isBST3(T,qr)) return false;
  // Chequea la condicion en el nodo
  return max(T,ql)<*n && *n<min(T,qr);
}
  
bool isBST3(btree<int>&T){ 
  return isBST3(T,T.begin()); 
}
  
void fillBST(btree<int>&T,list<int>&L){
  btree<int>::iterator n = T.begin();
  if(L.empty()) return;
  
  n = T.insert(n,*L.begin());
  L.erase(L.begin());
  while(!L.empty()){
    while(n != T.end()){
      if(*n>*L.begin())
        n = n.left();
      else if(*n<*L.begin())
        n = n.right();
      else {
        if(L.size() != 1)
          n = T.begin();
        else n = T.end();
        L.erase(L.begin());
      }
    }
    if(L.size()>=1 && n !=T.begin()){
      n = T.insert(n,*L.begin());
      L.erase(L.begin());
      n = T.begin();
    }
  }
}


bool eqsumsplit(set<int> &S) {
  // COMPLETAR...
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {
    ev.eval<1>(isBST3,vrbs);
    h1 = ev.evalr<1>(isBST3,seed,vrbs);
    
    ev.eval<2>(fillBST,vrbs);
    h2 = ev.evalr<2>(fillBST,seed,vrbs);
    
    /*ev.eval<3>(eqsumsplit,vrbs);
    h3 = ev.evalr<3>(eqsumsplit,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");*/
  } while (cin>>seed);
  
  return 0;
}
