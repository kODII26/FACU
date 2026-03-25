#include <iostream>
using namespace std;
bool es_primo(int a){
	for (int i=2; i<a;i++) {
		if (a%i==0)	
			return false;
	}
	return true;
}
int main() {
	int a;
	cin>>a;
	if (es_primo(a)) {
		cout<<"Es primo"<<endl;
	} else 
		cout<<"No es primo";
	return 0;
}

