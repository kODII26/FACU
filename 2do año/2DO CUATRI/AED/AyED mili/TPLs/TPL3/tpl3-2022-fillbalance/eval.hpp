// GITVERSION: aed-2021-216-gb9900979
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/str_convs.hpp"
#include <forward_list>
#include <sstream>
using namespace std;

bool even(int x);
bool odd(int x);
bool ge7(int x);
bool le3(int x);
bool div4(int x);
bool isprime(int x);
bool isnotprime(int x);
  
namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  //   FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t

  typedef void (*fillbalance_t)(btree<int> &B,list<int> &L);
  class eval1_t : public eval_base_t {
  public:
    fillbalance_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./fb.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      list<int> L = data["L"];
      btree<int> B;
      F(B,L);
      outuser["B"] = lisp_print(B);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      string
        suser = outuser["B"],
        sref = outref["B"];
      btree<int> Buser,Bref;
      lisp2btree(suser,Buser);
      lisp2btree(sref,Bref);
      return Buser==Bref;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      list<int> L;
      int n=5+rnd.rand()%5;
      for (int j=0; j<n; j++)
        L.push_back(rnd.rand()%10);
      datain["L"] = L;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,fillbalance_t>;
}
#undef CSTR

#endif
