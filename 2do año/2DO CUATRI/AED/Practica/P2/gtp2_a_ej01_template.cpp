#include <iostream>
#include <list>
#include <ctime>
using namespace std;

void show_list(list<int> &L){
	for (auto x: L){
		cout<< x <<", ";
	}
	cout<<endl;
}

void basic_sort(list<int> &L){
	list<int> L2;
	
	while (!L.empty()){
		auto it=L.begin();
		auto it_aux=L.begin();
		while (it!=L.end()){ //Este while se podria reemplazar con la funcion min_element para que sea mas corto el codigo
			if (*it<=*it_aux){
				it_aux = it;
			}
			it++;
		}
		L2.push_back(*it_aux);
		L.erase(it_aux);
	}
	L.swap(L2);
}


int main(int argc, char *argv[]) {
	list<int> L= {4,2,6,1,3,5};
	show_list(L);
	basic_sort(L);
	show_list(L);
	return 0;
}

