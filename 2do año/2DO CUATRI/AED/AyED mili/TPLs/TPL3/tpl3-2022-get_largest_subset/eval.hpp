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

  typedef void (*get_largest_subset_t)(set<int> &S,set<int> &C);
  class eval1_t : public eval_base_t {
  public:
    get_largest_subset_t F;
    eval1_t() {
      dumptests=1;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./fb.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      set<int> S = data["S"];
      set<int> C;
      F(S,C);
      outuser["C"] = C;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      set<int> 
        suser = outuser["C"],
        sref = outref["C"];
      return suser==sref;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      set<int> S;
      int n=5+rnd.rand()%5;
      for (int j=0; j<n; j++)
        S.insert(rnd.rand()%10);
      datain["S"] = S;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,get_largest_subset_t>;
}
#undef CSTR

#endif
