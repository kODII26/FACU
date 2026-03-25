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
  
  typedef void (*tree2pmap_t)(tree<int> &T,map<int,int> &M);
  class eval1_t : public eval_base_t {
  public:
    tree2pmap_t F;
    eval1_t() {
      dumptests=0;
      const char *dt = getenv("DUMPTESTS");
      if (dt && !strcmp(dt,"1")) dumptests=1;
      F=NULL; ejerc=EJERC; testfile="./fmd.json";
    }
    void run_case(json &data, json &outuser) {
      check_dni();
      tree<int> T;
      lisp2tree(data["T"],T);
      list<int> L1 = data["L1"];
      list<int> L2 = data["L2"];
      map<int,int> M;
      list<int>::iterator it1 = L1.begin();
      list<int>::iterator it2 = L2.begin();
      while(it1!=L1.end()){
        M[*it1] = *it2;
        it1++;
        it2++;
      }
      F(T,M);
      
      list<int> L3;
      list<int> L4;
      
      map<int,int>::iterator itm = M.begin();
      while(itm!=M.end()){
        L3.push_back(itm->first);
        L4.push_back(itm->second);
        itm++;
      }

      outuser["OL1"] = L3;
      outuser["OL2"] = L4;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }

    void generate_case(randomg_t &rnd,json &datain) {


      list<int> L1;
      int n=5;
      for (int j=0; j<n; j++)
        L1.push_back(rnd.rand()%10);
      datain["L1"] = L1;
      
      list<int> L2;
      n=5;
      for (int j=0; j<n; j++)
        L2.push_back(rnd.rand()%10);
      datain["L2"] = L2;
        
      tree<int> T;
      int m = 5+rnd.rand()%10; 
      n = 5+rnd.rand()%10;
      make_random_tree2(T,10,m,n,rnd);
      datain["T"] = tree2lisp(T);


    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,tree2pmap_t>;
}
#undef CSTR

#endif
