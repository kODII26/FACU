#include <iostream>
#include <cstdlib>
#include <queue>
#include <stack>
using namespace std;

void show_pila(stack<int> S){
	cout<<"{ ";
	while(!S.empty()){
		cout<<S.top()<<" ";
		S.pop();
	}
	cout<<" }"<<endl;
}

// EJERCICIO 6 
/// Se invierte pila para q el maximo quede en la parte 
///superior y despues se invierte toda la pila
int busca_mayor(stack<int> S, int n){
	int pos = 0; int cont = 0;
	int max_el = S.top();
	while(cont<n){
		if(S.top()>max_el){
			max_el = S.top();
			pos = cont;
		}
		cont++;
		S.pop();
	}
	return pos;
}
void invertir(stack<int> &S, int n){
	queue<int> aux;
	for(int i =0; i<n; i++){
		aux.push(S.top());
		S.pop();
	}
	while(!aux.empty()){
		S.push(aux.front());
		aux.pop();
	}
}
void pancake_sort(stack<int> &S){
	int N = S.size();
	for(int i =0; i<N;i++){
		// elementos por ordenar
		int n = N-i; 
		
		// busca el mayor de la pila desordenada
		int iMax = busca_mayor(S,N-i); 
		
		
		// invertir rango desde el tope hasta el mayor i
		invertir(S, iMax+1); 
		show_pila(S);
		
		// invertir toda la pila desordenada
		invertir(S, n); 
		show_pila(S);
		
	}
}

	
// EJERCICIO 7
int busca_mayor_abs(stack<int> S, int n){
	int pos = 0; int cont = 0;
	int max_el = abs(S.top());
	while(cont<n){
		if(abs(S.top())>max_el){
			max_el = abs(S.top());
			pos = cont;
		}
		cont++;
		S.pop();
	}
	return pos;
}

void invertir_signo(stack<int> &S, int n){
	queue<int> aux;
	for(int i =0; i<n; i++){
		aux.push(S.top());
		S.pop();
	}
	while(!aux.empty()){
		S.push(-aux.front());
		aux.pop();
	}
}
	
void burnt_pancake_sort(stack<int> &S){
	int N = S.size();
	for(int i =0; i<N;i++){
		// elementos por ordenar
		int n = N-i; 
		
		// busca el mayor de la pila desordenada
		int iMax = busca_mayor_abs(S,N-i); 
		
		
		// invertir rango desde el tope hasta el mayor i
		invertir_signo(S, iMax+1); 
		show_pila(S);
		
		if(S.top()>0){
			int aux = S.top();
			S.pop();
			S.push(-aux);
		}
		
		// invertir toda la pila desordenada
		invertir_signo(S, n); 
		show_pila(S);
		
	}
}

	
// EJERCICIO 8
bool is_even(int n){
	return(n % 2 == 0);
}
void rotacion(queue <int> &C){
	while(!is_even(C.front())){
		C.push(C.front());
		C.pop();
	}
}
int main(int argc, char *argv[]) {
	stack<int> pila({5,32,56,4,-4,-6,-7,-9});
	//pancake_sort(pila);
	//invertir(pila,5);
	return 0;
}

