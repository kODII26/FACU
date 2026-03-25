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

void make_full(btree<int> &T) {
  // COMPLETAR AQUI...
}

void suma(btree<int> &T, btree<int>::iterator it, int &sum){
  if(it==T.end()) return;
  sum+=*it;
  suma(T, it.left(),sum);
  suma(T,it.right(),sum);
}
  

void max_subbtree(btree<int> &T, btree<int>::iterator it, int &max_sum){
  if(it==T.end()) return;
  
  int sum=0;
  suma(T, it,sum);
  if(sum>max_sum) max_sum=sum;
  
  max_subbtree(T, it.left(), max_sum);
  max_subbtree(T, it.right(), max_sum);
  
}
int max_subbtree(btree<int>&T){
  int max_sum=0;
  max_subbtree(T, T.begin(), max_sum);
  
  return max_sum;
}

int most_connected(vector< set<int> > &VS) {
  // COMPLETAR AQUI...
  return 0;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    /*ev.eval<1>(make_full,vrbs);
    h1 = ev.evalr<1>(make_full,seed,vrbs);*/

    ev.eval<2>(max_subbtree,vrbs);
    h2 = ev.evalr<2>(max_subbtree,seed,vrbs);

    /*ev.eval<3>(most_connected,vrbs);
    h3 = ev.evalr<3>(most_connected,seed,vrbs);

    printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
           seed,h1,h2,h3);
    
    printf("\n\nIngrese un valor para la semilla:");*/
  } while (cin>>seed);

  return 0;
}
