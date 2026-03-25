#include <iostream>
#include <cmath>
using namespace std;
float hipot(float c1, float c2, float h){
	h = sqrt(c1*c1+c2*c2);
	return h;
}
	
int main(int argc, char *argv[]) {
	float c1,c2,h;
	cout<<"Ingrese cateto1 " ; cin>> c1;
	cout<<"Ingrese cateto2 " ; cin>> c2;
	
	cout<<"La hipotenusa es: "<<hipot(c1,c2,h);
	return 0;
}

