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

void get_path(tree<int> &T, tree<int>::iterator q, int n, list<int> &L){
  if(q==T.end()) return;
  if (*q==n) {
    L.clear();
    L.push_back(n);
    return;
  }
  auto c =q.lchild();
  while (c!=T.end()) {
    get_path(T,c,n,L);
    if (!L.empty()) {
      L.push_front(*q);
      return;
    }
    c++;
  }
}
void get_path(tree<int> T,int n,list<int> &L){
  tree<int>::iterator it = T.begin();
  L.clear();
  get_path(T, it, n, L);
}
void classify_relative(tree<int> &T,int n1,int n2,int &m1, int&m2) {
  list<int> L1,L2;
  get_path(T,n1,L1); get_path(T,n2,L2);
  for(list<int>::iterator it1=L1.begin(), it2 = L2.begin();L1.size()&&L2.size()&& *it1==*it2; it1++, it2++){
    L1.erase(L1.begin()); L2.erase(L2.begin());
  }
  m1 = L1.size(); m2 = L2.size();
  
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void hojas(tree<int> &arbol, tree<int>::iterator p, list<int> &L, int &n){
  if(p==arbol.end()) return;
  auto c = p.lchild();
  if(c==arbol.end()){
    //L.push_back(*p);
    L.push_back(n);
    n=0;
  }
  while(c!=arbol.end()) hojas(arbol,c++,L,++n);
}
list<int> hojas(tree<int> &arbol){
  list<int> L; int n =0;
  hojas(arbol,arbol.begin(),L,n);
  return L;
}
  
void prom_path(tree<int> &T, tree<int>::iterator p, int l, int& sum, int& cant){
  tree<int>::iterator c = p.lchild();
  if(c==T.end()){cant++; sum+=l; return;}
  while(c!=T.end()){
    prom_path(T,c++,l+1,sum,cant);
  }
}

float prom_path(tree<int> &T) {
  int sum =0, cant=0;
  prom_path(T, T.begin(),0,sum,cant);
  if(cant==0) return 0;
  return float(sum)/cant;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void filtra_deps(map<string,list<string>> &G,list<string> &L) {
  map<string, bool> necesarios;
  for(string &p: L){
    necesarios[p];
    for(string &pp: G[p]){
      if(necesarios.find(pp)!=necesarios.end()){
        necesarios[pp];
      }
    }
  }
  map<string,list<string>>::iterator it = G.begin();
  while(it!=G.end()){
    if(necesarios.find(it->first)==necesarios.end()){
      it=G.erase(it);
    }else{
      list<string>::iterator itAux= G[it->first].begin();
      while(itAux!=G[it->first].end()){
        if(necesarios.find(*itAux)==necesarios.end()){
          itAux=G[it->first].erase(itAux);
        }else{
          itAux++;
        }
        
      }
      it++;
    }
    
  }
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    ev.eval<1>(classify_relative,vrbs);
    h1 = ev.evalr<1>(classify_relative,seed,vrbs);

    ev.eval<2>(prom_path,vrbs);
    h2 = ev.evalr<2>(prom_path,seed,vrbs);

    ev.eval<3>(filtra_deps,vrbs);
    h3 = ev.evalr<3>(filtra_deps,seed,vrbs);

    /*printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");*/
  } while (cin>>seed);

  return 0;
}
