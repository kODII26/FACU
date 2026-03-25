#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

void selection_sort(list<int> &L){
	for (auto it1=L.begin();it1!=L.end();++it1){
		auto it_min= min_element(it1,L.end());
		iter_swap(it_min,it1);
	}
}

void show_list(list<int> &L){
	for (auto x: L){
		cout<< x <<", ";
	}
	cout<<endl;
}
	
int main(int argc, char *argv[]) {
	list<int> L={5,3,1,2,7};

	show_list(L);
	selection_sort(L);
	show_list(L);
	return 0;
}

