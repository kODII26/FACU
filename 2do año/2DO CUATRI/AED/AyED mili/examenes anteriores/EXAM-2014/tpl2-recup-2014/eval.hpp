#ifndef EVAL_HPP
#define EVAL_HPP

#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tree.hpp"
#include "util_tree.hpp"
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

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void dump(list<int> &L,string s="") {
      cout << s; 
      list<int>::iterator q = L.begin();
      while (q!=L.end()) cout << *q++ << " ";
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void dump(vector< list<int> > &VL,string s="") {
      int N = VL.size();
      // cout << "vector length " << N << endl;
      for (int j=0; j<N; j++) {
        cout << s << "[" << j << "]: ";
        dump(VL[j]);
      }
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void dump(map<int,int> &M,string s="") {
      cout << s << endl; 
      map<int,int>::iterator itm = M.begin();
      while (itm != M.end()){
        cout << "M[" << itm->first <<"] = "<< itm->second << endl;
        itm++;
      }
      cout << endl;
    }

    void printmap(map<int, list<bool> >& M) {
      cout << "M = {";
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
      int k, n, v;
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
      for (int j=0; j<v.size(); j++) 
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
    typedef void (*mkmtree_t)(tree<int> &T,int m,int k);
    void verificar1(int &caso,int &okt,mkmtree_t F,int m,int k,string stref, 
                    int vrbs=0) {
      tree<int> Tref,Tuser;
      lisp2tree(stref,Tref);
      F(Tuser,m,k);
      int ok = (Tuser == Tref);
      if (!ok || vrbs) {
        printf("---------\n");
        cout << "m: " << m << ", k: " << k << endl;
        cout << "T(ref): " << stref << endl;
        cout << "T(user): "; Tuser.lisp_print(); cout << endl;
      }
      cout << "EJ1|Caso" << caso++ << ". Estado: " << i2s(ok) << endl;
      okt += ok; 
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void eval1(mkmtree_t F,int vrbs=0) {
      cout << "----------------\nEvaluando ejercicio 1 (mkmtree)" << endl;
      int caso = 0, ok = 0;
#define VRF(m,k,T) verificar1(caso,ok,F,m,k,T,vrbs);
      VRF(10,3,"(10 (7 (4 1) 1) (4 1) 1)");
      VRF(10,2,"(10 (8 (6 (4 2) 2) (4 2) 2) (6 (4 2) 2) (4 2) 2)");
      VRF(20,7,"(20 (13 6) 6)");
      VRF(23,6,"(23 (17 (11 5) 5) (11 5) 5)");
      int total = caso;
      printf("ESTADO EJ1: total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int eval1r(mkmtree_t F,int seed,int vrbs=0) {
      int ncasos=20;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejercicio 1. Caso %d\n",caso);
        int 
          m = 20 + rnd.rand()%10,
          k = 5 + rnd.rand()%5;
        tree<int> T;
        F(T,m,k);
        if (vrbs) {
          printf("hash check: m %d, k %d\nT: ",m,k);
          T.lisp_print();
          printf("\n");
        }
        hash(hasher,T);
        
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ1: SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    typedef bool (*has_equal_path_t)(tree<int> &T);
    void verificar2(int &caso,int &okt,has_equal_path_t F,
                    string stin,int rvref,
                    int vrbs=0) {
      tree<int> Tin;
      lisp2tree(stin,Tin);
      int rvuser = F(Tin);
      int ok = (rvuser == rvref);
      if (!ok || vrbs) {
        printf("---------\n");
        cout << "T: " << stin << endl;
        cout << "retval(user): " << rvuser 
             << ", retval(ref): " << rvref << endl;
      }
      cout << "EJ2|Caso" << caso++ << ". Estado: " << i2s(ok) << endl;
      okt += ok; 
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void eval2(has_equal_path_t F,int vrbs=0) {
      cout << "----------------\n"
        "Evaluando ejercicio 2 (has_equal_path)" << endl;
      int caso = 0, ok = 0;
#define VRF2(T,R) verificar2(caso,ok,F,T,R,vrbs);
      VRF2("(1 (1 2 3) (1 2 4))",0);
      VRF2("(1 (1 2 3) (1 2 1))",1);
      VRF2("(1 (1 2 1) (1 2 4))",1);
      VRF2("(1 (2 2 1) (1 2 4))",0);
      int total = caso;
      printf("ESTADO EJ1: total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int eval2r(has_equal_path_t F,int seed,int vrbs=0) {
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejercicio 2. Caso %d\n",caso);
        tree<int> T;
        this->make_random_tree2(T,2,40,5,rnd);
        // T.lisp_print(); printf("\n");
        // printf("has_equal_path: %d\n",F(T));
        int has = F(T);
        hasher.hash(has);
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ2: SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void dump(stack<int> S,string s="") {
      cout << s; 
      while (!S.empty()){
        cout << S.top() << " ";
        S.pop();
      }
      cout << endl;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void dump(queue<int> Q,string s="") {
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
	
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    typedef void (*pancake_sort_t)(stack<int> &S);
    void verificar1(int &caso,int &okt,pancake_sort_t F,string sstack, 
                    string sres, int vrbs=0) {
      stack<int> s,s2;
      stack<int> Sans;
      s2sta(sstack,s);
      s2sta(sstack,s2);
      s2sta(sres,Sans);
      F(s);
		
      int ok = (s == Sans);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(s2,"S: ");
        dump(Sans,"Respuesta esperada S: ");
        cout << endl;
      }
      cout << "EJ3|Caso" << caso++ << ". Estado: " << i2s(ok) << endl;
      okt += ok;
    }
	
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void eval3(pancake_sort_t F,int vrbs=0) {
      cout << "----------------\n"
        "Evaluando ejercicio 3 (pancake-sort)" << endl;
      int caso = 0, ok = 0;
      verificar1(caso,ok,F,"1 5 2 9 7 3 6 8 4","9 8 7 6 5 4 3 2 1",vrbs);
      verificar1(caso,ok,F,"30 10 20 3 47 52 1 150 5","150 52 47 30 20 10 5 3 1",vrbs);
      verificar1(caso,ok,F,"1 2 3 4 5 6 7 8 9","9 8 7 6 5 4 3 2 1",vrbs);
      verificar1(caso,ok,F,"1","1",vrbs);
      verificar1(caso,ok,F,"30 20 10","30 20 10",vrbs);
      int total = caso;
      printf("ESTADO EJ3: total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int eval3r(pancake_sort_t F,int seed,int vrbs=0) {
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      int TERM=-1;
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejercicio 3. Caso %d\n",caso);
        stack<int> S;
        int N = 20+rnd.rand()%20;
        for (int j=0; j<N; j++) {
          int x = rnd.rand()%100;
          hasher.hash(x);
          S.push(x);
        }
        hasher.hash(TERM);
        F(S);
        while (!S.empty()) {
          int x = S.top(); S.pop();
          hasher.hash(x);
        }
        hasher.hash(TERM);
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ3: SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    typedef int (*count_cycles_t)(map<int,int> &M);
    void verificar4(int &caso,int &okt,count_cycles_t F,
                    string sm, int ans, int vrbs=0) {
      map<int,int> m,m2;
      s2m(sm,m);
      s2m(sm,m2);
      int user_ans = F(m);
		
      int ok = (user_ans == ans);
      if (!ok || vrbs) {
        printf("---------\n");
        dump(m2,"M: ");
        cout << "Retval (ref): " << ans << " ciclos." << endl;
        cout << "Retval (user): " << user_ans << " ciclos." << endl;
      }
      cout << "EJ4|Caso" << caso++ << ". Estado: " << i2s(ok) << endl;
      okt += ok; 
    }
	
    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    void eval4(count_cycles_t F,int vrbs=0) {
      cout << "----------------"
        "\nEvaluando ejercicio 4 (count-cycles)" << endl;
      int caso = 0, ok = 0;
      verificar4(caso,ok,F,"1 2 2 3 3 1",1,vrbs);
      verificar4(caso,ok,F,"1 2 2 4 3 6 4 9 6 3 9 1 10 10",3,vrbs);
      verificar4(caso,ok,F,"1 2 2 3 3 4 4 5 5 6 6 1",1,vrbs);
      verificar4(caso,ok,F,"21 2 2 21",1,vrbs);
      verificar4(caso,ok,F,"5 5 3 3",2,vrbs);
      int total = caso;
      printf("ESTADO EJ4: total %d, ok %d, mal %d. Todos bien? %s\n",
             total,ok,total-ok,i2s(ok==total));
    }

    void random_shuffle(randomg_t &rnd,vector<int> &v,int k1,int k2) {
      int n = k2-k1;
      if (n<=1) return;
      int n1 = n/2, n2 = n-n1, j1=k1, j2=k1+n1;
      this->random_shuffle(rnd,v,k1,j2);
      this->random_shuffle(rnd,v,j2,k2);
      vector<int> w;
      while (n1 || n2) {
        int choose1 = (rnd.rand()%(n1+n2))<n1;
        if (choose1) { w.push_back(v[j1++]); n1--; }
        else { w.push_back(v[j2++]); n2--; }
      }
      for (int j=0; j<n; j++) v[k1+j] = w[j];
    }

    void random_shuffle(randomg_t &rnd,vector<int> &v) {
      this->random_shuffle(rnd,v,0,v.size());
    }

    //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
    int eval4r(count_cycles_t F,int seed,int vrbs=0) {
      
      int ncasos=50;
      hasher_t hasher;
      randomg_t rnd;
      rnd.reset(seed);
      int TERM=-1;
      for (int caso=0; caso<ncasos; caso++) {
        if (vrbs>=2) printf("Ejercicio 4. Caso %d\n",caso);
        map<int,int> M;
        int N = 20+rnd.rand()%20;
        set<int> s;
        while (s.size()<N) { s.insert(rnd.rand()%(4*N));}
        vector<int> vx,vy;
        set<int>::iterator q = s.begin();
        while (q!=s.end()) vx.push_back(*q++);
        vy = vx;
        random_shuffle(rnd,vy);
        for (int j=0; j<N; j++) {
          // printf("%d -> %d\n",vx[j],vy[j]);
          M[vx[j]] = vy[j];
          hasher.hash(vx[j]);
          hasher.hash(vy[j]);
        }
        hasher.hash(TERM);
        int ncy = F(M);
        // printf("ncy %d\n",ncy);
        hasher.hash(ncy);
        hasher.hash(TERM);
      }
      int H = hasher.val()%1000;
      if (vrbs) printf("EJ4: SEED=%03d, HASH=%03d\n",seed,H);
      return H;
    }
  };
}

#endif
