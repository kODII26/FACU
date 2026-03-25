#include "eval.hpp"
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

void mkmtree(tree<int> &T,int m,int k) {
  // COMPLETAR AQUI...
}

bool has_equal_path(tree_t &T) {
  // COMPLETAR AQUI...
  return false;
}

void pancake_sort(stack<int> &s){
  // COMPLETAR AQUI...
}

int count_cycles(map<int,int> &M){
  // COMPLETAR AQUI...
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval1(mkmtree,vrbs);
  h1 = ev.eval1r(mkmtree,seed); // para SEED=123 debe dar H1=170

  ev.eval2(has_equal_path,vrbs);
  h2 = ev.eval2r(has_equal_path,seed); // para SEED=123 debe dar H2=959

  ev.eval3(pancake_sort,vrbs);
  h3 = ev.eval3r(pancake_sort,seed); // para SEED=123 debe dar H3=489

  ev.eval4(count_cycles,vrbs);
  h4 = ev.eval4r(count_cycles,seed); // para SEED=123 debe dar H4=392
 
  printf("SEED=%03d -> HASH1=%03d, HASH2=%03d, HASH3=%03d, HASH4=%03d\n",
         seed,h1,h2,h3,h4);

  return 0;
}
