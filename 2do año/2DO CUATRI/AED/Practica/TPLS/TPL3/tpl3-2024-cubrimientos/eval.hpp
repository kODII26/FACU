// GITVERSION: aed-2021-509-gdf2a3965
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

  typedef int (*cubrimientos_t)(list<set<int>> &L);
  class eval1_t : public eval_base_t {
  public:
    cubrimientos_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./cub.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      json &JL = data["L"];
      list<set<int>> L;
      for (auto &s : JL) {
        set<int> S = s;
        L.push_back(S);
      }
      int n = F(L);
      // cout << JL << "    =>   "  << n << endl;
      data["L"].swap(JL);
      outuser["n"] = n;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      int nset=3+rnd.rand()%3;
      json JL;
      for (int j=0; j<nset; j++) {
        set<int> s;
        int m = 2+rnd.rand()%2;
        for (int k=0; k<m; k++) 
          s.insert(rnd.rand()%4);
        JL.push_back(json(s));
      }
      datain["L"].swap(JL);
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,cubrimientos_t>;
}
#undef CSTR

#endif
