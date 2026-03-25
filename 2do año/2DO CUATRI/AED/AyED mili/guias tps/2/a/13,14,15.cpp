#include <iostream>
#include <list>
#include <iomanip>
using namespace std;

void showl(list<int> L){
	for(int &x: L) cout<<x<<", ";
	cout<<endl;
}
	
int sumar_els(list<int> &L){
	int suma=0;
	for(int &x: L) suma +=x;
	return suma;
}

// EJERCICO 13
list<int> max_sublist(list<int> &L){

	list<int> Lmax;
	list<int> aux;
	list<int>::iterator it1 = L.begin();
	list<int>::iterator it2 = L.end();
	
	while(it1!=L.end()){
		//analizar todas las posibles sublistas que empiezan por este elemento
		list<int>::iterator it_aux = it1;
		list<int> aux2;
		aux.push_back(*it_aux);
		while(it_aux!=it2){
			aux2.push_back(*it_aux);
			if(sumar_els(aux2)>sumar_els(aux)){
				aux=aux2;
			}
			++it_aux;
		}
		if(sumar_els(aux)>sumar_els(Lmax) /*|| (sumar_els(aux)==sumar_els(Lmax) and aux.size()<Lmax.size())*/){
			Lmax=aux;
		}
		aux.erase(aux.begin(),aux.end());
		it1++;
	}
	return Lmax;
}


// EJERCICIO 14
void merge(list<int> &L1, list<int> &L2, list<int>& L){
	list<int>::iterator it1 = L1.begin();
	list<int>::iterator it2 = L2.begin();
	while(it1!=L1.end() and it2!=L2.end()){
		if(*it1<*it2){
			L.push_back(*it1);
			it1++;
		}else{
			L.push_back(*it2);
			it2++;
		}
	}
	if(it1==L.end()){
		while(it2!=L2.end()){
			L.push_back(*it2);
			it2++;
		}
	}else{
		while(it1!=L1.end()){
			L.push_back(*it1);
			it1++;
		}
	}
}
	
// EJERCICIO 15
void mergesort(list<int> &L){
	if(L.size()<=1){
		return;
	}else{
		list<int> L1,L2;
		L1.swap(L);
		list<int>::iterator it1=L1.begin();
		for(unsigned int i=0;i<L1.size()/2;i++) it1++;
		L2.splice(L2.begin(),L1,it1,L1.end());
		mergesort(L1);
		mergesort(L2);
		merge(L1,L2,L);
	}
}

int main(int argc, char *argv[]) {
	list<int>  LA = {1,2,-5,4,3,-3,2};
	//list<int>  LB = {5,-3,-5,1,7,-2};
	//list<int>  LC = {4,-3,11,-2};
	showl(max_sublist(LA));
	list<int> L1 = {1,3,6,11}, L2 = {2,4,6,10}, L;
	//merge(L1,L2,L);
	//showl(L);
	mergesort(L1);
	showl(L1);
	return 0;
}

