#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void transpose(vector<list<int> > &M,vector<list<int> > &Mt) {
  int filas = M[0].size();
  Mt.resize(filas);
  int cols = M.size();
  for(int i = 0; i<cols ; i++){
    list<int>::iterator it = M[i].begin();
    int pos =0;
    while(it!=M[i].end()){
      Mt[pos].push_back(*it);
      it++;pos++;
    }
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void homogeniza(list<int>& C, int hmin, int hmax) {
  list<int>::iterator it = C.begin();
  while(it!=C.end()){
    while(next(it)!=C.end() && *next(it)<*it+hmin){
      it = C.erase(next(it));
      it--;
    }
    while(next(it)!=C.end() && *next(it)>*it+hmax){
      it = C.insert(next(it),*it+hmax);
      it--;
    }
    it++;
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void ordenar(list<int> &L){
  list<int> aux1 = L;
  list<int> aux2;
  list<int>::iterator it = aux1.begin();
  for(size_t i =0; i<L.size(); i++){
    auto it_min = min_element(aux1.begin(), aux1.end());
    aux2.push_back(*it_min);
    aux1.erase(it_min);
  }
  L = aux2;
}
void bool_opers(list<int> &Lxor, list<int> &Land, 
                list<int> &L1, list<int> &L2) {
  list<int>::iterator it1 = L1.begin();
  while(it1!=L1.end()){
    bool rep = false;
    list<int>::iterator it = L2.begin();
    while(it!=L2.end()){
      if(*it1==*it){
        Land.push_back(*it1);
        rep = true;
        it = L2.erase(it);
        it1=L1.erase(it1);
      }
      it++;
    }
    if(!rep){
      Lxor.push_back(*it1);
      it1=L1.erase(it1);
    }
  }
  
  it1 = L2.begin();
  while(it1!=L2.end()){
    bool rep = false;
    list<int>::iterator it = L1.begin();
    while(it!=L1.end()){
      if(*it1==*it){
        rep = true;
      }
      it++;
    }
    if(!rep) Lxor.push_back(*it1);
    it1 = L2.erase(it1);
  }
  
  ordenar(Land); 
  ordenar(Lxor);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  ev.eval<1>(transpose,vrbs);
  h1 = ev.evalr<1>(transpose,seed,vrbs);
  
  ev.eval<2>(homogeniza,vrbs);
  h2 = ev.evalr<2>(homogeniza,seed,vrbs);
  
  ev.eval<3>(bool_opers,vrbs);
  h3 = ev.evalr<3>(bool_opers,seed,vrbs);

  // Debe dar para S=123 -> H1=028 H2=361 H3=840
  // printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
  //        seed,h1,h2,h3);
  
  return 0;
}
