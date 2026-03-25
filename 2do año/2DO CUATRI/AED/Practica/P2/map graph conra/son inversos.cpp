#include <iostream>
#include <map>
using namespace std;

bool areinverse(map<int,int>&m1,map<int,int>&m2){
	
	if(m1.size()!=m2.size()){
		return false;
	}
	auto it=m1.begin();
	for(it;it!=m1.end();it++){
		if(m2[it->second]!=it->first){
			return false;
		}
	}
	return true;
}


int main(int argc, char *argv[]) {
	
	map<int,int> m1={{1,2},{2,3},{3,4}};
	map<int,int> m2={{2,1},{3,2},{4,3}};
	cout<<areinverse(m1,m2);
	return 0;
}

