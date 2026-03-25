#include <iostream>
#include <tree.hpp>
#include <graphviz.hpp>
#include <lisp.hpp>
#include <list>

using namespace aed;
using namespace std;

template<typename T>
void show_list(const list<T> &L){
	cout << "[ ";
	for_each(L.begin(),L.end(),[](T v){cout << v << " ";});
	cout << "] \n";
}
	
void altura(tree<int> &arbol, tree<int>::iterator it, int prof, int &alt){
	if (it==arbol.end()) return;
	auto h=it.lchild();
	while (h!=arbol.end()){
		altura(arbol,h,prof+1,alt);
		h++;
	}
	if (prof>alt){
		alt=prof;
	}
}

void contar_hojas(tree<int> &arbol, tree<int>::iterator it, int &n_hojas)
{	
	if (it==arbol.end()) return;
	
	auto h=it.lchild();
	
	if (h==arbol.end()) ++n_hojas;
	while (h!=arbol.end()){
		contar_hojas(arbol,h,n_hojas);
		h++;
	}


}

void etiqueta_maxima(tree<int> &arbol, tree<int>::iterator it, int &et_max)
{
	if (it==arbol.end()) return;
	
	auto h=it.lchild();
	
	if (*it>et_max) et_max=*it;
	
	while (h!=arbol.end()){
		etiqueta_maxima(arbol,h,et_max);
		h++;
	}
}

void etiqueta_maxima_par(tree<int> &arbol, tree<int>::iterator it, int &et_max)
{
	if (it==arbol.end()) return;
	
	auto h=it.lchild();
	
	if (*it>et_max && *it%2==0){
		et_max=*it;
	}
	
	while (h!=arbol.end()){
		etiqueta_maxima_par(arbol,h,et_max);
		h++;
	}

}

void suma_etiquetas(tree<int> &arbol, tree<int>::iterator it, int &suma)
{
	if (it==arbol.end()) return;
	
	suma+=*it;
	
	auto h=it.lchild();
	
	while (h!=arbol.end()){
		suma_etiquetas(arbol,h,suma);
		h++;
	}
	
}

void purge_odd(tree<int> &arbol, tree<int>::iterator it )
{		
	if (*it%2!=0){
		it=arbol.erase(it);
	}
	if (it==arbol.end()) return;
	auto h= it.lchild();
	while (h!=arbol.end()){
		if (*h%2 !=0) {
			h=arbol.erase(h);
		}else {
			purge_odd(arbol,h);
			++h;
		}
	}
}

	
int main()
	{			
	string s_arbol("(10 2 (3 6 (7 11 12))(4 8) (6 9 (41 10))");
	//string s_arbol("(1)");
	tree<int> arbol;	
	
	if (!lisp2tree(s_arbol,arbol)) 
	{
	 cout << "Error en crear arbol a partir de notacion de lisp \n";
	 return -1;
	}
	tree2dot(arbol, "arbol_completo");
	
	int alt = 0;
	altura(arbol, arbol.begin(),0,alt);
	
	int n_hojas = 0;
	contar_hojas(arbol, arbol.begin(),n_hojas);
	
	int et_max= -1;
	etiqueta_maxima(arbol, arbol.begin(),et_max);

	int et_max_par= -1;
	etiqueta_maxima_par(arbol, arbol.begin(),et_max_par);
	
	int suma = 0;
	suma_etiquetas(arbol, arbol.begin(),suma);
	
	cout << "altura: "<<alt << endl;
	cout << "n_hojas: "<<n_hojas<< endl;
	cout << "et_max: "<<et_max<< endl;
	cout << "et_max_par: "<<et_max_par<< endl;
	cout << "suma: "<<suma<< endl;
	
	purge_odd(arbol, arbol.begin());	
	tree2dot(arbol,"arbol_sin_impares");	
	
	return 0;
	}
