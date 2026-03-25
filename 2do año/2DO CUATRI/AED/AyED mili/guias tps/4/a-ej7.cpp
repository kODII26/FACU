#include <iostream>
#include <list>
#include <set>
#include <cmath>
using namespace std;

void show_set(set<int> A)
{
	cout << "{ ";
	for (auto i:A)
	{
		cout << i <<" ";		
	}
	cout << "} ";
}

void showl_set(list<set<int>> L){
	cout<<"L = {";
	for(auto s: L){
		show_set(s);
	}
	cout<<"}"<<endl;
}

list<set<int>> subk(set<int> &S, int k){
	list<set<int>> L;
	set<int>::iterator it = S.begin();
	while(it!=S.end()){
		int val = *it;
		it = S.erase(it);
		for(int i=0; i<ceil(S.size());i++){
			set<int> tmp;
			tmp.insert(tmp.begin(),val);
			set<int>::iterator it2 = S.begin();
			for(int aux=0; aux<(k-1)*i; aux++) it2++;
			int cont =1;
			while(it2!=S.end() && cont<k){
				tmp.insert(tmp.end(), *it2);
				cont++; it2++;
			}
			L.push_back(tmp);
		}
	}
	return L;
}
	
// otra estrategia: recorrer todos los subconjuntos, filtrar por tamaño

int main() {
	
	set<int> S= {1,2,3,4,5,6};
	int k = 2;
	showl_set(subk(S,k));
	
	return 0;
}







