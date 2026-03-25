#include <iostream>
#include <list>
#include <map>
#include <iomanip>
#include <graphviz.hpp>
using namespace aed;
using namespace std;

void showll(list<list<int>> &L){
	cout<<"L = (";
	for(list<int> &x: L){
		cout<<"{";
		for(int &y: x)cout<<y<<", ";
		cout<<"}, ";
	}
	cout<<")"<<endl;
}

void showl(list<int> &L){
	for(int &x: L) cout<<x<<", ";
	cout<<endl;
}
	
void show_map(map<int, list<int>> &M){
	cout<<"M={";
	for(typename map<int,list<int>>::iterator it =M.begin(); it!=M.end(); it++){
		cout<<"["<<(*it).first<<"->";
		showl((*it).second);
		cout<<"],";
	}
	cout<<"]"<<endl;
}

	
// EJERCICIO 7
bool es_camino(map<int,list<int>> G, list<int> L){
	list<int>::iterator it = L.begin();
	while(it!=prev(L.end())){
		list<int> aux = G[*it];
		it++;
		bool sigue= false;
		list<int>::iterator it_aux = aux.begin();
		while(it_aux!=aux.end()){
			if(*it_aux==*it) sigue=true;
			it_aux++;
		}
		if(!sigue) return false;
	}
	return true;
}


// EJERCICIO 8
bool pertenece(list<int> &L,int x){
	for(int &y: L){
		if(x==y) return true;
	}
	return false;
}
	
void findConexos(map<int,list<int>> &G, map<int, list<int>>::iterator it, list<int> &conexos){
	if(pertenece(conexos, it->first)) return;
	conexos.push_back(it->first);
	for(int &node: it->second){
		if(G.find(node)==G.end()) continue;
		findConexos(G,G.find(node),conexos);
	}
}

void comp_conexas(map<int,list<int>> &G, list<list<int>> &D){
	map<int, list<int>>::iterator it = G.begin();
	list<int> conexosAll; // Registro de vértices que ya están
	while(it!=G.end()){
		list<int> conexos;
		if(!pertenece(conexosAll,it->first)){
			
			findConexos(G, it,conexos);
			
			conexosAll.insert(conexosAll.end(),conexos.begin(),conexos.end());
			D.push_back(conexos);
		}
		++it;
		
	}
}



// EJERCICIO 9	
bool isHamilt(map<int, list<int>>&G, list<int> &L){
	if(!es_camino(G,L) || G.size()!=L.size()) return false;
	list<int> ya_visitados;
	for(int &nodo: L){
		if(pertenece(ya_visitados, nodo)) return false;
		ya_visitados.push_back(nodo);
	}
	return true;
}
	


// EJERCICIO 10
list<list<int>> distancia(map<int, list<int>>&G,map<int, list<int>>::iterator nodo){
	list<list<int>> dist;
	list<int> ya_agregados;
	dist.push_back({nodo->first});
	ya_agregados.push_back(nodo->first);
	//dist.push_back(nodo->second);
	
	while(ya_agregados.size()<G.size()){
		list<list<int>>::iterator itLL = prev(dist.end());
		list<int> ult_capa = *itLL;
		list<int>::iterator itL = ult_capa.begin();
		list<int> nueva_capa;
		while(itL!=ult_capa.end()){
			auto itGrafo = G.find(*itL);
			for(int &x: itGrafo->second){
				if(!pertenece(ya_agregados, x)){
					ya_agregados.push_back(x);
					nueva_capa.push_back(x);
				}
			}
			itL++;
		}
		dist.push_back(nueva_capa);
		
	}
	return dist;
}
	
int main(int argc, char *argv[]) {
	map<int, list<int>> M={{1,{2}},{2,{1}},{3,{4}},{4,{3}}};
	list<list<int>> cc;
	comp_conexas(M,cc);
	//showll(cc);
	
	map<int, list<int>> G = {
		{1, {2,6}},
	{2, {1,3,4,5}},
		{3, {2,5,7}},
	{4, {2,6}},
		{5, {2,3}},
	{6, {1,4,7}},
		{7, {3,6}}
	};
	/*list<int> L = {1,2,3,5};
	list<int> LH = {1,2,5,3,7,6,4};
	cout<< "L es camino hamiltoniano? "<< isHamilt(G,L)<<endl;
	cout<< "LH es camino hamiltoniano? "<< isHamilt(G,LH)<<endl;*/

	graph2dot(G);
	list<list<int>> distancias = distancia(G, ++G.begin());
	showll(distancias);
	return 0;
}

