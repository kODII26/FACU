#include <iostream>
#include <tuple>
using namespace std;
void eliminaRep (int *v, int &cant){
	for (int i=0;i<cant-1;i++){
		for (int c=i+1;c<cant;c++){
			if (*(v+i)==*(v+c)){
				*(v+c) = *(v+cant-1);
				*(v+i) = *(v+cant-2);
				cant--;
				cant--;
			}
		}
	}
}

tuple<int*,int*> retornarReps (int *v, int n, int inicio) {
	int *r1, *r2;
	for (int i=inicio;i<n-1;i++){
		for (int c=i+1;c<n;c++){
			if (*(v+i)==*(v+c)){
				r1=(v+i);
				r2=(v+c);
				return make_tuple(r1,r2);
			}
		}
	}
	r1=nullptr;
	r2=nullptr;
	return make_tuple(r1,r2);
}

int main() {
	int n=6;
	int *p= new int[n];
	*(p+0)= 2; *(p+1)= 3;*(p+2)= 1;*(p+3)= 2;*(p+4)= 5;*(p+5)=6;
	cout<<"------------------------------------"<<endl;
	for (int i=0; i<n;++i){
		cout<<*(p+i)<<endl;
	}
	cout<<"-------------------------------------"<<endl;
	int *r1,*r2;
	int inicio=0;
	tie(r1,r2)= retornarReps(p,n,inicio);
	while (r1!=nullptr){
		if (r1==nullptr){
			cout<<"No hay elementos repetidos"<<endl;
		} else {
			cout<<"Los elementos repetidos son: "<<endl;
			cout<<*r1<<" Direccion: "<<r1<<" Posicion: "<<r1-p<<endl;
			cout<<*r2<<" Direccion: "<<r2<<" Posicion: "<<r2-p<<endl;
			inicio++;
			tie(r1,r2)= retornarReps(p,n,inicio);
		};
	}
	eliminaRep(p,n);
	cout<<"------------------------------------"<<endl;
	for (int i=0; i<n;++i){
		cout<<*(p+i)<<endl;
	}
	cout<<"-------------------------------------"<<endl;
	return 0;
}

