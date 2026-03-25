#include<iostream>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

void show_list(list<int>& L){
	cout<<"(";
	for(auto it = L.begin();it!=L.end();it++){
		cout<<*it<<" ";		
	}
	cout<<")"<<endl;
}
	
void sort(list<int> &L)	{
	stack<int> s;
	auto min=L.begin();
	while (!L.empty()){
		min=min_element(L.begin(),L.end());
		s.push(*min);
		L.erase(min);
	}
	while (!s.empty()){
		L.push_back(s.top());
		s.pop();
	}
	
}
	
	
int main() {
	list<int> L({5,4,3,2,1});						
	show_list(L);
	
	sort(L);
	show_list(L);

}
	
