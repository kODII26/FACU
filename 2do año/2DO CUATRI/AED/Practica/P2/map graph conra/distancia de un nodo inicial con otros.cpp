#include <iostream>
#include <map>
#include <list>
#include <graphviz.hpp>
using namespace aed;
using namespace std;


void dist_2(map<int,list<int>>&G,map<int,list<int>>&D,int nodo,int n){
	
if(n<2){
	D[n].push_back(nodo);
	for(auto &vecino:G[nodo]){
		dist_2(G,D,vecino,n+1);
	}
}else if(find(D[n-1].begin(),D[n-1].end(),nodo)==D[n-1].end() and find(D[n-2].begin(),D[n-2].end(),nodo)==D[n-2].end()){
	D[n].push_back(nodo);
	for(auto &vecino:G[nodo]){
		dist_2(G,D,vecino,n+1);
	}
}
	
}



map<int,list<int>> distancia(map<int,list<int>>&G,int nodoinicial){
	map<int,list<int>>D;
	int dist=0;
	dist_2(G,D,nodoinicial,dist);
	return D;
}


int main() {
	
	map<int,list<int>>G={
	{0,{1}},
	{1,{0,3,4,5}},
	{2,{3}},
	{3,{1,2}},
	{4,{1}},
	{5,{6,1}},
	{6,{5,7}},
	{7,{6}}
	};
	
	graph2dot(G);
	
	map<int,list<int>>d=distancia(G,1);
	
	auto it=d.begin();
	while(it!=d.end()){
		auto it2=it->second.begin();
		cout<<"{ ";
		while(it2!=it->second.end()){
			cout<<*it2<<" ";
			it2++;
		}
		cout<<"} "<<endl;
		it++;
	}
	
	return 0;
}







