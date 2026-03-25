// GITVERSION: aed-2021-206-g38e74854
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
  
  typedef pair<int,int> (*findmaxdepth_t)(tree<int> &T,bool (*pred)(int));
  class eval1_t : public eval_base_t {
  public:
    findmaxdepth_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./fmd.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      tree<int> T;
      bool(*pred)(int);
      lisp2tree(data["T"],T);
      string pname = data["pred"];
#define DPRED(p) else if (pname==#p) pred=p
      if (0) {}
      DPRED(even);
      DPRED(odd);
      DPRED(ge7);
      DPRED(le3);
      DPRED(div4);
      DPRED(isprime);
      DPRED(isnotprime);
      pair<int,int> p;
      p = F(T,pred);
      outuser["nodeval"] = p.first;
      outuser["depth"] = p.second;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
#if 0      
      list<int> L;
      int n=8+rnd.rand()%8;
      for (int j=0; j<n; j++)
        L.push_back(rnd.rand()%10);
      datain["L"] = L;
#endif
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,findmaxdepth_t>;
}
#undef CSTR

#endif
