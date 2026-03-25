// GITVERSION: aed-3.0-28-g4527c35
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"

namespace aed {

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  typedef void (*transpose_t)(vector<list<int> > &M,vector<list<int> > &Mt);
  class eval1_t : public eval_base_t {
  public:
    transpose_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=1; testfile="./tests1.json"; }
    void run_case(json &data,json &outuser) {
      int m = data["m"];
      int n = data["n"];
      vector<int> v = data["v"];
      list<int> w = data["v"];
      assert(int(v.size())==m*n);
      vector<list<int> > M,Mt;
      M.resize(m);
      for (int j=0; j<m; j++) 
        for (int k=0; k<n; k++) 
          M[j].push_back(v[j*n+k]);
      F(M,Mt);
      outuser["oksizes"] = 1;
      vector<int> vout;
      outuser["vout"] = vout;
      const int ERRO = 1;
      try {
        if (int(Mt.size())!=n) throw ERRO;
        for (int j=0; j<n; j++) {
          list<int> col=Mt[j];
          if (int(col.size())!=m) throw ERRO;
          auto p=col.begin();
          while (p!=col.end()) vout.push_back(*p++);
        }
      } catch(int z) {
        outuser["oksizes"] = 0;
        return;
      }
      outuser["vout"] = vout;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int m=3+rnd.rand()%3,n=3+rnd.rand()%3;
      datain["m"] = m;
      datain["n"] = n;
      vector<int> v;
      for (int j=0; j<m*n; j++) v.push_back(rnd.rand()%20);
      datain["v"] = v;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  typedef void (*homogeniza_t)(list<int>&C,int hmin, int hmax);
  class eval2_t : public eval_base_t {
  public:
    homogeniza_t F;
    eval2_t() { dumptests=0; F=NULL; ejerc=2; testfile="./tests2.json"; }
    void run_case(json &data,json &outuser) {
      int hmin = data["hmin"];
      int hmax = data["hmax"];
      vector<int> Cv = data["C"];
      list<int> C;
      for (int j=0; j<int(Cv.size()); j++){
        C.push_back(Cv[j]);
      }
      F(C,hmin,hmax);
      
      vector<int> Cout;
      auto it = C.begin();
      while(it!=C.end()){
        Cout.push_back(*it++); 
      }
      outuser["Cout"] = Cout;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int m=1+rnd.rand()%3,n=m+1+rnd.rand()%5;
      int s=5+rnd.rand()%5;
      datain["hmin"] = m;
      datain["hmax"] = n;
      vector<int> C;
      int last = 0;
      for (int j=0; j<s; j++){
        int inc = 1+rnd.rand()%(2*n);
        C.push_back(last+inc);
        last+=inc;
      }
      datain["C"] = C;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  typedef void (*bool_opers_t)(list<int> &Lxor, list<int> &Land, 
                               list<int> &L1, list<int> &L2);
  class eval3_t : public eval_base_t {
  public:
    bool_opers_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./tests3.json"; }
    void run_case(json &data,json &outuser) {
      list<int> Land,Lxor,
        L1 = data["L1"],
        L2 = data["L2"];
      F(Lxor,Land,L1,L2);
      outuser["Lxor"] = Lxor;
      outuser["Land"] = Land;
    }
    
    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int
        N1=5+rnd.rand()%5,
        N2=5+rnd.rand()%5;
      list<int> L1,L2;
      int z;
      z = rnd.rand()%3;
      for (int j=0; j<N1; j++) {
        L1.push_back(z); z+= rnd.rand()%3;
      }
      z = rnd.rand()%3;
      for (int j=0; j<N2; j++) {
        L2.push_back(z); z+= rnd.rand()%3;
      }
      datain["L1"] = L1;
      datain["L2"] = L2;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,transpose_t,
                      eval2_t,homogeniza_t,
                      eval3_t,bool_opers_t>;
}
#undef CSTR

#endif
