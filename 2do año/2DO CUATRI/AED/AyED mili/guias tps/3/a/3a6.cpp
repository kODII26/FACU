#include <iostream>
#include <tree.hpp>
#include <graphviz.hpp>#include <lisp.hpp>#include <list>
#include <iomanip>
using namespace aed;
using namespace std;

template<typename T>void show_list(const list<T> &L){	cout << "[ ";	for_each(L.begin(),L.end(),[](T v){cout << v << " ";});	cout << "] \n";}

// EJERCICIO 3
void count_level(tree<int> &T, tree<int>::iterator p, int &nnodes, int &current_level, int l){
	if(p==T.end()) return;
	if(current_level==l)nnodes++;
	else{
		tree<int>::iterator c = p.lchild();
		current_level++;
		while(c!=T.end()){
			count_level(T, c, nnodes, current_level, l);
			c++;
		}
		current_level--;
	}
}
int count_level(tree<int> &T, int l){
	int nnodes=0;
	int current_level =0;
	count_level(T, T.begin(),nnodes,current_level,l);
	return nnodes;
}
	
// EJERCICIO 4
void orden_de_nivel(tree<int> &T, tree<int>::iterator p, map<int, list<int>> &M,int &current_level){
	if(p==T.end()) return;
	M[current_level].push_back(*p);
	tree<int>::iterator c = p.lchild();
	current_level++;
	while(c!= T.end()){
		orden_de_nivel(T,c,M,current_level);
		c++;
	}
	current_level--;
}
void orden_de_nivel(tree<int> &T){
	int current_level =0;
	map<int, list<int>> M;
	list<int> L;
	orden_de_nivel(T, T.begin(),M,current_level);
	
	for(auto &x: M){
		for(auto &y: x.second) L.push_back(y);
	}
	show_list(L);
}
	


// EJERCICIO 5
bool odd(int x){
	return x%2;
}
void count_if(tree<int> &T, tree<int>::iterator p, bool (*pred)(int x), int &nnodes){
	if(p==T.end()) return;
	if(pred(*p)) nnodes++;
	tree<int>::iterator c = p.lchild();
	while(c!=T.end()){
		count_if(T,c++,pred,nnodes);
	}
}
int count_if(tree<int> &T, bool (*pred)(int x)){
	int nnodes=0;
	count_if(T, T.begin(), pred, nnodes);
	return nnodes;
}


// EJERCICIO 6
void list_if(tree<int> &T,tree<int>::iterator p,list<int> &L,bool (*pred)(int x)){
	if(p==T.end())return;
	if(pred(*p)) L.push_back(*p);
	tree<int>::iterator c = p.lchild();
	while(c!=T.end()){
		list_if(T,c++,L,pred);
	}
}
void list_if(tree<int> &T,list<int> &L,bool (*pred)(int x)){
	list_if(T,T.begin(),L,pred);
}

int main() {
	string s_arbol("(1 2 (3 6 (7 11 12))(4 8) (5 9 (13 10))");	tree<int> arbol;			if (lisp2tree(s_arbol,arbol)) tree2dot(arbol);	else cout << "Error en crear arbol a partir de notacion de lisp \n";
	
	cout<<count_if(arbol,odd)<<endl;
	list<int> L;
	list_if(arbol,L,odd);show_list(L);
	
	return 0;
}







