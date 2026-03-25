#define USECHRONO
#undef HAVE_MPI

#include "eval.hpp"
#include <cassert>
#include <climits>
#include <cstdlib>
#include <stack>
using namespace aed;
using namespace std;


//---:---<*>---:---<*>- COMIENZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
// COMPLETAR DNI y NOMBRE AQUI:
// Nombre: Bob Esponja
int DNI=98765432;

void get_sub_prop(set<int> S, list<set<int>> &sub_prop){
  set<int>::iterator it = S.begin();
  int sub = S.size();
  
  while(it!=S.end()){
    set<int>::iterator it2 = S.begin();
    set<int> tmp;
    tmp.insert(*it);
    
    while(it2!=S.end()){
      tmp.insert(*it2);
      if(sub>tmp.size()){
        sub_prop.push_back(tmp);
      }
      it2++;
    }
    it = S.erase(it);
  }
  
}


float promedio(set<int> S){
  int suma=0;
  int cont =0;
  while(!S.empty()){
    suma+=*S.begin();
    S.erase(S.begin());
    cont++;
  }
  if(cont==0) return cont;
  return (suma/(cont*1.0));
}
  
int max_of_set(set<int> s){
  int max=-1;
  set<int>::iterator it= s.begin();
  while(it!=s.end()){
    if(*it>max) max=*it;
    it++;
  }
  return max;
}

bool mayor(set<int> s1, set<int> s2){
  if(s1.empty()) return false;
  if(s2.empty()) return true;
  
  set<int>::iterator it1 = s1.begin();
  set<int>::iterator it2 = s2.begin();
  
  while(!s1.empty() && !s2.empty()){
    if(max_of_set(s1)> max_of_set(s2)) return true;
    else if(max_of_set(s1)< max_of_set(s2)) return false;
    else{
      s1.erase(max_of_set(s1)); s2.erase(max_of_set(s2));
    }
  }
  if(s1.empty() ) return false;
  return true;
}

  
void get_largest_subset(set<int> &S, set<int> &C)
{
  if(S.empty()) return;
  
  list<set<int>> sub_prop;
  get_sub_prop(S, sub_prop);
  
  float prom = promedio(S);
  
  float min_dif = 9999999;
  set<int> rta;
  
  
  for(auto sp: sub_prop){
    float aux_prom = promedio(sp);
    if(fabs(prom-aux_prom)<min_dif){
      min_dif = fabs(prom-aux_prom);
      rta=sp;
    }else if(fabs(prom-aux_prom)==min_dif){
      if(mayor(sp,rta)){
        rta=sp;
      }
    };
  }
  C=rta;
}


//---:---<*>---:---<*>- FINALIZA CODIGO FUNCION --:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs=0;
  ev.eval<1>(get_largest_subset,vrbs);
  
  return 0;
}
