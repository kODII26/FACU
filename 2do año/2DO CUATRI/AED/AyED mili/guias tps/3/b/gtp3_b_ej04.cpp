#include <iostream>
#include <lisp.hpp>
#include <graphviz.hpp>
#include <btree.hpp>
using namespace aed;
using namespace std;

void bin2ord(btree<int>& bT, tree<int>& T, btree<int>::iterator itbT, tree<int>::iterator itT) 
{
	if (itbT == bT.end()) return;
	
	itT = T.insert(itT, *itbT);
	
	btree<int>::iterator itbT_left = itbT.left();
	btree<int>::iterator itbT_right = itbT.right();
	
	// si es hoja salimos
	if (itbT_left == bT.end() && itbT_right == bT.end()) return;
	
	if (itbT_left != bT.end()) 
	{
		bin2ord(bT,T,itbT_left,itT.lchild());				
	} 
	else 
	{
		T.insert(itT.lchild(),-1);
	}
	
	if (itbT_right != bT.end()) 
	{	
		bin2ord(bT,T,itbT_right,itT.lchild().right());				
	}	
	else 
	{
		T.insert(itT.lchild().right(),-1);
	}
		
	//recursion 2020
//	if (itbT_left != bT.end() && itbT_right == bT.end()) 
//	{
//		bin2ord(bT,T,itbT_left,itT.lchild());
//		T.insert(itT.lchild().right(),-1);
//		
//	} 
//	else if (itbT_left == bT.end() && itbT_right != bT.end()) 
//	{
//		T.insert(itT.lchild(),-1);
//		bin2ord(bT,T,itbT_right,itT.lchild().right());				
//	}	
//	else 
//	{
//		bin2ord(bT,T,itbT_left,itT.lchild());
//		bin2ord(bT,T,itbT_right,itT.lchild().right());				
//	}
}

//wrapper

void bin2ord(btree<int>& bT, tree<int>& T) 
{
	bin2ord(bT, T, bT.begin(), T.begin());
}

int main(int argc, char *argv[]) {
	btree<int> bT;
	tree<int> T;
	
	lisp2btree("(1 (2 4 .) (6 (7 . 5) .))", bT);
	btree2dot(bT);	
	
	bin2ord(bT,T);
	tree2dot(T);
	
	return 0;
}
