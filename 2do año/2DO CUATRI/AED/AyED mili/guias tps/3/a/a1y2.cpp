#include <iostream>
#include <tree.hpp>
#include <list>
#include <graphviz.hpp>#include <lisp.hpp>
using namespace aed;
using namespace std;


// EJERCICIO 1
void preorden(tree<int> &arbol, list<int> &L, tree<int>::iterator nodo){
	L.push_back(*nodo);
	auto hijo = nodo.lchild();
	while(hijo!=arbol.end()){
		preorden(arbol, L, hijo);
		hijo++;
	}
}
void postorden(tree<int> &arbol, list<int> &L, tree<int>::iterator nodo){
	auto c = nodo.lchild();
	while(c != arbol.end()){
		postorden(arbol, L, c);
		c = c.right();
	}
	L.push_back(*c);
}
	
// EJERCICIO 2
/* 2.a */
void altura(tree<int> &arbol, tree<int>::iterator nodo, int nivel, int &max){
	if(max<nivel) max=nivel;
	auto hijo = nodo.lchild();
	while(hijo!=arbol.end()){
		altura(arbol,hijo,nivel+1,max);
		hijo++;
	}
}
int altura(tree<int> &arbol){
	int n = 0; int nmax = 0;
	altura(arbol,arbol.begin(),n,nmax);
	return nmax;
}

/* 2.b */
template<typename T>
void hojas(tree<T> &arbol,typename tree<T>::iterator p, int &n){
	if (p == arbol.end()) return;
	typename tree<T>::iterator c = p.lchild();
	if (c == arbol.end()) ++n;
	while (c != arbol.end()) hojas(arbol,c++,n);
}
template<typename T>
int hojas(tree<T> &arbol){
	int n = 0;
	hojas(arbol,arbol.begin(),n);
	return n;
}
	
/* 2.c */
void max_etiqueta(tree<int> &arbol, tree<int>::iterator nodo, int &max_et){
	auto hijo = nodo.lchild();
	while(hijo!=arbol.end()){
		if(max_et<*hijo) max_et = *hijo;
		max_etiqueta(arbol,hijo,max_et);
		hijo++;
	}
}
int max_etiqueta(tree<int> &arbol){
	int max_et = *arbol.begin();
	max_etiqueta(arbol,arbol.begin(),max_et);
	return max_et;
}


/* 2.d */
void max_etiqueta_par(tree<int> &arbol, tree<int>::iterator nodo, int &max_et){
	if(nodo==arbol.end())return;
	if(*nodo>max_et && *nodo%2==0) max_et=*nodo;
	nodo = nodo.lchild();
	while(nodo != arbol.end()){
		max_etiqueta_par(arbol, nodo++, max_et);
	}
}
int max_etiqueta_par(tree<int> &arbol){
	int max_et_par=-1;
	max_etiqueta_par(arbol,arbol.begin(),max_et_par);
	return max_et_par;
}
	

/* 2.e */
void max_etiqueta_hojas(tree<int> &arbol, tree<int>::iterator p, int &max_hoja){
	if(p==arbol.end()) return;
	if(p.lchild()==arbol.end() && *p>max_hoja) max_hoja = *p;
	tree<int>::iterator c = p.lchild();
	while(c!=arbol.end()){
		max_etiqueta_hojas(arbol, c++, max_hoja);
	}
}
int max_etiqueta_hojas(tree<int> &arbol){
	int max_hoja =-9999999;
	max_etiqueta_hojas(arbol,arbol.begin(),max_hoja);
	return max_hoja;
}
	

/* 2.f */	
void suma_etiquetas(tree<int> &arbol, tree<int>::iterator p, int &suma){
	if(p == arbol.end()) return;
	suma+=*p;
	tree<int>::iterator c = p.lchild();
	while(c!=arbol.end()){
		suma_etiquetas(arbol, c++, suma);
	}
}
int suma_etiquetas(tree<int> &arbol){
	int suma =0;
	suma_etiquetas(arbol,arbol.begin(),suma);
	return suma;
}
	
/* 2.g */
tree<int>::iterator eliminar_etiquetas_impares(tree<int> &arbol,tree<int>::iterator p){	if (p == arbol.end()) return p;	if (*p%2){		p = arbol.erase(p);	}	else{		tree<int>::iterator c = p.lchild();		while (c != arbol.end()){ c = eliminar_etiquetas_impares(arbol,c);}		++p;	}	return p;}
void purga_impares(tree<int> &arbol){
	eliminar_etiquetas_impares(arbol,arbol.begin());
}
	
int main() {
	string s_arbol("(1 2 (3 6 (7 11 12))(4 8) (5 9 (13 10))");	tree<int> arbol;			if (lisp2tree(s_arbol,arbol)) tree2dot(arbol);	else cout << "Error en crear arbol a partir de notacion de lisp \n";
	
	cout<<max_etiqueta(arbol)<<endl;
	return 0;
}







