#include <iostream>
#include <map>
#include <tree.hpp>
#include <list>
#include <graphviz.hpp>
#include <climits>

using namespace aed;
using namespace std;

typedef map<char, map<char,int>> graphW;

const int INF = INT_MAX;

int Prim(graphW& G, tree<char>& T)
{
	graphW::iterator itG = G.begin();
	tree<char>::iterator p = T.begin();
	
	map <char, tree<char>::iterator> visitados;
	
	// vertice inicial
	p = T.insert(p, itG->first);
	visitados[itG->first] = p;
	
	//peso acumulado
	int W  = 0;
	
	//itera hasta que la cantidad de nodos sea la misma
	while (visitados.size() < G.size())
	{
		//par vertices menor peso		
		char c, f;
		
		int min = INF;
		//recorrer todos los vertices del grafo
		itG = G.begin();
		for (int x = 0; x <G.size()-1; x++, itG++)
		{
			char nodoActual = itG->first;
			//chequeo visitados
			if (visitados.find(nodoActual) != visitados.end())
			{
				map<char,int>& adyacentes = itG->second;
				map<char,int>::iterator j = adyacentes.begin();
				
				/// recorrer todas las aristas adyacentes
				for (int y = 0; y < adyacentes.size(); y++, j++)
				{
					char nodoAdyacente = j->first;
					// seleccionamos arista de menor peso
					//verificando que no haya ciclos
					if (min > G[nodoActual][nodoAdyacente] && visitados.find(nodoAdyacente) == visitados.end())
					{
						// G['A']['B'] devuelve el peso de la arista A-B
						min = G[nodoActual][nodoAdyacente];
						f = nodoActual;
						c = nodoAdyacente;
					}
				}								
			}
		}
		
		//acumulamos peso
		W += min;
		
		//armar el arbol		
		p = T.insert(visitados[f].lchild(),c);
		
		// agregamos vertice a la lista
		visitados[c] = p;
	}
	
	return W;
}

int main()
{
	
	graphW G = 
	{
		{'A',{{'B',2},{'C',3},}},
		{'B',{{'D',5},{'E',2},{'A',2},}},
		{'C',{{'A',3},{'E',5},}},
		{'D',{{'B',5},{'E',1},{'Z',2},}},	
		{'E',{{'C',5},{'B',2},{'D',1},{'Z',4},}},
		{'Z',{{'D',2},{'E',4},}},};
	
	tree<char> arbol;
	cout << Prim(G,arbol);	
	
	tree2dot(arbol);	
}
