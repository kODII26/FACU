// GITVERSION: aed-2021-137-g25d89fc3
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/str_convs.hpp"
#include <forward_list>
#include <sstream>
using namespace std;

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  //   FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  //void force(list<int> &A, list<int> &B, int (*f)(int,int),
  //  mapfun_t f, ,randomg_t &rnd) {
  //  if (n==T.end()) return;
  //  auto cl=n.left();
  //  auto cr=n.right();
  //  unsigned int prob=50;
  //  if (cl!=T.end() && rnd.rand()%100<prob) *cl=f(*n);
  //  if (cr!=T.end() && rnd.rand()%100<prob) *cr=f(*n);
  //  force(T,cl,f,rnd);
  //  force(T,cr,f,rnd);
  //}
  void force(set<int> &A, set<int> &B, int (*f)(int), randomg_t &rnd)
  {
    B.clear();
    unsigned int prob = 50;
    if (rnd.rand()%100 < prob){
      auto itA = A.begin();
      while (itA != A.end()) {
        int b = f(*itA);
        B.insert(b);
        ++itA;
      }
    }else{
      int n = 8+rnd.rand()%8;
      int x = rnd.rand()%2;
      for (int j=0; j<n; j++) {
        int z = rnd.rand()%20;
        if (rnd.rand()%5>=2) z += -(z%2) + x%2;
        x=z;
        B.insert(z);
      }
      
    }
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t
  
  typedef void (*prime_distance_t)(list<int>& L);
  class eval1_t : public eval_base_t {
  public:
    prime_distance_t F;
    eval1_t() { dumptests=1; F=NULL; ejerc=EJERC; testfile="./dp.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L = data["L"];
      int v = data["v"];
      F(L);
      outuser["Lout"] = L;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) 
    {
      return outuser==outref;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      list<int> L;
      int n = 3+rnd.rand()%10, S=0;
      for(int i=0;i<n;i++) {
        int x = rnd.rand()%20;
        L.push_back(x);
      }
      int v = -10+rnd.rand()%20;
      datain["L"] = L;
      datain["v"] = v;

    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,prime_distance_t>;
}
#undef CSTR

#endif
