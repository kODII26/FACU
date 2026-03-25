#define USECHRONO
#undef HAVE_MPI
#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
#include <map>

using namespace aed;
using namespace std;

void make_full(btree<int> &T, btree<int>::iterator it){
  
  if(it==T.end()) return;
  
  btree<int>::iterator cl = it.left();
  btree<int>::iterator cr = it.right();
  
  if(cl==T.end()&&cr==T.end()) return;
  
  if(cl==T.end() xor cr == T.end()){
    btree<int> T2;
    if(cl ==T.end()){
      T2.splice(T2.begin(),cr);
    }else{
      T2.splice(T2.begin(),cl);
    }
    it = T.erase(it);
    btree<int>::iterator it2 = T2.begin();
    T.splice(it, it2);
    make_full(T, it);
  }
  else{
    if(cl!=T.end()) make_full(T,cl);
    if(cr!=T.end()) make_full(T,cr);
  }
  
}

void make_full(btree<int> &T) {
  make_full(T, T.begin());
}

// Otra solucion, no necesita refrescar los iteradores
void make_full2(btree<int> &T, btree<int>::iterator it) {
  if ( (it.left()==T.end()) != (it.right()==T.end()) ) {
    // Tiene uno solo de los hijos, elimina el nodo y
    // splicea ese hijo
    // T2 es un temporario para splicear
    btree<int> T2;
    // ITC es el nodo que no es Lamdba
    auto itc = it.left()==T.end() ? it.right() : it.left();
    // Mueve el subarbol del hijo al temporario
    T2.splice(T2.begin(),itc);
    // Elimina el nodo (a esta altura es una hoja)
    it = T.erase(it);
    // Splicea de vuelta el temporario al nodo eliminado
    auto it2 = T2.begin();
    it = T.splice(it,it2);
    // Aplica recursivamente
    make_full2(T,it);
  } else {
    // Los dos nodos son Lambda o NO. Le aplica la funcion
    // recursivamente a cada uno de ellos (si no son Lambda)
    if (it.left()!=T.end()) make_full2(T,it.left());
    if (it.right()!=T.end()) make_full2(T,it.right());
  }
}

// Wrapper
void make_full2(btree<int> &T) {
  make_full2(T,T.begin());
}

// Funcion auxiliar, hace la suma del subarbol de IT en el
// arbol T
int aux(btree<int>&T,btree<int>::iterator it){
  if(it==T.end()) return 0;
  int l = aux(T,it.left());
  int r = aux(T,it.right());
  return *it+l+r;
}
  
  // Retorna la suma del maximo subarbol de un nodo en el
  // subarbol de IT.  Busca el maximo en cada uno de los hijos
  // ML,MR y despues considera: Los subarboles encontrados en
  // los hijos (ML y MR) y despues la suma correspondiente al
  // subarbol de IT mismo
  int max_subbtree(btree<int>&T,btree<int>::iterator it){
    if(it==T.end()) return 0;
    int Ml = max_subbtree(T,it.left());
    int Mr = max_subbtree(T,it.right());
    int M = aux(T,it);
    return max(max(M,Ml),Mr);
  }
    
    int max_subbtree(btree<int>&T){
      return max_subbtree(T,T.begin());
    }
      
      // Retorna el indice J de aquel set VS[J] tal que VS[J] esta
      // "conectado" a la mayor cantidad de los otros conjuntos
      // VS[K].  Dos conjuntos VS[J],VS[K] estan conectados si
      // tienen interseccion no-nula.
      int most_connected(vector< set<int> > &VS) {
        // Numero de conjuntos en VS
        int nset= VS.size();
        // Inicializar indx (posicion del mas conectado) y su
        // numero de conexiones
        int indx=-1,maxcon=-1;
        // Recorre todos los conjuntos
        for (int j=0; j<nset; j++) {
          // Cuenta cuantos conjuntos tienen interseccion no-nula
          int jcon=0;
          set<int> &VSj = VS[j];
          for (int k=0; k<nset; k++) {
            set<int> &VSk = VS[k];
            set<int> tmp;
            // Usa un temporario para la interseccion
            set_intersection(VSj,VSk,tmp);
            // Sumar 1 si la interseccion no es vacia
            jcon += !tmp.empty();
          }
          // Si el actual J tiene mas conexiones que el mas
          // conectacto hasta ahora => actualizar
          if (jcon>maxcon) {
            maxcon = jcon;
            indx = j;
          }
        }
        return indx;
      }
      
      //---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
      bool connected(set<int> &s1,set<int> &s2) {
        set<int> tmp;
        // Usa un temporario para la interseccion
        set_intersection(s1,s2,tmp);
        return !tmp.empty();
      }

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0;

  do {

    
   
    
    printf("\n\nIngrese un valor para la semilla:");
  } while (cin>>seed);

  return 0;
}
