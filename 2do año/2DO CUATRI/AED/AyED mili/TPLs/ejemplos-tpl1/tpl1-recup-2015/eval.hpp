// GITVERSION: tpl1-recup-2015-33-ge65b368
#ifndef EVAL_HPP
#define EVAL_HPP

#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tree.hpp"
#include "util_tree.hpp"
#include "btree.hpp"
#include "util_btree.hpp"
using namespace std;

namespace aed {

  // Simple hasher class for the examples
  class hasher_t  {
  private:
    // BJ hash (Bob Jenkins). From
    // http://www.chasanc.com/old/hashing_func.htm
    typedef uint32_t u4; /* unsigned 4-byte type */
    typedef uint8_t u1;   /* unsigned 1-byte type */
    u4 state;

    /* The mixing step */
#define mix(a,b,c)                              \
    {                                           \
      a=a-b;  a=a-c;  a=a^(c>>13);              \
      b=b-c;  b=b-a;  b=b^(a<<8);               \
      c=c-a;  c=c-b;  c=c^(b>>13);              \
      a=a-b;  a=a-c;  a=a^(c>>12);              \
      b=b-c;  b=b-a;  b=b^(a<<16);              \
      c=c-a;  c=c-b;  c=c^(b>>5);               \
      a=a-b;  a=a-c;  a=a^(c>>3);               \
      b=b-c;  b=b-a;  b=b^(a<<10);              \
      c=c-a;  c=c-b;  c=c^(b>>15);              \
    }

    /* The whole new hash function */
    u4 bjhash(register u1* k,u4 length, u4 initval)
    // register u1 *k;        /* the key */
    // u4           length;   /* the length of the key in bytes */
    // u4           initval;  /* the previous hash, or an arbitrary value */
    {
      register u4 a,b,c;  /* the internal state */
      u4          len;    /* how many key bytes still need mixing */

      /* Set up the internal state */
      len = length;
      a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
      c = initval;         /* variable initialization of internal state */

      /*---------------------------------------- handle most of the key */
      while (len >= 12)
        {
          a=a+(k[0]+((u4)k[1]<<8)+((u4)k[2]<<16) +((u4)k[3]<<24));
          b=b+(k[4]+((u4)k[5]<<8)+((u4)k[6]<<16) +((u4)k[7]<<24));
          c=c+(k[8]+((u4)k[9]<<8)+((u4)k[10]<<16)+((u4)k[11]<<24));
          mix(a,b,c);
          k = k+12; len = len-12;
        }

      /*------------------------------------- handle the last 11 bytes */
      c = c+length;
      switch(len)              /* all the case statements fall through */
        {
        case 11: c=c+((u4)k[10]<<24);
        case 10: c=c+((u4)k[9]<<16);
        case 9 : c=c+((u4)k[8]<<8);
          /* the first byte of c is reserved for the length */
        case 8 : b=b+((u4)k[7]<<24);
        case 7 : b=b+((u4)k[6]<<16);
        case 6 : b=b+((u4)k[5]<<8);
        case 5 : b=b+k[4];
        case 4 : a=a+((u4)k[3]<<24);
        case 3 : a=a+((u4)k[2]<<16);
        case 2 : a=a+((u4)k[1]<<8);
        case 1 : a=a+k[0];
          /* case 0: nothing left to add */
        }
      mix(a,b,c);
      /*-------------------------------------------- report the result */
      return c;
    }


  public:
    hasher_t() { reset(); }
    void reset() { state = 0L; }
    void hash(vector<int> w) { hash(&w[0],w.size()); }
    void hash(list<int> &L) {
      list<int>::iterator q = L.begin();
      while (q!=L.end()) hash(*q++);
    }
    void hash(set<int> &S) {
      set<int>::iterator q = S.begin();
      while (q!=S.end()) hash(*q++);
    }
    void hash(vector< list<int> > &VL) {
      int N = VL.size();
      for (int j=0; j<N; j++) {
        list<int> &L = VL[j];
        hash(L.size());
        hash(L);
      }
    }

    void hash(int w) {
      state = bjhash((u1*)&w,sizeof(int),state);
    }

    void hash(int *w,int n) {
      for (int j=0; j<n; j++) hash(w[j]);
    }

    uint64_t val() {
      return state;
    }


  };

  // Simple random generator class for the examples
  class randomg_t  {
  private:
    hasher_t hasher;
    uint64_t state;
  public:
    randomg_t() { reset(0); }
    void reset(uint64_t seed=0) { hasher.reset(); state=seed; }
    uint64_t rand() { 
      hasher.hash(state++); 
      return hasher.val();
    }
  };
  
  //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
  class Eval {

  public:
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(list<int> &L,string s="") {
      cout << s;
      if (s!="") cout << ": ";
      list<int>::iterator q = L.begin();
      while (q!=L.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(vector<int> &V,string s="") {
      cout << s; 
      vector<int>::iterator q = V.begin();
      while (q!=V.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(vector< list<int> > &VL,string s="") {
      int N = VL.size();
      // cout << "vector length " << N << endl;
      for (int j=0; j<N; j++) {
        cout << s << "[" << j << "]: ";
        dump(VL[j]);
      }
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(list< list<int> > &LL,string s="") {
      list< list<int> >::iterator p= LL.begin();
      int j=0;
      while (p!=LL.end()) {
        list<int> &L = *p++;
        cout << s << "[" << j++ << "]: ";
        dump(L);
      }
    }
    
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(set<int> &S,string s="") {
      cout << s; 
      set<int>::iterator q = S.begin();
      while (q!=S.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(vector< set<int> > &VS,string s="") {
      int N = VS.size();
      for (int j=0; j<N; j++) {
        cout << s << "[" << j << "]: ";
        dump(VS[j]);
      }
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(map<int,int> &M,string s="") {
      cout << s << endl; 
      map<int,int>::iterator itm = M.begin();
      while (itm != M.end()){
        cout << "M[" << itm->first <<"] = "<< itm->second << endl;
        itm++;
      }
      cout << endl;
    }

    static void dump(map<int, list<bool> >& M,string s="M") {
      cout << s << " = {";
      map<int, list<bool> >::iterator p = M.begin();
      while (p!=M.end()) {
        cout << p->first << "->[";
        list<bool> &L = p->second;
        list<bool>::iterator q = L.begin();
        while (q!=L.end()) {
          cout << (*q ? "true" : "false");
          q++;
          if (q!=L.end()) cout << ", ";
        }
        cout << "]";
        p++;
        if (p!=M.end()) cout << ", ";
      }
      cout << "}" << endl;
    }

  private:
    list< list<int> > colas(list<int> &L) {
      list< list<int> > R;
      if (L.empty()) return R;
      list<int>::iterator it = L.begin();
      while (it != L.end()) {
        R.push_back(list<int>(it, L.end()));
        ++ it;
      }

      return R;
    }

    // Retorna todos los elementos de la lista
    // e.g.: "1 2 3 4 3 2 1" -> (1 2 3 4 3 2 1)
    void s2l(string s, list<int> &L) {
      istringstream is(s);
      int n;
      while (is >> n)
        L.push_back(n);
    }

    void s2v(string s, vector<int> &V) {
      istringstream is(s);
      int n;
      while (is >> n) V.push_back(n);
    }

    void prl(list<int> &L) {
      if (L.empty()) return;
      list<int>::iterator il = L.begin();
      for (; &*il != &*L.rbegin(); il ++)
        cout << *il << " ";
      cout << *il;
    }


    void s2m(string s, map<int, list<bool> > &M) {
      M.clear();
      istringstream is(s);

      int k, n, v;
      while (is >> k >> n) {
        list<bool> L;

        for (int i = 0 ; i < n ; i ++) {
          is >> v;
          L.push_back(v);
        }
        M[k] = L;
      }
    }

    void s2m(string s, map<int, list<int> > &M) {
      M.clear();
      istringstream is(s);
      int k, n, v;
      while (is >> k >> n) {
        list<int> L;
        for (int i = 0 ; i < n ; i ++) {
          is >> v;
          L.push_back(v);
        }
        M[k] = L;
      }
    }

    void s2m(string s, map<int, int> &M) {
      M.clear();
      istringstream is(s);
      int k, n;
      while (is >> k >> n) {
        M[k] = n;
      }
    }

    // string -> vector de listas
    // (n1 L1 n2 L2 ...)
    // "3 1 2 3 4 5 4 3 2"  -> [(1 2 3) (5 4 3 2)]
    void s2vl(string s, vector< list<int> > &v) {
      istringstream is(s);
      int n1, n2;
      while (is >> n1) {
        v.push_back(list<int>());
        for (int i = 0 ; i < n1 ; i ++) {
          is >> n2;
          v.back().push_back(n2);
        }
      }
    }

    string l2s(list<int> &L) {
      ostringstream os;
      list<int>::iterator q = L.begin();
      while (q!=L.end()) os << *q++ << " ";
      return os.str();
    }

    string ll2s(list< list<int> > &LL) {
      ostringstream os;
      list< list<int> >::iterator p=LL.begin();
      while (p!=LL.end()) {
        list<int> &L = *p++;
        os << L.size() << " " << l2s(L) << " ";
      }
      return os.str();
    }

    void s2ll(string s, list< list<int> > &ll) {
      ll.clear();
      vector< list<int> > vl;
      s2vl(s,vl);
      int N = vl.size();
      for (int j=0; j<N; j++) ll.push_back(vl[j]);
    }

    void s2vs(string s, vector< set<int> > &v) {
      istringstream is(s);
      int n1, n2;
      while (is >> n1) {
        v.push_back(set<int>());
        for (int i = 0 ; i < n1 ; i ++) {
          is >> n2;
          v.back().insert(n2);
        }
      }
    }

    string vs2s(vector< set<int> > &VS) {
      ostringstream os;
      int NS = VS.size();
      for (int j=0; j<NS; j++) 
        os << VS[j].size() << " " << set2str(VS[j]) << " ";
      return os.str();
    }

    string set2str(set<int> &S) {
      ostringstream os;
      set<int>::iterator q = S.begin();
      while (q!=S.end()) os << *q++ << " ";
      return os.str();
    }

    void acum_hasta(list<int> &L, int n) {
      int acum = 0;
      list<int>::iterator it = L.begin();
      while (it != L.end()) {
        acum += *it;
        it = L.erase(it);
        if (acum >= n) {
          L.insert(it, acum);
          acum = 0;
        }
      }
      if (acum > 0) L.push_back(acum);
    }

    int readnum(string &s, unsigned int &n) {
      int k = 0;
      bool negativo = false;
      if (s[n] == '-') {
        negativo = true;
        n ++;
      }

      while (s[n] >= '0' && s[n] <= '9') {
        k *= 10;
        k += s[n] - '0';
        ++ n;
      }
      if (negativo) k *= -1;
      return k;
    }

    void lisp2tree(string s, tree<int> &T, unsigned int &i, 
                   tree<int>::iterator it) {
      while (i < s.size()) {
        while (s[i] == ' ') ++ i;
        
        if (s[i] == '(') {
          ++ i;
          while (s[i] == ' ') ++ i;
          it = T.insert(it, readnum(s, i));
          lisp2tree(s, T, i, it.lchild());
          ++ it;
        } else if (s[i] == ')') {
          ++ i;
          return;
        } else {
          it = T.insert(it, readnum(s, i));
          ++ it;
        }
      }
    }

    void preorder(tree<int> &T,tree<int>::iterator n,list<int> &L) {
      L.insert(L.end(),*n);
      tree<int>::iterator c = n.lchild();
      while (c!=T.end()) {
        preorder(T,c,L);
        c = c.right();
      }
    }

    void preorder(tree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      preorder(T,T.begin(),L);
    }

    void postorder(tree<int> &T,tree<int>::iterator n,list<int> &L) {
      tree<int>::iterator c = n.lchild();
      while (c!=T.end()) {
        postorder(T,c,L);
        c = c.right();
      }
      L.insert(L.end(),*n);
    }

    void postorder(tree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      postorder(T,T.begin(),L);
    }

    void lisp2btree(string s, btree<int> &T, unsigned int &i, 
                    btree<int>::iterator it) {
      while (i < s.size()) {
        while (s[i] == ' ') ++ i;

        if (s[i] == '(') {
          ++ i;
          it = T.insert(it, readnum(s, i));

          lisp2btree(s, T, i, it.left());
          lisp2btree(s, T, i, it.right());
        } else if (s[i] == ')' || s[i] == '.') {
          ++ i;
          return;
        } else {
          T.insert(it, readnum(s, i));
          return;
        }
      }
    }

    void lisp2btree(string s, btree<int> &T) {
      unsigned int i = 0;
      lisp2btree(s, T, i, T.begin());
    }

    void preorder(btree<int> &T,btree<int>::iterator n,list<int> &L) {
      if(n==T.end()) return;
      L.insert(L.end(),*n);
      preorder(T,n.left(),L);
      preorder(T,n.right(),L);
    }

    void preorder(btree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      preorder(T,T.begin(),L);
    }

    void postorder(btree<int> &T,btree<int>::iterator n,list<int> &L) {
      if(n==T.end()) return;
      postorder(T,n.left(),L);
      postorder(T,n.right(),L);
      L.insert(L.end(),*n);
    }

    void postorder(btree<int> &T,list<int> &L) {
      if (T.begin()==T.end()) return;
      postorder(T,T.begin(),L);
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void make_random_btree(btree<int> &t,btree<int>::iterator n,
                           int m,int level,double siblings,
                           randomg_t &rnd) {
      btree<int>::iterator c;
      double lambda,nivel;
      n=t.insert(n,rnd.rand()%m);
      nivel=double(level);
      lambda = 1.0/(siblings/nivel+1.0);
      for (int j=0;j<2;j++) {
        if  (j==0) {
          c=n.left();}
        else {
          c=n.right();
        }
        unsigned int MAX = 100000;
        double x = double(rnd.rand()%MAX)/MAX;
        if (x>lambda) make_random_btree(t,c,m,level+1,siblings,rnd);
      }
    }

    // -----------------------------------------------------------------
    void make_random_btree(btree<int> &t,int m,double siblings,
                           randomg_t &rnd) {
      t.clear();
      make_random_btree(t,t.begin(),m,0,siblings,rnd);
    } 

    void hash(hasher_t &hasher,tree<int> &T) {
      list<int> L;
      preorder(T,L);
      list<int>::iterator q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);

      L.clear();
      postorder(T,L);
      q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);
    }

    void hash(hasher_t &hasher,btree<int> &T) {
      list<int> L;
      preorder(T,L);
      list<int>::iterator q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);

      L.clear();
      postorder(T,L);
      q=L.begin();
      while (q!=L.end()) hasher.hash(*q++);
    }

    void hash(hasher_t &hasher,set<int> &S) {
      set<int>::iterator q = S.begin();
      while (q!=S.end()) hasher.hash(*q++);
    }

  public:

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    // Makes a random tree with `s' siblings and `m' nodes.
    // The value at the node is in [0,M)
    void make_random_tree2(tree<int> &T,tree<int>::iterator n,
                           int M, int m,int s,
                           randomg_t &rnd) {
      if (!m) return;
      // Toma los m nodos y los divide en `ss' siblings donde s es aleatorio
      // en [1,s]
      int ss = rnd.rand()%s+1;
      // Inserta un nodo en la raiz
      n = T.insert(n,rnd.rand()%M);
      m--; // toma en cuenta que ya inserto 1
      // Reparte los nodos que quedan aleatoriamente en los ss hijos
      vector<int> v(ss,0);
      for (int j=0; j<m; j++) v[rnd.rand()%ss]++;
      // A esta altura tenemos un vector v[] con s enteros
      // cuya suma es `m'.  Algunos pueden ser nulos, pero no importa
      // porque en ese caso la llamada recursiva no va a hacer nada. 
      for (unsigned int j=0; j<v.size(); j++) 
        make_random_tree2(T,n.lchild(),M,v[j],s,rnd);
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    // Wrapper
    void make_random_tree2(tree<int> &T,int M, int m,int s,
                           randomg_t &rnd) {
      T.clear();
      make_random_tree2(T,T.begin(),M,m,s,rnd);
    }

    void lisp2tree(string s, tree<int> &T) {
      unsigned int i = 0;
      lisp2tree(s, T, i, T.begin());
    }

    const char *i2s(int ok) { return (ok ? "OK" : "MAL"); }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    // BEGIN EVALUACION DE FUNCIONES USUARIO
#define CONCAT(a,b) a##b
#define VERJ(J) CONCAT(verificar,J)
#define EVALJ(J) CONCAT(eval,J)
#define EVALRJ(J) CONCAT(evalr,J)
#define STR(n) #n

    //---:---<*>---: START EJERC 1 ---<*>---:---<*>---:---<*>---:---<*>
#undef VERFUN
#undef EVFUN
#undef EVRFUN
#undef SEJERC
#define EJERC 1
#define VERFUN VERJ(EJERC)
#define EVFUN EVALJ(EJERC)
#define EVRFUN EVALRJ(EJERC)
#define SEJERC STR(1)

    void map2count(list<int> &L,map<int,int> &M) {
      M.clear();
      list<int>::iterator p=L.begin();
      while (p!=L.end()) M[*p++]++;
    }
    
    typedef list<int> (*mochila_t)(list<int> &P, int M);
#undef FUNC_T
#define FUNC_T mochila_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sP,
                int K,
                int Nmochiref,
                int vrbs=0) {

      list<int> P,Pu,Muser;
      s2l(sP,P);
      Pu = P;
      Muser = F(Pu,K);
      // Chequear que los elementos de Muser
      // esten en P
      int OKcont=1;
      {
        map<int,int> Mmochiuser,ML;
        map2count(Muser,Mmochiuser);
        map2count(P,ML);
        map<int,int>::iterator p = Mmochiuser.begin();
        while (p!=Mmochiuser.end()) {
          int elem = p->first, count= p->second;
          if (ML[elem]<count) { OKcont=0; break; }
          p++;
        }
      }
      
      int ok = (OKcont && int(Muser.size())==Nmochiref);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(P,"P");
        dump(Muser,"M(user)");
        cout << "K " << K << endl;
        cout << "mochila(user) contenida en P: " << i2s(OKcont) << endl;
        cout << "elementos en mochila (user): " << Muser.size() << endl;
        cout << "elementos en mochila (ref): " << Nmochiref << endl;
      }
      caso++;
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso" 
             << caso << ". Estado: " << i2s(ok) << endl;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0) {
      cout << "----------------\nEvaluando ejercicio " 
        STR(EJERC) << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(Lmu,K,Nref) VERFUN(caso,ok,F,Lmu,K,Nref,vrbs)
      VERF("3 2 7 11 2 5 9 4",11,4);
      VERF("3 2 7 11 2 5 9 4",10,3);
      VERF("3 2 7 11 2 5 9 4",12,4);
#include "./ver1.hpp"
      
      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0) {
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejerc " SEJERC ". Caso %d\n",caso);
        int N=10+rnd.rand()%10, ME=10;
        list<int> P,M;
        for (int j=0; j<N; j++)
          P.push_back(1+rnd.rand()%ME);
        int K = rnd.rand()%(ME*N/4);
        M = F(P,K);
        int Nmochi = M.size();
        if (0) {
          printf("V1(\"");
          dump(P);
          printf("\",");
          printf("%d,%d);\n",K,Nmochi);
        }
        hasher.hash(Nmochi);
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ" SEJERC ": SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }
    //---:---<*>---: END EJERC 1 ---<*>---:---<*>---:---<*>---:---<*>

    //---:---<*>---: START EJERC 2 ---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef VERFUN
#undef EVFUN
#undef EVRFUN
#undef SEJERC
#define EJERC 2
#define VERFUN VERJ(EJERC)
#define EVFUN EVALJ(EJERC)
#define EVRFUN EVALRJ(EJERC)
#define SEJERC STR(2)

    typedef bool (*enunosolo_t)(list<list <int> > &LL, list<int> &L);
#undef FUNC_T
#define FUNC_T enunosolo_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sLL,
                string sL,
                int rvref,
                int vrbs=0) {

      list< list<int> > LL,LLu;
      list<int> L,Lu;
      s2ll(sLL,LL);
      s2l(sL,L);
      
      LLu = LL;
      Lu = L;
      int rvuser = F(LLu,Lu);
      
      int ok = (rvuser==rvref);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(LL,"LL");
        dump(L,"L");
        cout << "retval(user) " << rvuser << endl;
        cout << "retval(ref) " << rvref << endl;
      }
      caso++;
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso" 
             << caso << ". Estado: " << i2s(ok) << endl;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0) {
      cout << "----------------\nEvaluando ejercicio " 
        SEJERC << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(LL,L,rv) VERFUN(caso,ok,F,LL,L,rv,vrbs)
      VERF("4 1 2 3 4 4 1 2 3 5 4 1 2 3 6","6 5 4",1);
      VERF("4 1 2 3 4 4 1 2 3 5 4 1 2 3 6","6 5",1);
      VERF("4 1 2 3 4 4 1 2 3 5 4 1 2 3 6","6 5 1",0);
      VERF("4 1 2 3 4 4 1 2 3 5 4 1 2 3 6","6 5 3",0);
      VERF("4 1 2 3 4 4 1 2 3 5 4 1 2 3 6","6 5 3 7",0);
#include "./ver2.hpp"
      
      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0) {
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejerc " SEJERC ". Caso %d\n",caso);
        // Nbr of lists
        int N=5+rnd.rand()%5;
        list< list<int> > LL;
        list<int> L;
        set<int> S;
        int M2 = 200;
        for (int j=0; j<N; j++) {
          int NL = 5+rnd.rand()%5;
          list<int> Lj;
          for (int j=0; j<NL; j++)
            Lj.push_back(rnd.rand()%M2);
          int m = rnd.rand()%M2;
          Lj.push_back(m);
          LL.push_back(Lj);
          S.insert(m);
          L.push_back(m);
        }
        vector<int> aux(S.size());
        copy(S.begin(),S.end(),aux.begin());
        random_shuffle(rnd,aux);
        v2l(aux,L);
        int rvuser = F(LL,L);
        if (0) {
          string sLL = ll2s(LL);
          string sL = l2s(L);
          printf("VERF(\"%s\",\"%s\",%d);\n",
                 sLL.c_str(),sL.c_str(),rvuser);
        }
        hasher.hash(rvuser);
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ" SEJERC ": SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }

    //---:---<*>---: END EJERC 2 ---<*>---:---<*>---:---<*>---:---<*>

    //---:---<*>---: START EJERC 3 ---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef VERFUN
#undef EVFUN
#undef EVRFUN
#undef SEJERC
#define EJERC 3
#define VERFUN VERJ(EJERC)
#define EVFUN EVALJ(EJERC)
#define EVRFUN EVALRJ(EJERC)
#define SEJERC STR(3)

    typedef int (*ppt_t)(list<int> &H, int n);
#undef FUNC_T
#define FUNC_T ppt_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sH,
                int n,
                int rvref,
                int vrbs=0) {

      list<int> H,Hu;
      s2l(sH,H);
      Hu = H;
      int rvuser = F(Hu,n);
      
      int ok = (rvuser==rvref);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(H,"H");
        cout << "n: " << n <<endl;
        cout << "retval(user) " << rvuser << endl;
        cout << "retval(ref) " << rvref << endl;
      }
      caso++;
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso" 
             << caso << ". Estado: " << i2s(ok) << endl;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0) {
      cout << "----------------\nEvaluando ejercicio " 
        SEJERC << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(H,n,rv) VERFUN(caso,ok,F,H,n,rv,vrbs)
      VERF("1 1 2 2 1 2 3 3 2 1 2 3 1 2",2,3);
      VERF("1 3 1 2 2 1 2 3 3 2 1 2 3 1 2",3,2);
      VERF("1 3 1 2 2 1 2 3 2 2 1 1 2 2 1 1 2 2 1",3,1);
#include "./ver3.hpp"
      
      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0) {
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejerc " SEJERC ". Caso %d\n",caso);
        // Nbr of plays
        int N=20+rnd.rand()%10;
        list<int> H;
        for (int j=0; j<N; j++) H.push_back(1+rnd.rand()%3);
        int n = 2+rnd.rand()%4;
        int rvuser = F(H,n);
        if (0) {
          string sH = l2s(H);
          printf("VERF(\"%s\",%d,%d);\n",
                 sH.c_str(),n,rvuser);
        }
        hasher.hash(rvuser);
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ" SEJERC ": SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }
    //---:---<*>---: END EJERC 3 ---<*>---:---<*>---:---<*>---:---<*>
    
    // END EVALUACION DE FUNCIONES USUARIO
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
        
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(stack<int> S,string s="") {
      cout << s; 
      while (!S.empty()){
        cout << S.top() << " ";
        S.pop();
      }
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    static void dump(queue<int> Q,string s="") {
      cout << s; 
      while (!Q.empty()){
        cout << Q.front() << " ";
        Q.pop();
      }
      cout << endl;
    }
	
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void s2sta(string s, stack<int> &S){
      istringstream is(s);
      int n;
      while (is >> n)
        S.push(n);
    }
	
    void random_shuffle(randomg_t &rnd,vector<int> &v,int k1,int k2) {
      int n = k2-k1;
      if (n<=1) return;
      int n1 = n/2, n2 = n-n1, j1=k1, j2=k1+n1;
      this->random_shuffle(rnd,v,k1,j2);
      this->random_shuffle(rnd,v,j2,k2);
      vector<int> w;
      while (n1 || n2) {
        int choose1 = int(rnd.rand()%(n1+n2))<n1;
        if (choose1) { w.push_back(v[j1++]); n1--; }
        else { w.push_back(v[j2++]); n2--; }
      }
      for (int j=0; j<n; j++) v[k1+j] = w[j];
    }

    void random_shuffle(randomg_t &rnd,vector<int> &v) {
      this->random_shuffle(rnd,v,0,v.size());
    }

    void l2v(const list<int> &L,vector<int> &v) {
      v.clear();
      list<int>::const_iterator p = L.begin();
      while (p!=L.end()) v.push_back(*p++);
    }

    void v2l(const vector<int> &v, list<int> &L) {
      L.clear();
      int N = v.size();
      for (int j=0; j<N; j++) L.push_back(v[j]);
    }
    
    void random_shuffle(randomg_t &rnd,list<int> &L) {
      vector<int> v;
      l2v(L,v);
      random_shuffle(rnd,v);
      v2l(v,L);
    }
  };

}

#endif
