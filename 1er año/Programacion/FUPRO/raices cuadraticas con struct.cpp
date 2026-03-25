#include <iostream>
#include <cmath>
using namespace std;

struct raices {
	float r1;
	float r2;
	float a,b,c;
	float getRaices();
};

raices getRaices(raices x) {
	raices r;
	r.r1= (-x.b+sqrt(x.b*x.b-4*x.a*x.c))/2*x.a;
	r.r2= (-x.b-sqrt(x.b*x.b-4*x.a*x.c))/2*x.a;
	
	return r;
}

int main() {
	raices x;
	cin>>x.a>>x.b>>x.c;
	raices r = getRaices(x);
	cout<<"las raices son : "<<endl<<r.r1<<endl<<r.r2;
	return 0;
}
