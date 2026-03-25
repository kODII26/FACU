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

bool domina(vector<int> x, vector<int> y){
  bool cond2=false;
  for(size_t i =0; i<x.size(); i++){
    if(x[i]>y[i]) return false;
    if(x[i]<y[i]) cond2=true;
  }
  return cond2;
}

list<vector<int>> Pareto(list<vector<int>>&L){
  list<vector<int>> no_dominados;
  list<vector<int>>::iterator it = L.begin();
  while(it!=L.end()){
    list<vector<int>>::iterator it_aux = L.begin();
    bool agregar = true;
    while(it_aux!=L.end()){
      if(domina(*it_aux,*it)){
        agregar=false;
        break;
      }
      it_aux++;
    }
    if(agregar) no_dominados.push_back(*it);
    it++;
  }
  return no_dominados;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool todas_vacias(vector< queue<int> > qords){
  for(queue<int> &x : qords){
    if(!x.empty()) return false;
  }
  return true;
}
void merge_kway(vector< queue<int> > &qords, queue<int> &merged) {
  int tamanio = qords.size();
  while(!todas_vacias(qords)){
    int prox=9999;
    int pos;
    for(int i=0; i<tamanio;i++){
      if(!qords[i].empty() && qords[i].front()<prox){
        prox = qords[i].front();
        pos =i;
      }
    }
    qords[pos].pop();
    merged.push(prox);
  }
  
}

bool is_balanced(string &c) {
  stack<char> S;
  for(char &l : c){
    if(l=='(' || l=='{' || l=='['){
      S.push(l);
    }
    if(l==')' || l=='}' || l==']'){
      if(S.empty()) return false;
      if(l==')' and S.top()!='(') return false;
      else if(l==']' and S.top()!='[') return false;
      else if(l=='}' and S.top()!='{') return false;
      else S.pop();
    }
  }
  if(!S.empty()) return false;
  return true;
}
 
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

int main() {

  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  cout << "seed: 123" << endl;
  do {
    ev.eval<1>(Pareto,vrbs);
    h1 = ev.evalr<1>(Pareto,seed,vrbs);

    ev.eval<2>(merge_kway,vrbs);
    h2 = ev.evalr<2>(merge_kway,seed,vrbs);
    
    ev.eval<3>(is_balanced,vrbs);
    h3 = ev.evalr<3>(is_balanced,seed,vrbs);
    
    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    cout << endl << "Siguiente seed: ";
  } while (cin>>seed);

  return 0;
}
