// GITVERSION: tpl12015-2-gc8252f7
#include "eval.hpp"
#include <climits>
#include <cstdlib>
#include <stack>

#include <list>
using namespace aed;
using namespace std;
int sumar_els(list<int> &L){
  int suma=0;
  for(int &x: L) suma +=x;
  return suma;
}
  
//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
// Retorna la sublista contigua cuya suma es maxima
list<int> max_sublist(list<int> &L){
  
  list<int> Lmax;
  list<int> aux;
  list<int>::iterator it1 = L.begin();
  list<int>::iterator it2 = L.end();
  
  while(it1!=L.end()){
    //analizar todas las posibles sublistas que empiezan por este elemento
    list<int>::iterator it_aux = it1;
    list<int> aux2;
    aux.push_back(*it_aux);
    while(it_aux!=it2){
      aux2.push_back(*it_aux);
      if(sumar_els(aux2)>sumar_els(aux)){
        aux=aux2;
      }
      ++it_aux;
    }
    if(sumar_els(aux)>sumar_els(Lmax) /*|| (sumar_els(aux)==sumar_els(Lmax) and aux.size()<=Lmax.size())*/){ 
      Lmax=aux;
    }
    aux.erase(aux.begin(),aux.end());
    it1++;
  }
  return Lmax;
  
  return {};
}

//---:---<*>---:---<*>---:---<*>---:---<*>---:---<*>
int main() {
  Eval ev;
  int vrbs = 0;

  ev.eval2(max_sublist,vrbs);
  
  return 0;
}
