#include <iostream>
#include <list>
#include <stack>
#include <queue>
#include <iomanip>
using namespace std;



// EJERCICIO 2
bool inverso(list<char>&L){
	//suppongase sin espacios y par
	list<char>::iterator it = L.begin();
	stack<char> pila; queue<char> cola;
	int i =0;
	while(i<L.size()/2){
		pila.push(*it);
		i++;it++;
	}
	while(i<L.size()){
		cola.push(*it);
		i++;it++;
	}
	
	while(!pila.empty()){
		if(pila.top()!=cola.front()){
			return false;
		}
		pila.pop();cola.pop();
	}
	return true;
}
	
// EJERCICIO 3

	

// EJERCICIO 4 
void sort(list<int> &L){
	stack<int> pila;
	list<int>::iterator it =L.begin();
	list<int>::iterator it_lowest = it;
	while(!L.empty()){
		it =L.begin();
		it_lowest = it;
		advance(it,1);
		while(it!=L.end()){
			if(*it<*it_lowest) it_lowest=it;
			advance(it,1);
		}
		pila.push(*it_lowest);
		L.erase(it_lowest);
	}
	while(!pila.empty()){
		L.insert(L.end(),pila.top());
		pila.pop();
	}
}
	
// EJERCICIO 5
void sort6(list<int> &L){
	queue<int> cola;
	list<int>::iterator it =L.begin();
	list<int>::iterator it_lowest = it;
	while(!L.empty()){
		it =L.begin();
		it_lowest = it;
		advance(it,1);
		while(it!=L.end()){
			if(*it<*it_lowest) it_lowest=it;
			advance(it,1);
		}
		cola.push(*it_lowest);
		L.erase(it_lowest);
	}
	while(!cola.empty()){
		L.insert(L.end(),cola.front());
		cola.pop();
	}
}
	

int main(int argc, char *argv[]) {
	
	list<char> z({'a','b','c','c','h','a'});
	cout<<inverso(z);
	return 0;
}

