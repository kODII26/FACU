#include <iostream>
#include <btree.hpp>
#include <lisp.hpp>
#include <graphviz.hpp>
using namespace aed;
using namespace std;

/// EJERCICIO 1 - ListarAB
void orden_prev(btree<int>& T,btree<int>::iterator it){
	if(it==T.end()) return;
	cout<<*it<<" ";
	orden_prev(T, it.left());
	orden_prev(T,it.right());
}
void orden_post(btree<int> T, btree<int>::iterator it){
	if(it==T.end()) return;
	orden_post(T, it.left());
	orden_post(T, it.right());
	cout<<*it<<" ";
}
void orden_sim(btree<int> &T, btree<int>::iterator it){
	if(it==T.end()) return;
	orden_sim(T, it.left());
	cout<<*it<<" ";
	orden_sim(T, it.right());
}
	
/// EJERCICIO 2 - VariosAB
// a. Determinar si dos árboles tienen la misma estructura
bool semejantes(btree<int> &A, btree<int>::iterator itA, btree<int>& B, btree<int>::iterator itB){
	bool valorIzq, valorDer;
	if(itA==A.end() xor itB==B.end()){
		return false;
	}else if(itA==A.end()){
		return true;
	}else{
		valorIzq = semejantes(A,itA.left(),B,itB.left());
		valorDer = semejantes(A,itA.right(),B,itB.right());
		return (valorIzq && valorDer);
	}
}
bool semejantes(btree<int> &A, btree<int>& B){
	return semejantes(A,A.begin(),B,B.begin());
}
	
// b. Determinar si la estructura de un arbol es la espejada de otro.
bool espejados(btree<int> &A, btree<int>::iterator itA, btree<int> &B, btree<int>::iterator itB){
	bool valorIzq, valorDer;
	if(itA==A.end() xor itB==B.end()){
		return false;
	}else if(itA==A.end()){
		return true;
	}else{
		valorIzq = espejados(A, itA.left(),B,itB.right());
		valorDer = espejados(A, itA.right(), B, itB.left());
		return(valorIzq && valorDer);
	}
}
bool espejados(btree<int> &A, btree<int> &B){
	return espejados(A,A.begin(),B,B.begin());
}

// c. Determina si dos arboles son iguales, en estructura y contenido.
bool iguales(btree<int> &A, btree<int>::iterator itA, btree<int>& B, btree<int>::iterator itB){
	bool valorIzq, valorDer;
	if(itA==A.end() xor itB==B.end()){
		return false;
	}else if(itA==A.end()){
		return true;
	}else if(*itA!=*itB){
		return false;
	}else{
		valorIzq = iguales(A,itA.left(),B,itB.left());
		valorDer = iguales(A,itA.right(),B,itB.right());
		return (valorIzq && valorDer);
	}
}
bool iguales(btree<int> &A, btree<int>& B){
	return iguales(A,A.begin(),B,B.begin());
}

// d. Copiar un arbol en otro en forma espejada.
void copia_espejada(btree<int> &A, btree<int>::iterator itA){
	btree<int> T;
	if(itA==A.end()){
		return;
	}else{
		T.splice(T.begin(),itA.left());
		A.splice(itA.left(),itA.right());
		A.splice(itA.right(), T.begin());
		
		copia_espejada(A, itA.left());
		copia_espejada(A, itA.right());
	}
}
void copia_espejada(btree<int> &A){
	copia_espejada(A,A.begin());
}
	
	
int main() {
	btree<int> T;
	
	lisp2btree("(1 (2 . 3) (6 . 7))", T);
	
	btree2dot(T);
	
	cout<<"Orden prev:"<<endl;
	orden_prev(T, T.begin());
	cout<<endl;
	
	cout<<"Orden prev:"<<endl;
	orden_post(T, T.begin());
	cout<<endl;
	
	cout<<"Orden sim:"<<endl;
	orden_sim(T, T.begin());
	cout<<endl;
	return 0;
}







