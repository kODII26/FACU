// GITVERSION: aed-3.0-45-g19b81ae
#ifndef EVAL_HPP
#define EVAL_HPP
#include "aedtools/evalbase.hpp"

namespace aed {

  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> UNORDERED equal
  
  typedef bool (*unordered_equal_t)(tree<int> &A,tree<int> &B);
  class eval1_t : public eval_base_t {
  public:
    unordered_equal_t F;
    eval1_t() { dumptests=0; F=NULL; ejerc=1; testfile="./unordered.json"; }
    void run_case(json &data,json &outuser) {
      string sA = data["A"];
      string sB = data["B"];
      tree<int> tA; lisp2tree(sA,tA);
      tree<int> tB; lisp2tree(sB,tB);
      bool ret = F(tA,tB);
      outuser["ret"] = ret?1:0;
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    tree<int>::iterator advance(tree<int>::iterator it, int n) { 
      for(int i=0;i<n;i++) { ++it; } return it;
    }
    
    void random_shuffle(tree<int> &T, tree<int>::iterator it,
                        int nchildren, randomg_t &rnd)
    {
      it = it.lchild();
      for(int i=0; i<nchildren-1; ++i,++it) { 
        int j = rnd.rand()%(nchildren-i);
        if (j==0) continue;
        auto it2 = advance(it,j);
        it = T.splice(it,it2);
      }
    }
    void make_random_trees(tree<int> &tA, tree<int> &tB, 
                           tree<int>::iterator itA, tree<int>::iterator itB, 
                           int deep, randomg_t &rnd)
    {
      int nchildren = 2+rnd.rand()%4;
      for(int i=0, base=0; i<nchildren; ++i) {
        base += 1 + rnd.rand()%10;
        tA.insert(itA.lchild(),base);
        tB.insert(itB.lchild(),base);
      }
      if (--deep) {
        for(int i=0; i<nchildren; i++) 
          make_random_trees(tA,tB,advance(itA.lchild(),i),advance(itB.lchild(),i),deep,rnd);
      }
      random_shuffle(tA,itA,nchildren,rnd);
      random_shuffle(tB,itB,nchildren,rnd);
      int diff = rnd.rand()%5+deep;
      if (diff==0) tA.erase(advance(itA.lchild(),rnd.rand()%nchildren));
      if (diff==1) tB.erase(advance(itB.lchild(),rnd.rand()%nchildren));
      if (diff==2) *advance(itA.lchild(),rnd.rand()%nchildren)+=100;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      int deep = 1+rnd.rand()%4, root = rnd.rand()%100;
      tree<int> tA, tB;
      tA.insert(tA.begin(),root);
      tB.insert(tB.begin(), (rnd.rand()%9)==0? (rnd.rand()%100) : root );
      make_random_trees(tA,tB,tA.begin(),tB.begin(),deep,rnd);
      datain["A"] = lisp_print(tA);
      datain["B"] = lisp_print(tB);
    }
  };
  
  
  
  
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> FUNCIONES AUXILIARES
  
//  template<typename TContainer>
//  int string2container(TContainer &v, const string &str) {
//    stringstream ss(str);
//    string aux;
//    while(ss>>aux) v.push_back(aux);
//    return v.size();
//  }
  
  template<typename TContainer>
  int string2container(TContainer &v, const string &str) {
    stringstream ss(str);
    string aux;
    while(getline(ss,aux,'|')) v.push_back(aux);
    return v.size();
  }
  template<typename TContainer>
  string container2string(const TContainer &v) {
    string s, d(1,'|');
    for(const auto &x:v)
      s += (s.empty()?string(""):d)+x;
    return s;
  }
  
  string get_first(const string &pair) {
    size_t pos = pair.find(':');
    return pair.substr(0,pos);
  }
  string get_second(const string &pair) {
    size_t pos = pair.find(':');
    return pair.substr(pos+1);
  }
  
  
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> HAY CAMINO
  
  typedef bool (*hay_camino_t)(map<string,list<string> > &M, list<string> &P, string cini, string cfin);
  class eval2_t : public eval_base_t {
  public:
    hay_camino_t F;
    eval2_t() { dumptests=0; F=NULL; ejerc=2; testfile="./piquetes.json"; }
    void run_case(json &data,json &outuser) {
      
      vector<string> vcities;  string2container(vcities,data["cities"]); // ciudades
      map<string,list<string> > M; for(auto city:vcities) M[city]; // grafo sin arcos
      vector<string> vconns; string2container(vconns,data["conns"]); // arcos
      for(auto &pair : vconns) {
        string city1 = get_first(pair), city2 = get_second(pair);
        M[city1].push_back(city2); M[city2].push_back(city1);
      }
      
      list<string> vpiquets; string2container(vpiquets,data["piquets"]); // piquetes
      string cini = data["cini"], cend = data["cfin"]; // origen y destino
      
      bool ret = F(M,vpiquets,cini,cend);
      outuser["ret"] = ret?1:0;
      
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      static vector<string> ciudades = { 
        "Santa Fe","Buenos Aires","Rosario","Rafaela","Cordoba",
        "Parana","Mar del Plata","Salta","Carlos Paz","Bariloche",
        "Mendoza","Colon","Santo Tome","Esmeralda" };
      // ciudades
      vector<string> vcities;
      do {
        vcities.clear();
        for(auto &city:ciudades) if(rnd.rand()%3) vcities.push_back(city);
      } while ( vcities.size()<5 );
      // arcos
      vector<string> vconns;
      for(size_t i=0;i<vcities.size()-1;i++) { 
        for(size_t j=i+1;j<vcities.size();j++) {
          if (rnd.rand()%4==0) vconns.push_back(vcities[i]+":"+vcities[j]);
        }
      }
      // origen  y destino
      string cini = vcities[rnd.rand()%vcities.size()], cfin;
      do { cfin = vcities[rnd.rand()%vcities.size()]; } while (cini==cfin);
      // piquetes
      vector<string> vpiquets;
      for(auto &city:vcities) if (city!=cini&&city!=cfin&&rnd.rand()%3==0) vpiquets.push_back(city);
      // json
      datain["cities"] = container2string(vcities);
      datain["conns"] = container2string(vconns);
      datain["piquets"] = container2string(vpiquets);
      datain["cini"] = cini; datain["cfin"] = cfin;
    }
  };
  
  
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*> ENHANCE HTML
  
  typedef void (*enhance_html_t)(tree<string> &T);
  class eval3_t : public eval_base_t {
  public:
    enhance_html_t F;
    eval3_t() { dumptests=0; F=NULL; ejerc=3; testfile="./html.json"; }
    void run_case(json &data,json &outuser) {
      string stree = data["tree"];
      tree<string> T;
      lisp2tree(stree,T);
      F(T);
      outuser["tree"] = lisp_print(T);
    }

    int check_case(json &datain,
                   json &outref,json &outuser) {
      return outref==outuser;
    }
    
    void fill_tree(tree<string> &T, tree<string>::iterator &it, int deep, randomg_t &rnd) {
      static vector<string> tags = { "h1","ul","ol","img","div","span","table","strong" };
      int nc = rnd.rand()%5;
      if (nc==0) return;
      for(int i=0;i<nc;i++) { 
        if (deep==0 && rnd.rand()%3==0) {
          T.insert(it.lchild(),"a");
        } else if (deep==1 && rnd.rand()%3==0) {
          auto aux = T.insert(it.lchild(),"strong");
          T.insert(aux.lchild(),"a");
        } else {
          auto aux = T.insert(it.lchild(),tags[rnd.rand()%tags.size()]);
          if (deep) fill_tree(T,aux,deep-1,rnd);
        }
      }
    }
    
    void generate_case(randomg_t &rnd,json &datain) {
      tree<string> T; T.insert(T.begin(),"html"); 
      auto it = T.begin().lchild(); it = T.insert(it,"body");
      int max_deep = 2+rnd.rand()%3;
      fill_tree(T,it,max_deep,rnd);
      datain["tree"] = lisp_print(T);
    }
  };

  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  using Eval = eval_t<eval1_t,unordered_equal_t,
                      eval2_t,hay_camino_t,
                      eval3_t,enhance_html_t>;
}
#undef CSTR

#endif
