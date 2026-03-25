#include <iostream>
using namespace std;

/// EJERCICIO 5
void ord2bin(tree<int>&T, btree<int>& B, tree<int>::iterator itT, btree<int>::iterator itB){
	if(itT == T.end() || *itT==-1) return;
	
	itB = B.insert(itB,*itT);
	
	if(itT.lchild()!=T.end()){
		ord2bin(T,B,itT.lchild(),itB.left());
		ord2bin(T,B,itT.lchild().right(),itB.right());
	}
}
void ord2bin(tree<int> &T, btree<int> &B){
	ord2bin(T,B,T.begin(),B.begin());
}

int main() {
	
	return 0;
}







