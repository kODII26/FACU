#include <iostream>
using namespace std;

int mayor(int a, int b) {
	int may;
	if (a>b) {
		may = a;
	} else {
		may = b;
	}
	return may;
}
int mayor(int a, int b,int c) {
	int may;
	if (a>b && a>c) {
		may= a;
	}
	if (b>c && b>a) { 
		may = b;
	} else {
		may = c;
	}
	return may;
}


int main() {
	int a,b,c;
	
	cout<<"ingrese 3 numeros"<<endl;
	cin>>a>>b>>c;
	
	cout<<"el mayor es: "<<mayor(a,b,c);
	return 0;
}

