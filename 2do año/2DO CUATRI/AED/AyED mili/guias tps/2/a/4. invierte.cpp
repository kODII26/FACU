#include <iostream>
using namespace std;

void invert(list<int> &L){
	auto it1 = l.begin();
	auto it2 = L.end();
	it2--;
	while(it1!=it2){
		int aux = *it1;
		*it1=*it2;
		*it2=aux;
		it1++;
		if(it1!=it2)
			it2--;
	}
}

int main(int argc, char *argv[]) {
	
	return 0;
}

