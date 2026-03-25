#include <iostream>
#include <set>

using namespace std;

void show_set(set<int> A)
{
	cout << "{ ";
	for (auto i:A)
	{
		cout << i <<" ";		
	}
	cout << "}" << endl;
}




//version eficiente
//O(n) = n
void set_union(set<int> &A, set<int> &B, set<int> &C)
{
	set<int>::iterator itA = A.begin();
	set<int>::iterator itB = B.begin();
	
	while(itA!=A.end() &&  itB!=B.end()){
		if(*itA < *itB){
			C.insert(C.end(),*itA);
			++itA;
		}else if(*itB<*itA){
			C.insert(C.end(),*itB);
			++itB;
		}
		else{
			C.insert(C.end(),*itA);
			++itA;++itB;
		}
	}
	while(itA!=A.end()){
		C.insert(C.end(),*itA);
		++itA;
	}
	while(itB!=B.end()){
		C.insert(C.end(),*itB);
		++itB;
	}
	
}
void set_union2(set<int> &A, set<int> &B, set<int> &C){
	C=A;
	C.insert(B.begin(),B.end());
}

void set_intersection(set<int> &A, set<int> &B, set<int> &C){
	set<int>::iterator itA = A.begin();
	set<int>::iterator itB = B.begin();
	
	while(itA!=A.end() &&  itB!=B.end()){
		if(*itA < *itB){
			++itA;
		}else if(*itB<*itA){
			itB++;
		}
		else{
			C.insert(C.end(),*itA);
			++itA;++itB;
		}
	}
}

void set_difference(set<int> &A,set<int> &B,set<int> &C){	C.clear();		set<int>::iterator itA = A.begin();	set<int>::iterator itB = B.begin();		while( itA!=A.end()&&itB!=B.end() ){		if(*itA<*itB){			C.insert(C.end(),*itA);			itA++;		}		else if(*itA>*itB){			itB++;		}else{		//son iguales			itA++; itB++;		}			}	while(itA!=A.end()){		C.insert(C.end(),*itA);		itA++;	}	}
	

int main()
{
	set<int> A = {1,2,3,4};
	set<int> B = {3,4,5,6};
	set<int> C;
	
	set_intersection(A,B,C);
	show_set(C);
	
	return 0;
}
