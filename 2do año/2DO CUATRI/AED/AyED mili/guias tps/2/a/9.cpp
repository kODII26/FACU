#include <iostream>
#include <list>
using namespace std;

bool menor(int x, int y){
	return x<y;
}

bool mayor(int x, int y){
	return x>y;
}

bool dist(int x, int y){
	if(x<0) x= -x;
	if(y<0) y=-y;
	return x<y;
}
	
void ordena(list<int> &L, bool (*f)(int,int)){
	
	if( L.empty() ) return;
	
	// con burbuja
	for( list<int>::iterator it=L.begin(); it!=L.end(); it++ ) { 
		for( list<int>::iterator it2=prev(L.end()); it2!=it; it2-- ) { 
			if( f(*it2,*prev(it2)) ){
				int tmp = *prev(it2);
				*prev(it2) = *it2;
				*it2 = tmp;
			}
		}
	}
}

int main(int argc, char *argv[]) {
	
	return 0;
}

