#include <iostream>
#include <btree.hpp>
#include <graphviz.hpp>
#include <lisp.hpp>
#include <climits>
using namespace aed;
using namespace std;

/// EJERCICIO 6
bool es_menor(btree<int> &A,btree<int>::iterator itA, btree<int> &B, btree<int>::iterator itB){
	if(itA==A.end() && itB==B.end()) return false;
	if(itA==A.end()) return true;
	if(itB==B.end()) return false;
	
	if(*itA<*itB) return true;
	if(*itA>*itB) return false;
	
	if(es_menor(A, itA.left(),B,itB.left())) return true;	
	if(es_menor(B, itB.left(),A,itA.left())) return false;
	return es_menor(A, itA.right(),B,itB.right());
}
bool es_menor(btree<int> &A,btree<int> &B){
	return es_menor(A,A.begin(),B,B.begin());
}
	
/// EJERCICIO 7
bool contenido(btree<int> &A,  btree<int> &B, btree<int>::iterator itA,btree<int>::iterator itB){
	bool condicIzq,condicDer;		if( itA==A.end()&&itB!=B.end() ) { 		return true;	} else if( itA!=A.end()&&itB==B.end() ) { 		return false;			} else if( itA==A.end()&&itB==B.end() ){ 		return true;			}else if( itA!=A.end()&&itB!=B.end() ){ 				if( *itA<*itB ){ 			condicIzq = contenido(A, B, itA.left(),itB.left());			condicDer = contenido(A, B, itA.right(),itB.right());		}else{ 			return false;		}	}	return (condicIzq && condicDer);
	
}
bool contenido(btree<int> &A, btree<int> &B){
	return contenido(A, B, A.begin(),B.begin());
}
	
/// EJERCICIO 8
bool is_balanced(btree<int> &T,btree<int>::iterator it, int &altura){
	altura=-1;
	if(it==T.end()) return true;
	
	btree<int>::iterator itl = it.left();
	btree<int>::iterator itr = it.right();
	int al,ar;
	altura = INT_MAX;
	
	if(!is_balanced(T, itl, al)) return false;
	if(!is_balanced(T, itr, ar)) return false;
	
	altura=( al > ar ? al : ar)+1;
	return abs(al-ar)<=1;
	
	/*if(it.left()==T.end() && it.right()==T.end()) return true;
	if(it.left()==T.end() && it.right().left()==T.end() && it.right().right()==T.end()) return true;
	if(it.right()==T.end() && it.left().left()==T.end() && it.left().right()==T.end()) return true;
	
	if(it.left()!=T.end() && it.right()!=T.end()){
		bool condIzq, condDer;
		condIzq = is_balanced(T,it.left());
		condDer = is_balanced(T, it.right());
		return (condIzq && condDer);
	}else{
		return false;
	}*/
	
}
bool is_balanced(btree<int> &T){
	int altura;
	return is_balanced(T,T.begin(),altura);
}

int main() {
	btree<int> T;
	//lisp2btree("(1 (2 4 (5 6 9)) (3 4 (5 6 9)))", T);
	lisp2btree("(1 2 (3 . 5)", T);
	btree2dot(T, "arbol");
	cout<<is_balanced(T);
	return 0;
}







