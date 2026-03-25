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

  typedef void (*set_prime_t)(vector<set<int>> &VS, set<int> &S);
  class eval1_t : public eval_base_t {
  public:
    set_prime_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./fb.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      
      json jVS = data["VS"];
      vector< set<int> > VS;
      for(auto p = jVS.begin(); p!=jVS.end(); p++) {
        VS.push_back(*p);
      }
      set<int> S;
      F(VS,S);
      outuser["S"] = S;
      
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      set<int> 
        suser = outuser["S"],
        sref = outref["S"];
      return suser==sref;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      
      int Nset = 2+rnd.rand()%2;
      json &jVS = datain["VS"];
      for (int j=0; j<Nset; j++) {
        set<int> S;
        int Nelems = 2+rnd.rand()%2;
        for (int k=0; k<5; k++) S.insert(10+rnd.rand()%90);
        jVS.push_back(S);
      }

    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,set_prime_t>;
}
#undef CSTR

#endif
