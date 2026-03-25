#include <iostream>
#include <stack>
#include <iomanip>
using namespace std;

void show_stack(stack<int> p){
	cout<<"[ ";
	while(!p.empty()){
		cout<<p.top()<<" ";
		p.pop();
	}
	cout<<" ]"<<endl;
}

void varios_a(stack<int> &p, int i){
	p.pop();
	p.pop();
	p.push(i);
}
	
void varios_b(stack<int> &p, int i){
	int aux = p.top();
	p.pop();
	p.pop();
	p.push(i);
	p.push(aux);
}
	
void varios_c(stack<int> &p, int i, int n){
	if(p.size()<n) return;
	int cont =0;
	while(cont!=n){
		p.pop();
		cont++;
	}
	p.push(i);
	
}

void varios_d(stack<int> &p, int i){	while(p.size()!=0){		p.pop();	}
	p.push(i);}

void varios_e(stack<int>& S,int i){	stack<int> aux;	S.pop();	while(!S.empty()){		aux.push(S.top());		S.pop();	}	S.push(i);	while(!aux.empty()){		S.push(aux.top());		aux.pop();	}	}
	

int main(int argc, char *argv[]) {
	stack<int> pi ({2,5,6,7});
	show_stack(pi);
	varios_a(pi,10);
	show_stack(pi);
	return 0;
}

