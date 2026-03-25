#include <iostream>
using namespace std;
int facto(int x) { 
	if (x==1) {
		return 1;
	} else {
		int aux = facto (x-1);
		return x*aux;
	}
}

int main(int argc, char *argv[]) {
	int x;
	cin>>x;
	facto( x);
	cout<<facto( x)<<endl;
	return 0;
}

