#include <iostream>
#include <list>
#include <string>

using namespace std;

void show_list(list<int>& L) {
	cout<<"(";
	for(list<int>::iterator it=L.begin();it!=L.end();it++) {
		cout<<*it<<" ";
	}
	cout<<")";
}

void show_list(list<string>& L) {
	cout<<"(";
	for(list<string>::iterator it=L.begin();it!=L.end();it++) {
		cout<<*it<<" ";
	}
	cout<<")";
}

/// Problema de Josephus
list<string> josephus(list<string>& nombres, int n) {
	auto it=nombres.begin();
	//hago una lista con los eliminados para poner el orden
	list<string> eliminados;
	while (!nombres.empty()){
		for (int i=0;i<n;++i){
			++it;
			if(it==nombres.end()){
				//si la list de nombres lleg oal final y todavia faltan numero para llegar a n, mando el iterador al principio de list asi sigue ocntando
				it=nombres.begin();
			}
		}
		eliminados.push_back(*it);
		it=nombres.erase(it);
		//si no esta al final del array sigue el ciclo en el sgte, pero verifico si esta en el final p las dudas
		if (it==nombres.end()){
			it=nombres.begin();
		}
	}
	return eliminados;
}


int main(int argc, char *argv[]) {
	list<string> nombres = {"roberto", "maria", "juana", "pepe", "daniel", "rosa"};
	show_list(nombres);	
	list<string> resultado = josephus(nombres, 2);
	
	show_list(resultado);	
	
	return 0;
}





