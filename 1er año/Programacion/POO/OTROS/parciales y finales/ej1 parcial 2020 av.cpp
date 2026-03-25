#include <iostream>
#include <algorithm>
using namespace std;
int* intercala (int *p, int *p2,int cant,int cant2){
	if (cant2>cant){
		swap(cant2,cant);
		swap(p,p2);
	}
	
	int cantfinal= cant+cant2;
	int *v=new int[cantfinal];
	int c=0;
	for (int i=0;i<cant2+1;++i){
		*(v+i+c)= *(p+c);
		c++;
	}
	int x=0;
	for (int f=1;f<cant2+1;++f){
		*(v+f+x)= *(p2+x);
		++x;
	}
	x+=c;
	for (int i=x;i<cantfinal;++i){
		*(v+i)= *(p+c);
	}
	return v;
}

int main() {
	cout<<"ingrese cantidad v1"<<endl;
	int cant;cin>>cant;
	int *p=new int[cant];
	for (int i=0;i<cant;++i){
		cin>>*(p+i);
	}
	cout<<"ingrese cantidad v2"<<endl;
	int cant2;cin>>cant2;
	int *p2=new int[cant2];
	for (int i=0;i<cant2;++i){
		cin>>*(p2+i);
	}
	int *v= intercala(p,p2,cant,cant2);
	int cantfinal=cant+cant2;
	for (int i=0;i<cantfinal;++i){
		cout<<*(v+i)<<" ";
	}
	delete [] p;
	delete [] p2;
	delete [] v;
	
	return 0;
}

