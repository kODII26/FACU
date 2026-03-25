// GITVERSION: aed-2021-513-gbf3233fb
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

  typedef int (*sumcartesian_t)(set<int> &A, set<int> &B);
  class eval1_t : public eval_base_t {
  public:
    sumcartesian_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./sumc.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      set<int> A = data["A"];
      set<int> B = data["B"];
      outuser["sum"] = F(A,B);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      for (int k=0; k<2; k++) {
        int n = 3+rnd.rand()%5;
        set<int> S;
        for (int j=0; j<n; j++) 
          S.insert(rnd.rand()%7);
        string key = (k==0? "A" : "B");
        datain[key] = json(S);
      }
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,sumcartesian_t>;
}
#undef CSTR

#endif
