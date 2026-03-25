#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

void fill_ordprev(tree<int> &T,list<int> &L, tree<int>::iterator itT, list<int>::iterator& itL) {
  *itT = *itL; itL++;
  auto hijo = itT.lchild();
  while(hijo!=T.end() && itL!=L.end()){
    fill_ordprev(T, L,hijo++,itL);
  }
}

void fill_ordprev(tree<int> &T,list<int> &L) {
  auto itT = T.begin(); auto itL = L.begin();
  fill_ordprev(T, L, itT,itL);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

void a_lo_ancho(graph& G, tree<char>& T){
  typedef tree<char>::iterator node;
  map<char,bool> visitados;
  list<char> nextLayer;
  list<char> currLayer;
  list<node> nextLayerTree;
  list<node> currLayerTree;
  
  currLayer.push_back(G.begin()->first);
  currLayerTree.push_back(T.insert(T.begin(),G.begin()->first));
  visitados[G.begin()->first];
  
  while(currLayer.size()){
    nextLayer.clear();
    nextLayerTree.clear();
    
    auto itLayer = currLayerTree.begin();
    for(char &n: currLayer){
      auto it = *itLayer;
      it = it.lchild();
      for(char &m: G[n]){
        if(visitados.find(m)==visitados.end()){
          nextLayer.push_back(m);
          it = T.insert(it,m);
          nextLayerTree.push_back(it);
          visitados[m];
          it++;
        }
      }
      itLayer++;
    }
    currLayer = nextLayer;
    currLayerTree = nextLayerTree;
  }
  
}

void intersect_map(map<int,list<int>> &A, map<int,list<int>> &B,map<int,list<int>> &C){
  auto itA = A.begin();
  auto itB =B.begin();
  
  
  while(itA!= A.end()){
    if(B.find(itA->first)!=B.end()){
      list<int> L;
      for(auto &el_a: A[itA->first]){
        if(find(B[itA->first].begin(), B[itA->first].end(),el_a)!=B[itA->first].end()){
          L.push_back(el_a);
        }
      }
      if(L.size())C[itA->first] = L;
    }
    itA++;
  }
  
  
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(fill_ordprev,vrbs);
    h1 = ev.evalr<1>(fill_ordprev,seed,vrbs);

    ev.eval<2>(a_lo_ancho,vrbs);
    h2 = ev.evalr<2>(a_lo_ancho,seed,vrbs);
    
    ev.eval<3>(intersect_map,vrbs);
    h3 = ev.evalr<3>(intersect_map,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
}
