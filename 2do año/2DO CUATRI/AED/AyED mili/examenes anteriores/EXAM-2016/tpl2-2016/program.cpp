#define USECHRONO
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

bool unordered_equal(tree<int> &A,tree<int> &B,
                     tree<int>::iterator itA,
                     tree<int>::iterator itB) {
  bool retorno = true;
  map<int,tree<int>::iterator> MA;
  auto c = itA.lchild();
  while(c!=A.end()){
    MA[*c]=c;
    c++;
  }
  map<int,tree<int>::iterator> MB;
  auto d = itB.lchild();
  while(d!=B.end()){
    MB[*d]=d;
    d++;
  }
  if(MA.size()!=MB.size()) return false;
  auto p= MA.begin(); auto q= MB.begin();
  while(p!=MA.end() && retorno){
    if(p->first!=q->first) return false;
    retorno = unordered_equal(A,B,p->second,q->second);
    p++;q++;
  }
  return retorno;
}

bool unordered_equal(tree<int> &A,tree<int> &B) {
  auto itA=A.begin();
  auto itB=B.begin();
  if(*itA!=*itB) return false;
  return unordered_equal(A,B,itA,itB);
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
bool hay_camino(map<string,list<string> > &M, string cini, string cfin, map<string,bool> visited) {
  // COMPLETAR ....
  return false;
}

bool hay_camino(map<string,list<string> > &M, list<string> &P, string cini, string cfin) {
  map<string,bool> visited;
  
  return true;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void enhance_html(tree<string> &T, string father, tree<string>::iterator it) {
  if(it==T.end()) return;
  if(*it=="a" && father!="strong"){
    *it="strong";
    it = T.insert(it.lchild(),"a");
  }else{
    auto c = it.lchild();
    while(c!=T.end()){
      enhance_html(T, *it,c);
      c++;
    }
  }
  
   
}

void enhance_html(tree<string> &T) {
  enhance_html(T,*T.begin(),T.begin().lchild());
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  ev.eval<1>(unordered_equal,vrbs);
  h1 = ev.evalr<1>(unordered_equal,seed,vrbs);
  
  /*ev.eval<2>(hay_camino,vrbs);
  h2 = ev.evalr<2>(hay_camino,seed,vrbs);*/
  
  ev.eval<3>(enhance_html,vrbs);
  h3 = ev.evalr<3>(enhance_html,seed,vrbs);

  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);
  
  return 0;
}
