// GITVERSION: parc1-2015-76-g3da893d
#ifndef EVAL_HPP
#define EVAL_HPP

#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#ifdef USECHRONO
#include <sys/time.h>
#endif
#include <math.h>
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

#define CSTR(s) (s).c_str()
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
    uint64_t hash(vector<int> w) { hash(&w[0],w.size()); return state; }
    uint64_t hash(list<int> &L) {
      list<int>::iterator q = L.begin();
      while (q!=L.end()) hash(*q++);
      return state;
    }
    uint64_t hash(set<int> &S) {
      set<int>::iterator q = S.begin();
      while (q!=S.end()) hash(*q++);
      return state;
    }
    uint64_t hash(vector< list<int> > &VL) {
      int N = VL.size();
      for (int j=0; j<N; j++) {
        list<int> &L = VL[j];
        hash(L.size());
        hash(L);
      }
      return state;
    }

    uint64_t hash(int w) {
      state = bjhash((u1*)&w,sizeof(int),state);
      return state;
    }

    uint64_t hash(int *w,int n) {
      for (int j=0; j<n; j++) hash(w[j]);
      return state;
    }

    // This is not completely bullet proof but it mixes the
    // pre and post order, so that two trees that have the
    // same preorder don't have the same hash. Hashes the
    // node before and after the childs. 
    void hash(tree<int> &T,tree<int>::iterator n) {
      if (n==T.end()) return;
      hash(*n);
      tree<int>::iterator c=n.lchild();
      while (c!=T.end()) hash(*c++);
      hash(*n);
    }

    uint64_t hash(tree<int> &T) {
#if 0
      // Hashes a tree. Since there is a univoque
      // relation between the tree and its (pre+post) order
      // then we build them and hash them. Doesn't work
      // because preorder is defined in Eval
      list<int> L;
      preorder(T,L); hash(L);
      postorder(T,L); hash(L);
#endif
      hash(T,T.begin());
      return state;
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

  class chrono_t {
    double gettod() const {
#ifdef USECHRONO
      struct timeval tv;
      gettimeofday(&tv,0);
      return tv.tv_sec + 1e-6 * tv.tv_usec;
#else
      return NAN;
#endif
    }
  private:
    /// structures for `libc' time function calls.
    double start_time;
    double elaps;
    int active;
  public:
    chrono_t() { reset(); }
    /// return elapsed CPU time from start
    double elapsed() const {return elaps;};
    /// reset start time to actual time
    void reset() { elaps=0.0; active=0; };
    void start() { start_time = gettod(); active=1; }
    double stop() {
      if (active) {
        elaps += gettod()-start_time;
        active=0;
      }
      return elaps;
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

    template<class T>
    static void dump(map<int, list<T> >& M,string s="M") {
      cout << s << " = {";
      typename map<int, list<T> >::iterator p = M.begin();
      while (p!=M.end()) {
        cout << p->first << "->[";
        list<T> &L = p->second;
        typename list<T>::iterator q = L.begin();
        while (q!=L.end()) {
          // cout << (*q ? "true" : "false");
          cout << *q;
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

    string g2s(map<int, list<int> > &G) {
      ostringstream os;
      map<int, list<int> >::iterator p=G.begin();
      while (p!=G.end()) {
        list<int> &L = p->second;
        os << p->first << " " << L.size() << " " << l2s(L) << "   ";
        p++;
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

    string lisp_print(tree<int> &T,tree<int>::iterator n) {
      ostringstream os;
      if (n==T.end()) return "";
      tree<int>::iterator c = n.lchild();
      bool is_leaf = c==T.end();
      if (is_leaf) os << *n;
      else {
	os << "(" << *n;
	while (c!=T.end()) {
	  os << " ";
	  os << lisp_print(T,c++);
	}
	os << ")";
      }
      return os.str();
    }
    // -------------------------------------------------------------
    string lisp_print(tree<int> &T) { return lisp_print(T,T.begin()); }
    
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

    double bogomips() {
      randomg_t rnd;
      int N=100000000;
      chrono_t chrono;
      chrono.start();
      for (int j=0; j<N; j++) rnd.rand();
      chrono.stop();
      double elapsed = chrono.elapsed();
      // printf("elapsed %f\n",elapsed);
      double refelapsed = 2.6119; // In my laptop
      return refelapsed/elapsed;
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
#undef EJERC
#undef VERFUN
#undef EVFUN
#undef EVRFUN
#undef SEJERC
#define EJERC 1
#define VERFUN VERJ(EJERC)
#define EVFUN EVALJ(EJERC)
#define EVRFUN EVALRJ(EJERC)
#define SEJERC STR(1)


    typedef void (*getpath_t)(map<int,list<int> > &M,
                         int vrtx, list<int> &path);
#undef FUNC_T
#define FUNC_T getpath_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sM,
                int v,
                string spathref,
                int vrbs=0,int ucase=-1) {
      if (ucase>=0 && ucase!=caso) { caso++; return; }

      list<int> pathref,pathuser;
      map<int,list<int> > M,Muser;
      s2m(sM,M);
      s2l(spathref,pathref);
      Muser=M;
      F(Muser,v,pathuser);
      
      int ok = (pathref==pathuser);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(M,"M");
        cout << "vrtx " << v << endl;
        dump(pathuser,"path(user): ");
        dump(pathref,"path(ref): ");
      }
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso " 
             << caso << ". Estado: " << i2s(ok) << endl;
      caso++;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0,int ucase=-1) {
      cout << "----------------\nEvaluando ejercicio " 
        STR(EJERC) << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(M,v,p) VERFUN(caso,ok,F,M,v,p,vrbs,ucase)
      VERF("0 1 1  1 3 3 0 2  2 2 1 3  3 3 1 4 2  4 1 3  ",3,"3 1 0 ");
      VERF("0 1 1  1 3 3 0 2  2 2 1 3  3 3 1 4 2  4 1 3  ",0,"0 1 3 4");
      VERF("0 1 1  1 3 3 0 2  2 2 1 3  3 3 1 4 2  4 1 3  ",1,"1 3 4");
      VERF("0 1 1  1 3 3 0 2  2 2 1 3  3 3 1 4 2  4 1 3  ",2,"2 1 3 4");
      VERF("0 1 1  1 3 3 0 2  2 2 1 3  3 3 1 4 2  4 1 3  ",4,"4 3 1 0");
      VERF("0 2 1 3 1 2 0 2 2 2 1 3 3 2 0 2",0,"0 1 2 3");
#include "./ver1.hpp"
      
      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0) {
      int hardness=0;
      double mips = NAN;
      if (hardness==5) mips=bogomips();
      int ncasos=50;
      double facmax=10000, fac = pow(facmax,hardness/5.0);
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      chrono_t chrono;

      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2 && !hardness) printf("Ejerc " SEJERC ". Caso %d\n",caso);
        int N = 5*fac; // graph has N vertices
        map<int,set<int> > MS;
        map<int,list<int> > M;
        list<int> path;
        // Each vrtx is connected to the next.
        // 50% of the vertices are connected to j+2
        for (int j=0; j<N-1; j++) {
          MS[j].insert(j+1);
          MS[j+1].insert(j);
        }

        for (int j=0; j<N-2; j++) {
          if (rnd.rand()%2) {
            MS[j].insert(j+2);
            MS[j+2].insert(j);
          }
        }

        // Convert to list and shuffle
        for (int j=0; j<N; j++) {
          list<int> &L = M[j];
          L.insert(L.begin(),MS[j].begin(),MS[j].end());
          random_shuffle(rnd,L);
        }
        
        int vrtx = rnd.rand()%N;
        F(M,vrtx,path);
        if (0) {
          string
            m = g2s(M),
            p = l2s(path);
          printf("VERF(\"%s\",%d,\"%s\");\n",
                 m.c_str(),vrtx,p.c_str());
        }
        hasher.hash(path);
      }
      if (hardness) {
        cout << "EJ" SEJERC ". Hardness "
             << hardness << ", elapsed " << chrono.elapsed() << "[s]";
        if (hardness==5) 
          cout << " (mips " << mips << ", relative "
               << chrono.elapsed()/mips << "[s])";
        cout << endl;
      }
      int H = hasher.val()%1000;
      if (vrbs && !hardness)
        printf("EJ" SEJERC ": SEED=%03d, HASH=%03d\n",seed,H);
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

    typedef int (*tricount_t)(map<int,list<int> > &M);
#undef FUNC_T
#define FUNC_T tricount_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sM,
                int vref,
                int vrbs=0,int ucase=-1) {
      if (ucase>=0 && ucase!=caso) { caso++; return; }

      map<int,list<int> > M,Muser;
      s2m(sM,M);
      Muser = M;
      int vuser = F(Muser);
      
      int ok = (vuser==vref);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(M,"M");
        cout << "ntri(user) " << vuser << endl;
        cout << "ntri(ref) " << vref << endl;
      }
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso " 
             << caso << ". Estado: " << i2s(ok) << endl;
      caso++;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0,int ucase=-1) {
      cout << "----------------\nEvaluando ejercicio " 
        STR(EJERC) << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(M,v) VERFUN(caso,ok,F,M,v,vrbs,ucase)
      VERF("0 3 3 1 2    1 2 3 0    2 4 5 0 4 3    3 4 2 1 0 5    4 2 2 5    5 3 2 3 4    ",4);
      VERF("0 2 1 2 1 2 0 2 2 2 0 1",1);
#include "./ver2.hpp"
      
      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    typedef map< int,set<int> > gs_t;
    typedef map< int,list<int> > gl_t;
    void addtri(gs_t &M,int n1,int n2,int n3) {
      M[n1].insert(n2);
      M[n2].insert(n1);
      M[n2].insert(n3);
      M[n3].insert(n2);
      M[n3].insert(n1);
      M[n1].insert(n3);
    }
    
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0,int hardness=0) {
      chrono_t chrono;

      double mips = NAN;
      if (hardness==5) mips=bogomips();
      double facmax=100, fac = pow(facmax,hardness/5.0);
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed); 

      chrono.reset();
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2  && !hardness) printf("Ejerc " SEJERC ". Caso %d\n",caso);
        // Makes a grid of 2xMxN tris
        // Vrtx numbering by columns: y-indx (k) runs faster
        
        int Z=5*fac, N = 1+rnd.rand()%(Z-1), M = Z-N;
        int NV = (N+1)*(M+1);
        gs_t MM;
        for (int j=0; j<M; j++) { // x indx
          for (int k=0; k<N; k++) { // y indx
            int
              SW = j*(N+1)+k,
              NW = SW+1,
              SE = SW+N+1,
              NE = SW+N+2;
            MM[SW].insert(NW);
            // FIXME:= add random split
            if (rnd.rand()%2) {
              // Split along SW-NE
              addtri(MM,SW,SE,NE);
              addtri(MM,NE,NW,SW);
            } else {
              // Split along SE-NW
              addtri(MM,SE,NE,NW);
              addtri(MM,NW,SW,SE);
            }
          }
        }
        assert(int(MM.size())==NV);
        gl_t G;
        
        for (int j=0; j<NV; j++) {
          list<int> &L = G[j];
          L.insert(L.begin(),MM[j].begin(),MM[j].end());
          random_shuffle(rnd,L);
        }

        chrono.start();
        int ntri = F(G);
        chrono.stop();
        // assert(ntri==2*M*N);
        if (0) {
          string SG = g2s(G);
          printf("VERF(\"%s\",%d);\n",CSTR(SG),ntri);
        }
        hasher.hash(ntri);
      }
      if (hardness) {
        cout << "EJ" SEJERC ". Hardness "
             << hardness << ", elapsed " << chrono.elapsed() << "[s]";
        if (hardness==5) 
          cout << " (mips " << mips << ", relative "
               << chrono.elapsed()/mips << "[s])";
        cout << endl;
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

    typedef void (*min_com_subtree_t)(tree<int> &T,node_t m,node_t n,
                                      tree<int> &Q);
#undef FUNC_T
#define FUNC_T min_com_subtree_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sT,
                int xm,int xn,
                string sQref,
                int vrbs=0,int ucase=-1) {
      if (ucase>=0 && ucase!=caso) { caso++; return; }

      tree<int> T,Tuser,Qref,Quser;
      lisp2tree(sT,T);
      Tuser = T;
      lisp2tree(sQref,Qref);
      typedef tree<int>::iterator node_t;
      node_t m = Tuser.find(xm);
      node_t n = Tuser.find(xn);
      assert(m!=T.end());
      assert(n!=T.end());
      
      F(Tuser,m,n,Quser);
      
      int ok = (Quser==Qref);
      if (!ok || vrbs) {
        printf("---------\n");
        cout << "T: "; T.lisp_print(); cout << endl;
        cout << "*m, *n " << *m << " " << *n << endl;
        cout << "Q(user): "; Quser.lisp_print(); cout << endl;
        cout << "Q(ref): "; Qref.lisp_print(); cout << endl;
      }
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso " 
             << caso << ". Estado: " << i2s(ok) << endl;
      caso++;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0,int ucase=-1) {
      cout << "----------------\nEvaluando ejercicio " 
        STR(EJERC) << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(T,m,n,Q) VERFUN(caso,ok,F,T,m,n,Q,vrbs,ucase)
      VERF("(1 (3 4 (2 5)) 6)",4,5,"(3 4 (2 5))");
#include "./ver3.hpp"

      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0,int hardness=0) {
      chrono_t chrono;
      double mips = NAN;
      if (hardness==5) mips=bogomips();
      double facmax=1000, fac = pow(facmax,hardness/5.0);
      int ncasos=30;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      int skipped = 0;
      int caso=0;

      chrono.reset();
      chrono_t total;
      total.start();
      while (1) {
        if (vrbs>=2 && !hardness) printf("Ejerc " SEJERC ". Caso %d\n",caso);
        tree<int> T,Q,Tcpy;
        list<int> L;
        int N = (5+rnd.rand()%5)*fac;
        this->make_random_tree2(T,20,N,3,rnd);
        Tcpy = T;
        this->preorder(T,L);
        random_shuffle(rnd,L);
        typedef tree<int>::iterator node_t;
        int mv= *L.begin(), nv = *(++L.begin());
        node_t m = T.find(mv), n = T.find(nv);
        // Check that m/n are not ancestor/descendant
        if (T.find(*m,n)!=T.end() || T.find(*n,m)!=T.end()) {
          skipped++;
          // printf("FOUND A/D: m %d, n%d\n",*m,*n);
          // T.lisp_print(); 
          // cout << endl;
          continue;
        }

        if (!hardness) F(T,m,n,Q);
        else {
          chrono.start();
          for (int k=0; k<100; k++) {
            tree<int> T1 = T, Q1;
            node_t m1 = T1.find(mv), n1 = T1.find(nv);
            F(T1,m1,n1,Q1);
            Q1.clear();
          }
          chrono.stop();
        }
        if (1) {
          // Generate ver1 tests
          string TT = lisp_print(Tcpy);
          string QQ = lisp_print(Q);
          printf("VERF(\"%s\",%d,%d,\"%s\");\n",CSTR(TT),*m,*n,CSTR(QQ));
        }
        hasher.hash(Q);
        caso++;
        if (caso==ncasos) break;
      }
      total.stop();
      // printf("total %f\n",total.elapsed());
      // printf("ncasos %d, skipped %d, skip rate %f\n",
      //        ncasos,skipped,double(skipped)/double(ncasos+skipped));
      if (hardness) {
        cout << "EJ" SEJERC ". Hardness "
             << hardness << ", elapsed " << chrono.elapsed() << "[s]";
        if (hardness==5) 
          cout << " (mips " << mips << ", relative "
               << chrono.elapsed()/mips << "[s])";
        cout << endl;
      }
      int H = hasher.val()%1000;
      if (vrbs  && !hardness)
        printf("EJ" SEJERC ": SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }
    //---:---<*>---: END EJERC 3 ---<*>---:---<*>---:---<*>---:---<*>

    //---:---<*>---: START EJERC 4 ---<*>---:---<*>---:---<*>---:---<*>
#undef EJERC
#undef VERFUN
#undef EVFUN
#undef EVRFUN
#undef SEJERC
#define EJERC 4
#define SEJERC "4"
#define VERFUN VERJ(EJERC)
#define EVFUN EVALJ(EJERC)
#define EVRFUN EVALRJ(EJERC)

    typedef void (*prune_to_level_t)(tree<int> &T,int lev);
#undef FUNC_T
#define FUNC_T prune_to_level_t
    void VERFUN(int &caso,int &okt,
                FUNC_T F,
                string sT,
                string sQref,
                int level,
                int vrbs=0,int ucase=-1) {
      if (ucase>=0 && ucase!=caso) { caso++; return; }

      tree<int> T,Quser,Qref;
      lisp2tree(sT,T);
      lisp2tree(sQref,Qref);
      Quser = T;
      F(Quser,level);
      
      int ok = (Quser==Qref);
      if (!ok || vrbs) {
        printf("---------\n");
        cout << "T: " << lisp_print(T) << endl;
        cout << "level: " << level << endl;
        cout << "Q(user): " << lisp_print(Quser) << endl;
        cout << "Q(ref): " << lisp_print(Qref) << endl;
      }
      if (vrbs || !ok)
        cout << "EJ" SEJERC "|Caso " 
             << caso << ". Estado: " << i2s(ok) << endl;
      caso++;
      okt += ok; 
    }

    void EVFUN(FUNC_T F,int vrbs=0,int ucase=-1) {
      cout << "----------------\nEvaluando ejercicio " 
        STR(EJERC) << endl;
      int caso = 0, ok = 0;

#undef VERF
#define VERF(T,Qref,l) VERFUN(caso,ok,F,T,l,Qref,vrbs,ucase)
      VERF("(1 (2 (4 9) 5) (3 (6 7 8)))",2,"(1 (2 4 5) (3 6))");
      VERF("(1 (2 4 5) (3 6))",1,"(1 2 3)");
#include "./ver4.hpp"
      
      int total = caso;
      printf("ESTADO EJ" SEJERC
             " Total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }
    
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int EVRFUN(FUNC_T F,int seed,int vrbs=0) {
      int ncasos=10;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);

      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejerc " SEJERC ". Caso %d\n",caso);

        int N = 5+rnd.rand()%5;
        tree<int> T,Q;
        this->make_random_tree2(T,10,N,3,rnd); 
        string sT = lisp_print(T);
        for (int lev=0; lev<5; lev++) {
          Q=T;
          F(Q,lev);
          hasher.hash(Q);
          if (0) {
            string sQ = lisp_print(Q);
            printf("VERF(\"%s\",%d,\"%s\");\n",CSTR(sT),lev,CSTR(sQ));
          }
        }
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ" SEJERC ": SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }
    //---:---<*>---: END EJERC 4 ---<*>---:---<*>---:---<*>---:---<*>
    
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
#undef C

#endif
