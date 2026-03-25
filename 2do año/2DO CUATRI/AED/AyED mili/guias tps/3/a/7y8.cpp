#include <iostream>
#include <tree.hpp>
#include <graphviz.hpp>#include <lisp.hpp>#include <list>
#include <iomanip>
using namespace aed;
using namespace std;

template<typename T>
void show_list(const list<T> &L){	cout << "[ ";	for_each(L.begin(),L.end(),[](T v){cout << v << " ";});	cout << "] \n";}

// EJERCICIO 7
void list2tree(tree<int> &T, tree<int>::iterator& p, list<int> &L,list<int>::iterator &c){
	p = T.insert(p, *c);
	c++;
	int cantHijos = *c;
	c++;
	
	// Reconstruccion hijos
	tree<int>::iterator n = p.lchild();
	for(int i =0; i< cantHijos; i++){
		list2tree(T, n, L, c);
		n++;
	}
}

void list2tree(tree<int> &T, list<int> &L){
	list<int>::iterator c = L.begin();
	tree<int>::iterator p = T.begin() ;
	list2tree(T, p,L,c);
}

	
void tree2list(tree<int> &T, tree<int>::iterator& it, list<int> &L){
	if(it==T.end()) return;
	L.push_back(*it);
	int cantHijos =0;
	tree<int>::iterator it2 = it.lchild();
	while(it2!=T.end()){
		it2++;cantHijos++;
	}
	L.push_back(cantHijos);
	tree<int>::iterator it3 = it.lchild();
	while(it3!=T.end()){
		tree2list(T,it3,L);
		++it3;
	}
}
void tree2list(tree<int> &T, list<int > &L){
	tree<int>::iterator p = T.begin() ;
	tree2list(T,p,L);
}
	
// EJERCICIO 8
void preorden(tree<int> &T, list<int> &L, tree<int>::iterator it){
	if(it==T.end())return;
	L.push_back(*it);
	auto it2 = it.lchild();
	while(it2!=T.end()){
		preorden(T,L,it2++);
	}
}
list<int> preorden(tree<int> &T){
	list<int> L;
	preorden(T,L,T.begin());
	return L;
}
bool es_arbol_de_expansion(map<int,list<int>> M, tree<int> T){
	list<int> larbol = preorden(T);
	list<int> lmap;
	for(auto x: M) lmap.push_back(x.first);
	if(lmap.size()!=larbol.size()) return false;
	for(auto x: larbol){
		if(find(lmap.begin(),lmap.end(),x)==lmap.end()) return false;
	}
	return true;
	
}
int main() {
	string s_arbol("(1 2 (3 6 (7 11 12))(4 8) (5 9 (13 10))");	tree<int> arbol;			//if (lisp2tree(s_arbol,arbol)) tree2dot(arbol);	//else cout << "Error en crear arbol a partir de notacion de lisp \n";
	
	list<int> L = {1,4,7,0,2,0,6,0,3,2,4,0,5,0};
	tree<int> T;
	list2tree(T,L);tree2dot(T);
	
	tree<int> T2;
	list<int> L2 = {6, 5, 4, 0, 8, 0, 5, 2, 4, 0, 4, 0, 7, 0, 9, 0};
	//list2tree(T2, L2);	tree2dot(T2);
	list<int> L3;
	//tree2list(T2,L3); show_list(L3);
	
	map<int, list<int>> G = {
		{1, {2,6}},
	{2, {1,3,4,5}},
		{3, {2,5,7}},
	{4, {2,6}},
		{5, {2,3}},
	{6, {1,4,7}},
		{7, {3,6}}
	};
	cout<<es_arbol_de_expansion(G, T);
	return 0;
}

