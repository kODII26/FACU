#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

bool puede_simplificar(btree<string> &T, string fc) {
  // COMPLETAR...
  return false;
}

void gather_sets(vector<set<int>> &VS,
                 bool (*pred)(int),set<int> &S) {
  S.clear();
  for(auto ss: VS){
    set<int>::iterator it = ss.begin();
    while(it!=ss.end()){
      if(pred(*it)){
        S.insert(ss.begin(),ss.end());
        break;
      }
      it++;
    }
  }
}

void preorden(btree<int> &T, list<int> &L, btree<int>::iterator nodo){
  if(nodo==T.end()) return;
  L.push_back(*nodo);
  preorden(T, L,nodo.left());
  preorden(T,L,nodo.right());
}
void prune_and_return(btree<int>&T, int v, list<int>& L) {
  // encontrar iterador de etiqueta v
  btree<int>::iterator pos = T.find(v);
  if(pos!=T.end()){
    preorden(T,L,pos);
    T.erase(pos);
  }
  // listar en L subarbol
  // Eliminar subarbol
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;
  
  cout << "seed: 123" << endl;
  do {
    /*ev.eval<1>(puede_simplificar,vrbs);
    h1 = ev.evalr<1>(puede_simplificar,seed,vrbs);*/
    
    ev.eval<2>(prune_and_return,vrbs);
    h2 = ev.evalr<2>(prune_and_return,seed,vrbs);

    ev.eval<3>(gather_sets,vrbs);
    h3 = ev.evalr<3>(gather_sets,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed (ctrl+d para terminar): ";
  } while (cin>>seed);
  return 0;
  
}
