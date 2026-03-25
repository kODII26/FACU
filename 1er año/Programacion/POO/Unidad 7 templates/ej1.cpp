#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
template<typename T>
T Mayor (const vector<T> &v){
	T may=v[0];
	for (size_t i=0;i<v.size();++i){
		if (v[i]>may)
			may= v[i];
	}
	return may;
}
template<typename T>
T Mayor (T a, T b){
	if (a>b)
		return a;
	else
		return b;
}
struct Persona{
	string nombre;
	int dni;
};

template<typename T, typename T2>
T Mayor (const vector<T> &v, T2 PFnc){
	T may=v[0];
	for (size_t i=1;i<v.size();++i){
		if (PFnc(v[i],may))
			may= v[i];
	}
	return may;
}
bool Mayor_nom (Persona a1, Persona a2){
	return a1.nombre>a2.nombre;
}
bool Mayor_dni (const Persona &a1,const Persona &a2){
	return a1.dni>a2.dni;
}
int main() {
	int a=4,b=5;
	float c=10.01,d=10;
	string h="asd",g="sd";
	cout<<"El mayor entre enteros es: "<<Mayor(a,b)<<endl;
	cout<<"El mayor entre floats es: "<<Mayor(c,d)<<endl;
	cout<<"El mayor entre strings es: "<<Mayor(g,h)<<endl;
	
	vector<float> f(10);
	for (int i=0;i<10;++i){
		f[i]= rand()%1000/100.0;
	}
	cout<<"El mayor entre el vector de floats es: "<<Mayor(f)<<endl;
	
	vector<Persona> v(2);
	v[0].nombre= "Justo"; v[0].dni=100;
	v[1].nombre= "Luis"; v[1].dni=11;
	Persona mayor_nombre= Mayor(v,Mayor_nom);
	Persona mayor_dni= Mayor(v,Mayor_dni);
	
	cout<<"La persona con mayor nombre es: "<<mayor_nombre.nombre<<endl;
	cout<<"La persona con mayor dni es: "<<mayor_dni.nombre;
	return 0;
}

