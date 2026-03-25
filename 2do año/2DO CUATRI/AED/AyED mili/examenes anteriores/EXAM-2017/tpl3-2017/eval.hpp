// GITVERSION: aed-3.1-107-g705fb69d
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"
#include <forward_list>
#include <sstream>
using namespace std;

namespace aed {

  template<typename TKey, typename TValue>
  void str2map(std::map<TKey,TValue> &M, const std::string &s) {
    TKey clave; TValue valor;
    for(size_t i=1, p0=1;i<s.size();i++) { 
      if (s[i]==','||s[i]==')') {
        string spar = s.substr(p0,i-p0);
        spar.replace(spar.find("->"),2," ");
        std::stringstream ss(spar);
        ss>>clave>>valor;
        M[clave] = valor;
        p0=i+1;
      }
    }
  }
  
  template<typename T>
  std::string tree2lisp(tree<T> &A, typename tree<T>::iterator it) {
    std::stringstream ss;
    if (it.lchild()==A.end()) ss << *it;
    else {
      ss << "(" << *it;
      for(auto it2=it.lchild();it2!=A.end();++it2)
        ss << " " << tree2lisp(A,it2);
      ss << ")";
    }
    return ss.str();
  }
  
  template<typename T>
  std::string tree2lisp(tree<T> &A) {
    // if (A.begin()==A.end()) return "()";
    if (A.begin()==A.end()) return "";
    // return std::string("("+tree2lisp(A,A.begin())+")");
    return tree2lisp(A,A.begin());
  }

  //para funcional (ej pruneIf)
  typedef bool (*bt_fun_t)(int);
  bool even(int x) {return (x%2==0);}
  bool prime(int x) {
    if(x%2==0 && x!=2)
      return false;
    else{
      for(int i = 2 ;i<x-1;i++){
        if(x%i == 0)
          return false;
      }
      return true;
    }
  }
  
  //crea arbol binario posiblemente de busqueda
  
  void make_bst(btree<int> &t, btree<int>::iterator it,
                int min, int max, int n,randomg_t &rnd) {
    // corta por nivel y poda cada tanto para que no sea lleno
    if (rnd.rand()%(10-n)==0 || --n<0) return; 
    float f = (rnd.rand()%1001)/1000.f;
    f = pow(f,50); // el 25 controla cuan bst es, cuanto mas alto mas prob de serlo
    int v = int((min+max)/2 + (min+max)/2*f*(rnd.rand()%2?1:-1));
    it = t.insert(it,v);
    make_bst(t,it.left(),min,v,n,rnd);
    make_bst(t,it.right(),v,max,n,rnd);
  }
  
  //devuelve string de AB en notación lisp
  string btree2lisp(btree<int>::iterator n,btree<int> &T) {
    btree<int>::iterator r,l;
    stringstream ss;
    if (n==T.end()) { ss << "." ;return ss.str();}
    bool is_leaf;
    r=n.right();
    l=n.left();
    is_leaf=(r==T.end() && l==T.end());
    if (is_leaf==true) {
      ss << *n;}
    else { ss << "(" << *n << " ";
      ss << btree2lisp(l,T);
      ss << " ";
      ss << btree2lisp(r,T) ;
      ss << ")";
    }
    return ss.str();
  }
  // -------------------------------------------------------------
  string btree2lisp(btree<int>&T) { 
    return btree2lisp(T.begin(),T); 
  } 

  //genera lista aleatoria de length elementos en el rango min-max
  void randomList(list<int>&L,int min,int max, int length,randomg_t& rnd){
    for(int i = 0; i<length;i++){
      int x = min+rnd.rand()%max;
      L.push_back(x);
    }
  }
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> isBST
  typedef bool (*isbst_t)(btree<int>&T);
  class eval1_t : public eval_base_t {
    
  public:
    isbst_t F;
    eval1_t(){ dumptests=0;F=NULL;ejerc=1;testfile="./ib.json"; }
    void run_case(json &data, json &outuser){
      btree<int> T;
      lisp2btree(data["T"],T);
      outuser["R"] = F(T);
    }
    int check_case(json &datain,json &outref,json &outuser){
      return outref==outuser;
    }
	  
    void generate_case(randomg_t &rnd,json &datain){
      btree<int> T;
      int nl = 2+rnd.rand()%7; // niveles
      make_bst(T,T.begin(),0,50,nl,rnd);
      datain["T"] = btree2lisp(T);
    }
  };
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> fillBST
  typedef void (*fillbst_t)(btree<int>&T,list<int>&L);
  class eval2_t : public eval_base_t {

  public:
    fillbst_t F;
    eval2_t() { dumptests=0; F=NULL; ejerc=2; testfile="./fb.json"; }
    void run_case(json &data,json &outuser) {
      list<int> L = data["L"];
      btree<int> T;
      F(T,L);
      outuser["T"] = btree2lisp(T);
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      list<int> L;
      int min = 1+rnd.rand()%10;
      int max = min+rnd.rand()%1000;
      int length =  1+rnd.rand()%75;
      randomList(L,0,max,length,rnd);
      datain["L"] = L;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> EQSUMSPLIT
  typedef bool (*eqsumsplit_t)(set<int> &S);
  class eval3_t : public eval_base_t {
  public:
    eqsumsplit_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./eqs.json"; }
    void run_case(json &data,json &outuser) {
      set<int> S = data["S"];
      bool rv = F(S);
      outuser["retval"] = rv;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      set<int> S;
      int m = 5+rnd.rand()%5;
      int n = m;
      for (int j=0; j<m; j++) S.insert(rnd.rand()%n-n/2);
      datain["S"] = S;
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,isbst_t,
                      eval2_t,fillbst_t,
                      eval3_t,eqsumsplit_t>;
}
#undef CSTR

#endif
