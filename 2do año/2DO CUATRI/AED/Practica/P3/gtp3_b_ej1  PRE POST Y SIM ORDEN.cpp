#include <iostream>
#include <lisp.hpp>
#include <graphviz.hpp>
#include <btree.hpp>
using namespace aed;
using namespace std;

/// ListarAB. Escribir procedimientos para listar un arbol
/// binario siguiendo los ordenes prefijo, simetrico y postfijo.
void orden_prev(btree<int>& T, btree<int>::iterator it) {
	if (it!=T.end()){
		cout<<*it<<" - ";
		orden_prev(T,it.left());
		orden_prev(T,it.right());
	}
}

void orden_post(btree<int>& T, btree<int>::iterator it) {
	if (it!=T.end()){
		orden_post(T,it.left());
		orden_post(T,it.right());
		cout<<*it<<" - ";
	}
}

void orden_sim(btree<int>& T, btree<int>::iterator it) {
	if (it!=T.end()){
		orden_sim(T,it.left());
		cout<<*it<<" - ";
		orden_sim(T,it.right());
		
	}
}

int main(int argc, char *argv[]) {
	btree<int> T;
	
	lisp2btree("(1 (2 3 4) (6 7 .))", T);
	
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
