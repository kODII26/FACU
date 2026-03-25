#include <iostream>
using namespace std;

int main() {
	int a=90;
	int *p=&a;
	int b=(*p)++;
	int *q=p+2;
	cout<<p<<" "<<*p<<endl;
	cout<<q<<" "<<*q<<endl;
	a=*(++q);
	b=*(p++);
	(*p)++;
	cout<<p<<" "<<&p<<endl;
	cout<<q<<" "<<&q;
	return 0;
}

