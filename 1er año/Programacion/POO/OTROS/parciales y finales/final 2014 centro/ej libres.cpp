#include <iostream>
#include <cstdlib>
#include <list>
#include <tuple>
using namespace std;
template<typename T>
tuple<T,T> dosMayores (list<T> l){
	T may1=0, may2=0;
	for (T &x:l){
		if (x>may1){
			may2=may1;
			may1=x;
		}else {
			if (x>may2){
			may2=x;
		}
		}
	}
	return make_tuple(may1,may2);
}

int main() {
	list<int> l(10);
	for (auto it=l.begin();it!=l.end();++it){
		*it= rand()%100;
	}
	for (auto it=l.begin();it!=l.end();++it){
		cout<<*it<<endl;
	}
	int may1,may2;
	tie(may1,may2) = dosMayores(l);
	cout<<"dos mayores:" <<may1<<" "<<may2;
	return 0;
}

