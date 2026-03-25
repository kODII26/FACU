#include <iostream>
using namespace std;
int* modificaVector (int *inicio, int*fin, int m){
	int cantfinal= (fin-inicio+1)*m;
	int *v=new int[cantfinal];
	int c=0; int i=0;
	while (c<cantfinal){
		for (int f=0;f<m;++f){
			*(v+c)=*(inicio+i); 
			c++;
		}
		i++;
	}
	
	return v;
}
int main() {
	int m=6;
	int *fin;
	int *inicio= new int[3];
	inicio[0]=2;
	inicio[1]=5;
	inicio[2]=4;
	fin=&inicio[2];
	int *vfinal= modificaVector (inicio,fin,m);
	int cant= (fin-inicio+1)*m;
	for (int i=0;i<cant;++i){
		cout<<*(vfinal+i)<<" ";
	}
	return 0;
}

