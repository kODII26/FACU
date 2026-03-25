///PILA slide 220
Entran y salen cosas del mismo lugar (1er elemento)
	Insertar un elemento en el tope de la pila.
	Obtener el valor del elemento en el tope de la pila.
	Eliminar el elemento del tope.
Se usa mucho para almacenar cosas que quiero reutilizar pero no me importa su orden
///Funciones basicas de las pilas
elem_t top();  //x = top() devuelve el elemento en el tope de la pila (sin modificarla).
void pop();    //pop() remueve el elemento del tope (sin retornar su valor!).
void push(elem_t x);  //push(x) inserta el elemento x en el tope de la pila.
void clear();
int size();
bool empty();
///Ejemplo sumar elementos de la pila y luego vaciarla con el pop
int sumstack(stack<int> &P) {
	int sum=0;
	while (!P.empty()) {
		sum += P.top();
		P.pop();
	}
	return sum;
}

///Implementacion de pilas mediante listas
La pila se implementa a partir de una lista, asumiendo que el tope de la
	pila esta en el comienzo de la lista  ´ .
push(x) y pop() se pueden implementar a partir de insert y erase en el
	comienzo de la lista.
top() se puede implementar en base a retrieve.
La implementacion por punteros y cursores es apropiada, ya que todas  ´
	estas operaciones son O(1). Notar que si se usa el  ´ultimo elemento de la
	lista como tope, entonces las operaciones de pop() pasan a ser O(n).

	
	
	
///COLA slide 236
el primero en entrar es el primero en salir).
	
La cola es un objeto muchas veces usado como buffer o pulmon, es decir  ´
	un contenedor donde almacenar una serie de objetos que deben ser
	procesados, manteniendo el orden en el que ingresaron.
///Operaciones abstractas COLA
	*Obtener el elemento en el frente de la cola (front())
	*Eliminar el elemento en el frente de la cola
	*Agregar un elemento a la cola (back())
Igual que para la pila, la cola no tiene posiciones, de manera que no
	necesita sobrecarga de operadores ni clases anidadas.
pop() y front() act  ´uan sobre el frente de la cola (el principio de la lista).
	
push() act  ´ua sobre el fondo de la cola (el final de la lista).
///Funciones 
	void pop();    //pop() remueve el primer elemento (sin retornar su valor!).
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
