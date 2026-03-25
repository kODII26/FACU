// GITVERSION: aed-2021-477-gf4fa8304
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

  typedef void (*sortchild_t)(tree<int> &T);
  typedef void (*mkmono_t)(tree<int> &T);
  class eval1_t : public eval_base_t {
  public:
    mkmono_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./mkm.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      tree<int> T;
      string s = data["T"];
      lisp2tree(s,T);
      F(T);
      outuser["T"] = tree2lisp(T);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      tree<int> Tref,Tuser;
      lisp2tree(string(outuser["T"]),Tuser);
      lisp2tree(string(outref["T"]),Tref);
      return Tuser==Tref;
    }

    void fluct(randomg_t &rnd,tree<int> &T,tree<int>::iterator n) {
      if (n==T.end()) return;
      *n += rnd.rand()%6;
      auto c = n.lchild();
      while (c!=T.end()) fluct(rnd,T,c++);
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      tree<int> T;
      int m = 5+rnd.rand()%10;
      int n = 5+rnd.rand()%10;
      make_random_tree2(T,5,m,n,rnd);
      // cout << tree2lisp(T) << endl;
      F(T);
      // cout << tree2lisp(T) << endl;
      fluct(rnd,T,T.begin());
      // cout << tree2lisp(T) << endl;
      // static int cnt=0;
      // if (cnt>=3) exit(0);
      // cnt++;
      datain["T"] = tree2lisp(T);
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,sortchild_t>;
}
#undef CSTR

#endif
