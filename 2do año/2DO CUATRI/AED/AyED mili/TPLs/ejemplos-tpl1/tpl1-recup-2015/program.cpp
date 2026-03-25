#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

list<int> mochila(list<int> &L,int K) {
  // COMPLETAR AQUI...
  return list<int>();
}

bool enunosolo(list<list <int> > &LL, list<int> &L) {
  // COMPLETAR AQUI...
  return true;
}

int ppt(list<int> &H, int n) {
  int nextplay=0;
  list<int> last;
  list<int>::iterator it_end = --H.end();
  for(int i =0; i<n; i++){
	  last.push_front(*it_end);
	  it_end--;
  }
  list<int>::iterator it = H.begin();
  while(it!=H.end()){
	list<int>::iterator it2 = it++, q = last.begin();
	while(it2!=H.end() && q!=last.end() && *it2==*q){
		it2++;q++;
	}
	if(q!=last.end() || it2==H.end()) continue;
	nextplay=*it2;
	//it++;
  }
  return nextplay;
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 132;
  int h1=0,h2=0,h3=0;

  //ev.eval1(mochila,vrbs);
  //h1 = ev.evalr1(mochila,seed,0);

  //ev.eval2(enunosolo,vrbs);
  //h2 = ev.evalr2(enunosolo,seed,0);

  ev.eval3(ppt,vrbs);
  h3 = ev.evalr3(ppt,seed,0);

  // Para SEED=123 debe dar -> H1=333 H2=357 H3=340
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d\n",
         seed,h1,h2,h3);
  
  return 0;
}
