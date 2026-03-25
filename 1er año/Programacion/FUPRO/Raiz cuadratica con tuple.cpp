#include <iostream>
#include <cmath>
#include <tuple>
using namespace std;
tuple<int, int> GetRaices(int a, int b, int c) {
	float r1,r2;
	r1= (-b+sqrt(b*b-4*a*c))/2*a;
	r2= (-b-sqrt(b*b-4*a*c))/2*a;
	return make_tuple(r1,r2) ;
}

int main() {
	int a,b,c;
	float r1, r2;
	cin>>a>>b>>c;
	tie(r1,r2) = GetRaices(a,b,c);
	cout<<"Raiz 1: "<<r1<<endl<<"Raiz 2: "<<r2;
	
	
	return 0;
}

