#include <iostream>
#include <tuple>
#include <cmath>
using namespace std;

float determinante(float a,float b,float c){
	float det = b*b-4*a*c;
	return det;
}
	
	tuple<float,float> raices(float det,float a,float b,float c){
		float x1,x2;
		x1=(-b+sqrt(det))/(2*a);
		x2=(-b-sqrt(det))/(2*a);
		
		return make_tuple(x1,x2);
	}
		
		
		
		int main() {
			float a,b,c;
			cout<<"Ingrese los valores de a,b y c (en orden)."<<endl;
			cin>>a>>b>>c;
			float det = determinante(a,b,c);
			cout<<"El determinante es: "<< det <<endl;
			float x1,x2;
			tie(x1,x2) = raices(det,a,b,c);
			cout << "La raiz uno es: " << x1 <<endl;
			cout << "La raiz dos es: " << x2 <<endl;
			return 0;
		}
