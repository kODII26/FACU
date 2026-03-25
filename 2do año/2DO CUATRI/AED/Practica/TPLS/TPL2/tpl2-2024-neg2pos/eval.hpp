// GITVERSION: aed-2021-480-g1f515127
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

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t

  typedef void (*neg2pos_t)(list<int>& L, map<int,list<int>>& M);
  class eval1_t : public eval_base_t {
  public:
    neg2pos_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./n2p.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      list<int> L=data["L"];
      map<int,list<int>> M;
      F(L,M);
      json m;
      for (auto &q : M) {
        m.push_back(q.first);
        m.push_back(json(q.second));
      }
      outuser["M"].swap(m);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outuser==outref;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      int n = 8+rnd.rand()%8;
      int k=-(rnd.rand()%8)-1;
      datain["L"].push_back(k);
      for (int j=0; j<n; j++) {
        int k=(rnd.rand()%20)-5;
        datain["L"].push_back(k);
      }
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,neg2pos_t>;
}
#undef CSTR

#endif
