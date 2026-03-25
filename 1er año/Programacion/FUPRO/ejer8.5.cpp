#include <iostream>
#include <tuple>
using namespace std;
void intercambia(char &c, char &d) {
	int aux= c;
	c= d;
	d= aux;
}
void intercambia(int &a, int &b) {
	int aux= a;
	a= b;
	b= aux;
}
int main() {
	char c,d;
	int a,b, opcion;
	cout<<"1 para char 2 para int"<<endl;
	cin>>opcion;
	if (opcion == 1) 
		cin>>c>>d;
	if (opcion == 2)
		cin>>a>>b;
	intercambia(a,b);
	intercambia(c,d);
	if (opcion == 1) 
		cout<<c<<endl<<d;
	if (opcion == 2)
		cout<<a<<endl<<b;
	return 0;
}
