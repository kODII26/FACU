#include <iostream>
#include <stack>

using namespace std;

void show_stack(stack<int> S){
	cout<<"(";
	while (!S.empty())
	{
		cout << S.top()<< " ";
		S.pop();
	}
	cout<<")"<<endl;
}

	
///Asignar i a la posición del segundo elemento de la pila, con eliminación
/// Ejemplo: S = {1,2,3,4,5} -> S = {i,3,4,5}
void a_prima(stack<int> &S, int i){	
	S.pop();
	S.pop();
	S.push(i);
}

///Asignar i a la posición del segundo elemento de la pila, sin eliminación
/// Ejemplo: S = {1,2,3,4,5} -> S = {1,i,3,4,5}
void b_prima(stack<int> &S, int i){
	int prim= S.top();
	S.pop();
	S.pop();
	S.push(i);
	S.push(prim);
}

///Asignar i a la posición del n-esimo elemento de la pila, eliminando
/// Ejemplo: n=4, S = {1,2,3,4,5} -> S = {i,5}		
void c_prima(stack<int> &S, int i, int n){
	for (int i=0;i<n;++i){
		S.pop();
	}
	S.push(i);
}

///Asignar i al elemento del fondo de la pila, dejando la pila vac´ia
/// Ejemplo: n=4, S = {1,2,3,4,5} -> S = {i}	
void d_prima(stack<int> &S, int i){	
	while (!S.empty()){
		S.pop();
	}
	S.push(i);
}
	
///Asignar i al fondo de la pila, sin eliminar
/// Ejemplo: S = {1,2,3,4,5} -> S = {1,2,3,4,i}	
	
void e_prima(stack<int> &S, int i){	
	stack<int> S_aux;
	while (!S.empty()){
		S_aux.push(S.top());
		S.pop();
	}
	//S quedo vacia, ahora le pusheo el I y luego los otros 4
	S.push(i);
	S_aux.pop();
	while (!S_aux.empty()){
		S.push(S_aux.top());
		S_aux.pop();
	}
}
	
int main() {
	stack<int> S({5,4,3,2,1});
			
	cout<<endl<<"Pila: "<<endl;
	show_stack(S);		
	//a_prima(S,6);
	//b_prima(S,6);
	//c_prima(S,6,4);
	//d_prima(S,6);
	e_prima(S,6);
	cout<<endl<<"Pila: "<<endl;
	show_stack(S);		
	
	return 0;
}
