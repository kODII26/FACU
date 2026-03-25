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

int sign(int x){
  if(x<0) return -1;
  else return 1;
}
void sign_split(list<int> &L,vector< list<int> > &VL) {
  list<int>::iterator it = L.begin();
  int s = sign(*it);
  list<int> sublist;
  while(it!=L.end()){
    if(sign(*it)==s){
      sublist.push_back(*it);
    }else{
      VL.push_back(sublist);
      s=-s;
      sublist.clear();
      sublist.push_back(*it);
    }
    it++;
  }
  VL.push_back(sublist);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void sign_join(vector< list<int>> &VL,list<int> &L) {
  int s = 1;
  while(!VL.empty()){
    for(size_t i=0;i<VL.size(); i++){
      list<int>::iterator it = VL[i].begin();
      while(it!=VL[i].end() && sign(*it)==s){
        L.push_back(*it);
        it = VL[i].erase(it);
      }
      if(VL[i].empty()){
        VL.erase(VL.begin()+i);
        i--;
      }
    }
    s=-s;
  }
}

void auxReverseStack(stack<int> &S, int el){
  if(S.empty()) S.push(el);
  else{
    int aux = S.top();
    S.pop();
    auxReverseStack(S,el);
    S.push(aux);
  }
}

void reverseStack(stack<int>&S){
  if(S.empty()) return;
  int aux = S.top();
  S.pop();
  reverseStack(S);
  auxReverseStack(S,aux);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    ev.eval<1>(sign_split,vrbs);
    h1 = ev.evalr<1>(sign_split,seed,vrbs);

    ev.eval<2>(sign_join,vrbs);
    h2 = ev.evalr<2>(sign_join,seed,vrbs);

    ev.eval<3>(reverseStack,vrbs);
    h3 = ev.evalr<3>(reverseStack,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
