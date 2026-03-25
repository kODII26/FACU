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

bool menor(int x, int y){
	return x<y;
}
bool mayor(int x, int y){
	return x>y;
}
bool dist(int x, int y){
	return abs(x)<abs(y);
}

void ordena(list<int> &L, bool (*f)(int,int)){
	list<int> aux;
	while (!L.empty()){
		auto it=L.begin();
		auto escribe= L.begin();
		while (it!=L.end()){
			if (f(*it,*escribe)){ //si se cumple la funcion(cualquiera que sea) entonces me guardo 
				escribe=it;		// ese valor, lo escribo en la lista aux y luego lo borro de la original
			}
			++it; //cond para salir del while
		}
		aux.push_back(*escribe);
		L.erase(escribe); //cond para salir del while
	}
	L.swap(aux);
}

int main() {
	cout<<endl<<"Lista: "<<endl;
	list<int> L2 = {1, 2, 3, -2, 4, -7, 7, -5, 6, 9};
	show_list(L2);
	
	cout<<endl<<"Ordenamientos: (menor)"<<endl;
	ordena(L2,menor);
	show_list(L2);
	
	cout<<endl<<"Ordenamientos: (mayor)"<<endl;
	ordena(L2,mayor);
	show_list(L2);
	
	cout<<endl<<"Ordenamientos: (dist)"<<endl;
	ordena(L2,dist);
	show_list(L2);
	return 0;
}







