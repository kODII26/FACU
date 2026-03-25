#include <iostream>
#include <list>
#include <string>
#include <algorithm>
using namespace std;

list<string> josephus(list<string>& nombres, int n){
	list<string> orden;
	int cont=0;
	auto it = nombres.begin();
	
	while(!nombres.empty()){
		if(nombres.size()==1){
			orden.push_back(*it);
			break;
		}
		if(cont == n){
			orden.push_back(*it);
			it = nombres.erase(it);
			cont =0;
		}else{
			it++;
			cont++;
		}
		if(it == nombres.end()){
			it= nombres.begin();
		}
	}
	return orden;
}

bool is_palindromo(char* S){
	list<char> letras;
	to_list(S, letras);
	
	list<char>::iterator it1 = letras.begin();
	list<char>::iterator it2 = prev(letras.end());
	
	while (it1!=it2){
		if(*it1!=*it2) return false;
		it1++;
		if(it1!=it2) it2--;
	}
	return true;
}
	

void compacta(list<int> &L, list<int> &S){
	list<int>::iterator it1 = S.begin();
	list<int>::iterator it2 = L.begin();
	
	while(it1!=S.end() && it2!=L.end()){
		if(*it1>0){
			int cant = *it1;
			int sum = 0;
			list<int>::iterator it3 = it2;
			while(cant!=0 and !L.empty() and it2!=L.end()){
				sum+=*it2;
				it2++;cant--;
			}
			it2 = L.erase(it3,it2);
			it2 = L.insert(it2,sum);
			++it2;
		}
		it1++;
	}
}

int main(int argc, char *argv[]) {
	
	return 0;
}

