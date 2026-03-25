#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include "aedtools/lisp.hpp"

namespace aed {

  
  
  typedef bool (*pred_int)(int);
  inline bool es_par(int x) { return x%2 == 0; }
  inline bool es_impar(int x) { return x%2 == 1; }
  // considerando que el generador genera ints entre 0 y 100
  inline bool es_menor_a_10(int x) { return x<10; }
  inline bool es_capicua(int x) { return x<10 || x/10==x%10; }
  inline bool es_primo(int x) {
    static set<int> primos =  {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    return primos.count(x)!=0;
  }
  inline bool es_compuesto(int x) { return !es_primo(x); }
  inline bool es_fibonacci(int x) {
    static set<int> primos =  {0,1,2,3,5,8,13,21,34,55,89,144};
    return primos.count(x)==0;
  }
  static map<string,pred_int > lista_predicados = { 
    {"es_par",es_par }, 
    {"es_impar",es_impar},
    {"es_primo",es_primo},
    {"es_compuesto",es_compuesto},
    {"es_capicua",es_capicua},
    {"es_menor_a_10",es_menor_a_10},
    {"es_fibonacci",es_fibonacci} };
  
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> PUEDE SIMPLIFICAR
  typedef bool (*puede_simplificar_t)(btree<string> &T, string fc);
  class eval_puede_simplificar_t : public eval_base_t {
  public:
    puede_simplificar_t F;
    eval_puede_simplificar_t() { dumptests=0; F=NULL; ejerc=1; testfile="./puede_simplificar.json"; }
    void run_case(json &data,json &outuser) {
      string sT = data["T"];
      string fc = data["fc"];
      btree<string> T;
      lisp2btree(sT,T);
      bool ret = F(T,fc);
      outuser["ret"] = ret?1:0;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    static string make_operand(randomg_t &rnd) {
      if (rnd.rand()%2==0) return string(1,(rnd.rand()%('z'-'a'))+'a'); // cte
      else return to_string(rnd.rand()%100); // variable
    }
    
    // prob=0 => no aparece fc... prob=1 => 50% aparece, prob=2 => aparece seguro
    static void make_expr_tree(randomg_t &rnd, btree<string> &T, btree<string>::iterator it, string fc, int cur_lev=0, int prob=1) {
      const int min_lev = 1, max_lev = 3;
      const static string opers = "****++--/";
      
      // operadores
      char oper;
      if (prob==2) {
        if (cur_lev+1==max_lev) oper = '*';
        else oper = opers[rnd.rand()%(opers.size()-1)]; // el -1 es para que no salga '/'
      } else oper = opers[rnd.rand()%opers.size()];
      it = T.insert(it,string(1,oper));
      if (cur_lev+1<max_lev && (cur_lev<min_lev || rnd.rand()%3) ) { 
        int lprob = prob, rprob = prob;
        if (oper=='*' && rnd.rand()%2<prob) {
          if (rnd.rand()%2) {
            lprob = 2; rprob = 0;
          } else {
            lprob = 0; rprob = 2;
          }
        }
        make_expr_tree(rnd,T,it.right(),fc,cur_lev+1,rprob);
        make_expr_tree(rnd,T,it.left(),fc,cur_lev+1,lprob);

      // operandos
      } else {
        if (prob==0 || (prob==1&&rnd.rand()%2)) {
          T.insert(it.right(),make_operand(rnd));
          T.insert(it.left(),make_operand(rnd));
        } else {
          if (prob==2 && oper!='*') {
            T.insert(it.right(),fc);
            T.insert(it.left(),fc);
          } else if (rnd.rand()%2) {
            T.insert(it.right(),fc);
            T.insert(it.left(),make_operand(rnd));
          } else {
            T.insert(it.right(),make_operand(rnd));
            T.insert(it.left(),fc);
          }
        } 
      }
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      string fc = make_operand(rnd);
      btree<string> T;
      make_expr_tree(rnd,T,T.begin(),fc,0,1);
      datain["T"] = lisp_print(T);
      datain["fc"] = fc;
    }
  };
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> PUEDE_SIMPLIFICAR
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> PRUNE_AND_RETURN
  template<typename T>
  void string2list(const string &str, list<T> &l) {
    stringstream ss (str); T aux;
    while (ss>>aux) l.push_back(aux);
  }
  template<typename T>
  string list2string(const list<T> &l) {
    stringstream ss; bool first = true;
    for(const auto &x:l) {
      if (!first) ss << " "; 
      ss << x; first=false; 
    }
    return ss.str();
  }
  
  typedef void (*prune_and_return_t)(btree<int>&, int, list<int>&);
  class eval_prune_and_ret_t : public eval_base_t {
  public:
    prune_and_return_t F;
    eval_prune_and_ret_t() { dumptests=0; F=NULL; ejerc=2; testfile="./prune_and_ret.json"; }
    void run_case(json &data,json &outuser) {
      string sT = data["T"];
      int v = data["v"];
      btree<int> T;
      lisp2btree(sT,T);
      list<int> L;
      F(T,v,L);
      outuser["T"] = lisp_print(T);
      outuser["L"] = list2string(L);
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      btree<int> T;
      make_random_btree(T,2,.5,rnd);
      lisp_print(T);
      datain["T"] = lisp_print(T);
      datain["v"] = 42;
    }
  };
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> END PRUNE_AND_RETURN
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> GATHER SETS
  typedef void (*gather_sets_t)(vector<set<int>> &VS,
                                bool (*pred)(int),set<int> &S);
  class eval_gather_sets_t : public eval_base_t {
  public:
    gather_sets_t F;
    eval_gather_sets_t() { dumptests=0; F=NULL; ejerc=3; testfile="./gather_sets.json"; }
    void run_case(json &data,json &outuser) {
      string fname = data["fname"];
      json jVS = data["VS"];
      vector< set<int> > VS;
      for(auto p = jVS.begin(); p!=jVS.end(); p++) {
        VS.push_back(*p);
      }
      set<int> S;
      F(VS,lista_predicados[fname],S);
      outuser["S"] = S;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int Nset = 3+rnd.rand()%5;
      json &jVS = datain["VS"];
      for (int j=0; j<Nset; j++) {
        set<int> S;
        int Nelems = 3+rnd.rand()%8;
        for (int k=0; k<10; k++) S.insert(rnd.rand()%100);
        jVS.push_back(S);
      }
      auto it = lista_predicados.begin();
      advance(it,rnd.rand()%lista_predicados.size());
      datain["fname"] = it->first;
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval_puede_simplificar_t,puede_simplificar_t,
                      eval_prune_and_ret_t,prune_and_return_t,
                      eval_gather_sets_t,gather_sets_t>;
}
#undef CSTR

#endif
