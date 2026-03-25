#include <iostream>
#include <list>

using namespace std;

void show_list(list<int>& L){
	cout<<"(";
	for(auto it = L.begin();it!=L.end();it++){
		cout<<*it<<" ";		
	}
	cout<<")"<<endl;
}
	
	
void ascendente1(list<int> &L, list<list<int>> &LL){
	auto it1=L.begin();
	list<int> aux;
	aux.push_back(*it1);// el primer elemento ya lo meto al auxiliar asi puedo comparar con ese
	++it1; 				
	
	if (L.empty()) return;
	while (it1!=L.end()){
		if (*it1>aux.back()){ //back() muestra el ult elemnto de la lista
			aux.push_back(*it1); //si es mayor va guardando en orden ascendente
		}else{
			LL.push_back(aux); //si es menor, guarda la lista en la LL y resetea el algoritmo
			aux.clear();
			aux.push_back(*it1);
		}
		++it1;
		
	}
	LL.push_back(aux); //asigno la ultima lista ya que la parte que guarda datos es nomas si encuentra uno menor
}						//por lo que es posible que termine el while y el aux quede cargado con una lista ascendente y no se guarde

int main() {
	list<int> L = {4,4,1, 2, 3, 2, 4, 7, 7, 5, 6, 8};
	
	list<list<int>> LL;
	
	ascendente1(L,LL);
	
	cout<<endl<<"Ascendente con lista de listas: "<<endl;
	for(auto lista:LL){
		show_list(lista);
	}
	
	
	return 0;
}
