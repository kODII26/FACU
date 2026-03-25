#include <iostream>
#include <map>
#include <list>
#include <climits>
using namespace std;

typedef map<char,map<char,int>> graphW;
const int inf = INT_MAX;

int Dijkstra(graphW& G, char ini, char fin, list<char>&path){
	map<char, bool> visitados;
	map<char, pair<int, char>> acum; //acum['C'] ---> (3, 'A')
	
	for (auto &node: G){
		acum[node.first] = {inf,'-'};
	}
	acum[ini] = {0,'-'}; 
	
	char currentnode = ini;
	while(currentnode!=fin){
		visitados[currentnode];
		map<char, int> adyacentes = G[currentnode];
		
		int w = acum[currentnode].first;
		// actualizar la tabla de los vecinos
		for(auto &vecino: adyacentes){
			if(visitados.find(vecino.first)==visitados.end()){
				int new_w = w + vecino.second;
				if(new_w < acum[vecino.first].first){
					acum[vecino.first].first = new_w;
					acum[vecino.first].second = currentnode;
				}
			}
		}
		// seleccionar el siguiente nodo a evaluar
		// entre los no visitados, buscar el de menor peso en la tabla acum
		int minw = inf;
		for(auto &columna: acum){
			if(visitados.find(columna.first)==visitados.end()){
				if(columna.second.first < minw){
					minw = columna.second.first;
					currentnode = columna.first;
				}
			}
		}
	}
	// generar la lista 'hacia atras' (para construir path)
	while(currentnode!=ini){
		path.push_front(currentnode);
		currentnode = acum[currentnode].second;
	}
	
	return acum[fin].first;
}

int main() {
	
	graphW G2 = {
		{'A',{
			{'B',2},
		{'C',3},
		}},
	{'B',{
		{'A',2},
	{'D',5},
		{'E',2}
	}},
		{'C',{
			{'A',3},
		{'E',5}
		}},
	{'D',{
		{'B',5},
	{'E',1},
		{'Z',2}
	}},
		{'E',{
			{'B',2},
		{'C',5},
			{'D',1},
		{'Z',4}
		}},
	{'Z',{
		{'D',2},
	{'E',4}
	}}
	}; 
	
	list<char> path;
	int W = Dijkstra(G2,'A','Z',path);
	
	cout<<" camino con peso: "<<W<<" ---> (";
	for(char x:path){
		cout<<x<<" ";
	}
	cout<<")"<<endl;
	
	return 0;
}







