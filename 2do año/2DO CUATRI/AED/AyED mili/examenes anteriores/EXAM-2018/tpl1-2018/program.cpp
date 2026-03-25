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

void sign_split(list<int> &L,vector< list<int> > &VL) {
  // COMPLETAR AQUI....
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
void sign_join(vector< list<int> > &VL,list<int> &L) {
  // COMPLETAR AQUI....
}

void reverseStack(stack<int>&S){
  // COMPLETAR AQUI....
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
