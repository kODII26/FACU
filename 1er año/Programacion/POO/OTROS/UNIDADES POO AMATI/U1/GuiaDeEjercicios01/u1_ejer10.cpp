#include <iostream>
using namespace std;

int main() {
	int f=10,c=6;
	
	//RESERVAR MEMORIA
	int (*v)[10] = new int[6][10];
	
	//DAR VALORES.
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			v[i][j] = rand()%90+10;//*(v[i]+j) = v[i][j]
		}
	}
	
	
	for(int i=0; i<f; ++i) {
		for(int j=0; j<c; ++j) {
			cout<<" "<<v[i][j];
		}
		cout<<endl;
	}
	
	
	
	return 0;
}

