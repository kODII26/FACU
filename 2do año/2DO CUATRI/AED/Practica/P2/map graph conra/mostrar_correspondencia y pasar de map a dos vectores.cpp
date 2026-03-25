#include <iostream>
#include <map>
#include <list>
using namespace std;

template<typename T,typename Q>
void show_map(map<T,Q>&map){
	typename map<T,Q>::iterator it= map.begin();
	
	for(it; it!=map.end();it++){
		cout<<it->first<<" -> "<<it->second<<endl;
	}
	cout<<endl;
}
template<typename T,typename Q>
void map2list(map<T,Q>&M,list<T>&keys,list<Q>&vals){
	auto it=M.begin();
	for(it;it!=M.end();it++){
		keys.push_back(it->first);
		vals.push_back(it->second);
	}
}
template<typename R>
void showlist(list<R>l){
	auto it=l.begin();
	for(it;it!=l.end();it++){
		cout<<*it<<" ";
	}
	cout<<endl;
}
template<typename T,typename Q>
		void list2map(map<T,Q>&M,list<T>&keys,list<Q>&vals){
	auto it=keys.begin();
	auto it2=vals.begin();
	for(it;it!=keys.end();it++){
		if(it2!=vals.end()){
			M[*it]=*it2;
			it2++;
		}else{
			M[*it]=0;
		}
		
	}
	
	
	
	}

	
	
int main(int argc, char *argv[]) {
	map<int,int> m= {{2,3},{3,4},{5,6}};
	m[2]=10;
	show_map(m);
	list<int>l1,l2;
	map<int,int> m1= {{2,3},{3,4},{5,6}};
	map2list(m1,l1,l2);
	showlist(l1);
	showlist(l2);
	list<int>l3,l4;
	for(int i=0;i<5;i++){
		l3.push_back(i);
		l4.push_back(i+10);
	}
	map<int,int>m3;
	list2map(m3,l3,l4);
	show_map(m3);
	
	
	return 0;
}

