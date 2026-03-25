#include <iostream>
#include <map>
#include <list>
using namespace std;
void show_map(map<int,int> &M)
{
	cout<<"M={"<<endl;
	for(typename map<int,int>::iterator it = M.begin(); it != M.end(); it++) {
		cout<<"["<<(*it).first<<"]="<<(*it).second<<endl;
	}
	cout<<"}"<<endl;
}

void show_list(list<int>& L) {
	cout<<"(";
	for(typename list<int>::iterator it = L.begin(); it != L.end(); it++) {
		cout<<*it<<" ";		
	}
	cout<<")"<<endl;
}


void map2list(map<int,int> &M, list<int> &Keys, list<int> &Vals) {
	for (auto it=M.begin(); it!=M.end();++it){
		Keys.push_back((*it).first);
		Vals.push_back((*it).second);
	}
}

int main(void)
{
	list<int> L1, L2;
	map<int,int> M = {
		{1,2},
		{6,3},
		{7,4},
		{9,5},
		{10,8}
	};	
	
	show_map(M);
	
	map2list(M,L1,L2);
	
	show_list(L1);
	show_list(L2);
}
