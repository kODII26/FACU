// GITVERSION: aed-2021-537-g62b5f67c
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

  bool par(int x) { return x%2==0; }
  bool impar(int x) { return (x%2)!=0; }
  bool positivo(int x) { return x>0; }
  bool negativo(int x) { return x<0; }
  bool nulo(int x) { return x==0; }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  // END FUNCTIONS FOR THIS EXAM
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef EVAL
#define EJERC 1
#define EVAL eval1_t

  typedef bool (*pred_t)(int);
  typedef void (*stack2queue_t)(stack<int> &S, queue<int> &Q,pred_t pred);
  class eval1_t : public eval_base_t {
  public:
    stack2queue_t F;
    eval1_t() {
      dumptests=0; ncasos=50;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./s2q.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      stack<int> S;
      for (auto x : data["S"]) S.push(x);

      string p = data["pred"];
      pred_t pred;
#define DEF(x) else if (p==#x) pred=x
      if (0) {}
      DEF(par);
      DEF(impar);
      DEF(positivo);
      DEF(negativo);
      DEF(nulo);
      else assert(0);
      
      queue<int> Q;
      json JQ;
      F(S,Q,pred);
      while (!Q.empty()) {
        JQ.push_back(Q.front());
        Q.pop();
      }
      outuser["Q"].swap(JQ);
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outuser==outref;
    }

    void generate_case(randomg_t &rnd,json &datain) {
      json S;
      int n=5 +rnd.rand()%10;
      for (int k=0; k<n; k++) 
        S.push_back(rnd.rand()%10);
      datain["S"].swap(S);
      datain["pred"] = (rnd.rand()%2? "par" : "impar");
      // cout << datain << endl;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,stack2queue_t>;
}
#undef CSTR

#endif
