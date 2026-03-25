#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void prom_nivel(tree<int> &T, list<float> &P,tree<int>::iterator n,int l,map<int,list<int>> &lnodes){
  if(n==T.end()) return;
  
  lnodes[l].push_back(*n);
  tree<int>::iterator c = n.lchild();
  
  while(c!=T.end()){
    prom_nivel(T,P,c,l+1,lnodes); c++;
  }
}
  void prom_nivel(tree<int> &T, list<float> &P) {
    if (T.begin()==T.end()) return;
    
    map<int,list<int>> lnodes;
    prom_nivel(T,P,T.begin(),0,lnodes);
    
    int l=0;
    while(l< lnodes.size()){
      int sum=0;
      list<int> ln = lnodes[l];
      for(int &p: ln){
        sum+=p;
      }
      float prom = sum*1.0/(ln.size());
      P.push_back(prom);
      l++;
    }
  }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool pertenece(int x, list<int> L){
  for(int &y: L){
    if(y==x) return true;
  }
  return false;
}
bool es_circuito(map<int,list<int>>&G,list<int>&L){
  list<int>::iterator it = L.begin();
  while(it!=prev(L.end())){
    if(!pertenece(*next(it), G[*it])) return false;
    it++;
  }
  if(!pertenece(*L.begin(),G[*prev(L.end())])) return false;
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void unique(vector<int> &v) {
  // Using a map (could be a set)
  map<int,int> M;
  for (auto &x : v) M[x] = 1; // 1 or whatever
  v.clear();
  for (const auto &q : M) v.push_back(q.first);
  sort(v.begin(),v.end()); // No hace falta...
}
  
void map_graph(map<int,vector<int> > &Gin,map<int,int> &P,map<int,vector<int> > &Gout) {
  Gout.clear();
  map<int,vector<int>>::iterator it1 = Gin.begin();
  
  while(it1!=Gin.end()){
    for(int &x: it1->second){
      if(P.find(it1->first)!=P.end()){
        Gout[P[it1->first]].push_back(x);
      }
    }
    
    it1++;
  }
  for (auto & q : Gout) unique(q.second);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;
  
  
  

  do {
    /*ev.eval<1>(prom_nivel,vrbs);
    h3 = ev.evalr<1>(prom_nivel,seed,vrbs);*/
    
    /*ev.eval<2>(es_circuito,vrbs);
    h1 = ev.evalr<2>(es_circuito,seed,vrbs);*/
    
    ev.eval<3>(map_graph,vrbs);
    h2 = ev.evalr<3>(map_graph,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
