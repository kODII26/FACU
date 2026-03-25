#include <iostream>
#include <lisp.hpp>
#include <graphviz.hpp>
#include <btree.hpp>
using namespace aed;
using namespace std;

int cant_nodos_prof(btree<int> &A, btree<int>::iterator it, int prof, int& profActual){ 
	int cant_nodos = 0; 
	if(it == A.end()) return cant_nodos; 
	
	if(profActual >= prof)
		{ cant_nodos++; } 
	
	profActual++; 
	cant_nodos += cant_nodos_prof(A, it.left(), prof, profActual); 
	cant_nodos += cant_nodos_prof(A, it.right(), prof, profActual); 
	profActual--; 
	
	return cant_nodos; 
} 

	int cant_nodos_prof(btree<int> &A, int prof){ 
		int profActual = 0; 
		return cant_nodos_prof(A, A.begin(), prof, profActual); 
	} 

//auxiliar
void profundidad(btree<int> &A, btree<int>::iterator itA, int prof,  int& curr_nodes, int& curr_prof)
{
	if (itA != A.end()) {
		if (curr_prof >= prof) {
			curr_nodes++;			
		}
		
		curr_prof++;
		profundidad(A, itA.left(), prof, curr_nodes, curr_prof);
		profundidad(A, itA.right(), prof, curr_nodes, curr_prof);
		curr_prof--;
	}
	
	return;	
}

//wrapper
int profundidad(btree<int> &A, int prof)
{
	int curr_prof = 0;
	int curr_nodes = 0;
	
	btree<int>::iterator itA = A.begin();
	
	if (itA != A.end()) {
		profundidad(A, itA, prof, curr_nodes,curr_prof);
	}
	
	return curr_nodes;
		
}
	
int main(int argc, char *argv[]) {
	btree<int> T1;
	
	lisp2btree("(1 (2 4 .) (6 (7 . 5) .))", T1);
	btree2dot(T1);
	//cout << "Nodos: "<< profundidad(T1,6);
	cout << "Nodos: "<< profundidad(T1,2);
	
	return 0;
}
