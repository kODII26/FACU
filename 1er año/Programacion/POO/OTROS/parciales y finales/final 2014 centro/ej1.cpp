#include <iostream>
#include <vector>
using namespace std;

int *intercala(vector<int> &v1,vector<int> &v2,int *nuevo,int N) {
	int *a = new int[v1.size()];
	int *b = new int[v2.size()];
	
	a = &v1[0];
	b = &v2[0];
	
	for(int j=0;j<N;++j) {
		int ia=0;
		for(int i=0;i<N;i) {
			if(ia<v1.size()) {
				nuevo[i] = a[ia];
				ia++;
				if(i+1==N) {
					--i;
				}
			}
			++i;++i;
		}
		
		int ib=0;
		for(int i=1;i<N;i) {
			++i;
			if(ib<v2.size()) {
				nuevo[i] = b[ib];
				ib++;
				if(i+1==N) {
					--i;
				}
			}
			++i;++i;
		}
	}
	
	
	
	
	delete [] a;
	delete [] b;
	
	return nuevo;
	
}



int main() {
	vector<int> v = {1,3,5};
	vector<int> v2 = {2,6,7,8};
	int N = v.size()+v2.size();
	int *nuevo = new int[N];
	nuevo = intercala(v,v2,nuevo,N);
	
	for(int i=0;i<N;++i) {
		cout<<nuevo[i]<<" ";
	}
	
	delete [] nuevo;
	
	return 0;
}
