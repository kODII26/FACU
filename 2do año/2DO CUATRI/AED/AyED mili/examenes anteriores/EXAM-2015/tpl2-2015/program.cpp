// #define USECHRONO
#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

using namespace aed;
using namespace std;

// * Completar los datos.
// * No borrar las lineas "(BEGIN|END) USERCODE"
//   ya que son necesarias para la evaluacion automatica
//   del Torneo.
// --- <<BEGIN-USERCODE>> -----
// NOMBRE:
// DNI:
void getpath(map<int,list<int> > &M,
             int vrtx, list<int> &path) {
  vector<bool> visited;
  visited[vrtx]=true;
  path.push_back(vrtx);
  bool seguir = true;
  while(seguir){
	seguir=false;
	int ult_vrtx = *prev(path.end());
	list<int> vecinos = M[ult_vrtx];
	for(int x: vecinos){
		if(!visited[x]){
			seguir=true;
			visited[x]=true;
			path.push_back(x);
			break;
		}
	}
	
  }
}

int tricount(map<int,list<int> > &M) {
  // COMPLETAR AQUI...
  return 0;
}

void min_com_subtree(tree<int> &T,node_t m,node_t n,
                     tree<int> &Q) {
  // COMPLETAR AQUI...
}

// Wrapper
void prune_to_level(tree<int> &T,int lev) {
  // COMPLETAR AQUI...
}
// --- <<END-USERCODE>> -----

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;
  int seed = 123;
  int h1=0,h2=0,h3=0,h4=0;

  ev.eval1(getpath,vrbs);
  h1 = ev.evalr1(getpath,seed,vrbs);
    
  /*ev.eval2(tricount,vrbs);
  h2 = ev.evalr2(tricount,seed,vrbs);

  ev.eval3(min_com_subtree,vrbs);
  h3 = ev.evalr3(min_com_subtree,seed,vrbs);

  ev.eval4(prune_to_level,vrbs);
  h4 = ev.evalr4(prune_to_level,seed,vrbs);*/

  // Para S=123 debe retornar:
  // S=123 -> H1=085 H2=806 H3=655 H4=284
  printf("S=%03d -> H1=%03d H2=%03d H3=%03d H4=%03d\n",
         seed,h1,h2,h3,h4);

#if 0
  // Para el torneo (habilitar el macro USECHRONO arriba)
  int hardness=1;
  ev.evalr2(tricount,seed,vrbs,hardness);
  ev.evalr3(min_com_subtree,seed,vrbs,hardness);
#endif
  
  return 0;
}
