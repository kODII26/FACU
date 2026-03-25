#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

typedef tree<int>::iterator node_t;

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void tree2count(tree<int> &T,list<int> &L) {
  // COMPLETAR...
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void count2tree(list<int> &L,tree<int> &T) {
  // COMPLETAR...
}

bool hasnpath(map<int,list<int> >&M, int a, int b, int n){
  // COMPLETAR...
  return false;
}
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void key2abbrev(map<string,string> &abbrevs) {
  // COMPLETAR...
}

int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval1(tree2count,vrbs);
  h1 = ev.evalr1(tree2count,seed,vrbs);

  ev.eval2(count2tree,vrbs);
  h2 = ev.evalr2(count2tree,seed,vrbs);

  ev.eval3(hasnpath,vrbs);
  h3 = ev.evalr3(hasnpath,seed,vrbs);

  ev.eval4(key2abbrev,vrbs);
  h4 = ev.evalr4(key2abbrev,seed,vrbs);

  // Para S=123 debe dar -> H1=626 H2=303 H3=334 H4=512
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d\n",
         seed,h1,h2,h3,h4);

  return 0;
}
