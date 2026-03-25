#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>
using namespace std;
vector<int> reordena(vector<int> v, int N) {
	vector<int> v2(N);
	int c_par=0, c_imp=N-1;
	for (size_t i=0;i<v.size();i++){
		if (v[i]%2==0){
			v2[c_par]= v[i];
			c_par++;
		} else {
			v2[c_imp]= v[i];
			c_imp--;
		}
	}
	return v2;
}
tuple<int,int> getPromedio(vector<int> v, int N) {
	int prom_par=0, prom_imp=0,cont_par=0,cont_imp=0;
	for (size_t i=0;i<v.size();i++){
		if (v[i]%2==0){
			prom_par += v[i];
			cont_par++;
		} else {
			prom_imp += v[i];
			cont_imp++;
		}
	}
	prom_par= prom_par/cont_par;
	prom_imp= prom_imp/cont_imp;
	return make_tuple(prom_par,prom_imp);
}
int main() {
	int N,prompar,promimp;
	cin>>N;
	vector<int> v(N);
	for (size_t i=0;i<v.size();i++){
		v[i] = 1000+rand()%(1000-1500+1);
	}
	for (size_t i=0;i<v.size();i++) {
		cout<<v[i]<<endl;
	}
	cout<<" vector modificado"<<endl;
	vector<int> v2=reordena(v,N);
	for (size_t i=0;i<v2.size();i++) {
		cout<<v2[i]<<endl;
	}
	
	
	tie(prompar,promimp) = getPromedio(v,N);
	cout<< "promedio par: "<<prompar<<endl;
	cout<<"promedio impar: "<<promimp<<endl;
	return 0;
}

