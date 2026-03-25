///Que es la STL
Una biblioteca con clases y funciones genericas
	*Contenedores: estructuras de datos que almacenan 
	colecciones de otros objetos
		vector<int> v1;
	*Algoritmos: funciones que operan sobre rangos
	dentro de los contenedores
		sort(v.begin(),v.end());
	*Iteradores: objetos auxiliares para referenciar
	elementos y rangos dentro de un contenedor
//Contenedores
	*Secuenciales (elementos ordenados)
		list (lista dbl-enlazada) //<-importante
		//La memoria se organiza de una forma que hace que sea muy rapido y facil insertar y eliminar datos
		//pero si queres ir desde la pos 1 a la 500 tenes que ir 1 por 1, no podes llegar directamente
		vector (arreglo lineal) //<-importante
		//La memoria se guarda ordenadamente y podes ir a la direccion 500 directamente
		deque (doble cola)
		//Estructura parecida a vector, tiene acceso aleatorio a todos los elementos y ademas
		//insertar tanto al principio como al final suele ser barato
	*Asociativos (claves)
		set(conjunto)
		map(correspondencia) //<-importante para PF, Conjunto donde cada elemento tiene algo asociado
		multiset
		multimap
		bitset
	*Adaptadores ("derivados")
		stack(pila) //Saca y guarda siempre en la primera, como una pila de sillas
		queue(cola) //Va atendiendo al primero que llega, como si fuese una cola del super
		priority_queue(cola con prioridades)
	*Y mas (desde c++ 11)
		array(vector estatico)
		forward_list(lista simpl-enlazada)
		unordered_*(tablas de hash)
//Los que tienen <-importante son los que usamos

//Iteradores
	De entrada, de salida
	De acceso aleatorio, secuenciales //<-importante
	Direccionales, bidireccionales
	De inserción, etc
///Obtener iteradores 
vector<int> v;
vector<int>::iterator itbeg= v.begin();
vector<int>::iterator itend= v.end();
vector<int>::iterator it5= v.begin()+5;
//Modificar el vector
v[0]=25;
*it=18; //la pos apuntada por el iterador va a valer 18
v.push_back(10);
it=v.insert(it,10); //insertar 10 en la posicion it
//Siempre que llamamos a un metodo que agrega o elimina, el iterador 
// utilizado no funciona mas, por eso se asigna al nuevo iterador, se lo conoce como refrescar
v.pop_back(); //eliminar el ultimo
it= v.erase(it); //elimina el de la posicion it
v.erase(it1,it2); //elimina todo desde el it1 hasta antes del it2
v.clear() //borrar todo
///Inicializar vector con Iteradores
vector<int> v(15,0);
for (vector<int>::iterator it=v.begin();it!=v.end();++it){
	*it=1+rand()%100;
}
//Lo mismo pero con auto (c++ deduce que tipo de dato es a partir del valor con el que se inicializa)
vector<int> v(15,0);
for (auto it= v.begin();it!=v.end();++it){
	*it=1+rand()%100;
}
//Otra forma (dada en FUPRO)
vector<int> v(15,0);
for (int &x : v){
	x=1+rand()%100;
}
///Vector vs list 
*Organizacion de memoria: contigua(arreglo) vs. no contigua(lista enlaz.)
*Tipo de acceso: aleatorio vs secuencial
*Inserción y elminación: lenta vs rapida

list tiene una interfaz muy similar a la de vector, pero no permite acceso aleatorio
	* no tiene sobrecarga para el operador[]
	* sus iteradores solo pueden "moverse" con ++ y --
///Movimiento de iteradores
*Una pos modificando el iterador:
	 ++it | --it
*Una pos sin modificar el iterador
	it1= prev(it) | it2= next(it);
*Multiples pos, modificando el iterador
	advance(it, N) |  advance(it, -N);
*Multiples pos, sin modificar el iterador
	it1= it-N | it2= it+N; //solo para vector 
	it1= prev(it,N) | it2= next(it,N);
///Ejemplo de list
int main () {
	list<int> l(15,0);
	for (/*auto*/list<int>::iterator it5=l.begin();it!=l.end();++it){
		*it=rand()%100; //este for se podria cambiar por generate(v.begin(),v.end(),rand)
	}
	for (int x:l){
		cout<<x<<" ";
	}
	cout<<endl;
	
	int v=42, p=5;
	auto it5=l.begin(); 
	//Necesito posicionarme en la quinta posicion pero con list solo se puede sumar de a 1
	for (int i=0;i<5;++i){ //se podria poner como advance(it5,5)
		++it5;
	}
	l.insert(it5,v);
	for (int x:l){
		cout<<x<<" ";
	}
	cout<<endl;
}
///Otro ejemplo mediciones y -1 
void arregla_lista (list<int> &l){
	if (l.size()<2) return; //me aseguro que la lista tenga por lo menos mas de 2 datos
	for (auto it=next(l.begin()); it!=prev(l.end());++it){
		//next y prev se ponen ya que sino te podrias ir una posicion antes del inicio o una desp del final
		if (*it==-1){
			auto it2= it; --it2; //copio el iterador en otro iterador porque el it esta en el for 
			auto it3= it; ++it3; //y hay muchas chances de hacer cagada 
			*it= (*it2+*it3)/2; //remplazo el -1 por el promedio entre el anterior y el siguiente
		}
	}
}
///Otro ejemplo
void ejemplo (list<int> &l){
	auto it= l.begin();++it; //vamos a promediar a partir del 2do elemento
	while (it!=l.end()){
		auto itp=prev(it); // itp=it; --itp;
		int prom (*itp+*it)/2;
		it=l.insert(it,prom);
		advance(it,2) //++it;++it;
	} //el while va avanzando de a 2 porque ahi corresponde hacer la 1er insercion
	// y avanza de a 2 pos porque it queda apuntando al nuevo elemento(prom) despues de la insercion
}


///2da parte del video
///STD::map
*map guarda un conjunto de asociaciones entre objetos, pares clave-valor
*clave y valor pueden ser de tipos diferentes
*no puede haber claves repetidas
*el tipo de clave debe ser ordenable (operator<)
*insertar o buscar una clave en un map es rapido
//Crear un mapa
map<string,int> agenda; //asocia ints a strings;  la clave serian los strings, los valores los ints
//Guardar datos en el mapa
agenda["Fulano"]=1512312 //El mapa recibe la clave y el valor , y si la clave no existe, la crea en ese
	//momento, por eso no se le mandan dimensiones como a los vectores 
//Hay un problema y es que si queres consultar si existe un dato, no podes preguntarlo pq el mapa lo crea
cout<<agenda["Chuck Norris"]<<endl; //si ese dato no esta creado, lo va a crear y va a mostrar cualq cosa	
//Para consultar un dato cuando no se si existe: 
map<string,int>::iterator it= agenda.find("Chuck Norris"); //si no lo encuentra te devuelve el end
if (it==agenda.end())
	cout<<"No encuentro a Chuck"<<endl;
else 
	cout<<"Nro de chuck:" <<it->second;
//El mapa funcionaria como un struct de pares, .first seria la clave y .second el valor 

//Recorrer todo el mapa
for (auto it=agenda.begin();it!=agenda.end();++it){
	cout<<it->fist<<" esta asociado a "<<it->second<<endl;
}
//Dato: las claves de un map no se pueden modificar, si queres cambiarla tenes q borrarla y hacerlo nuevo

///Biblioteca <algorithm>
*Contiene algoritmos genericos: para cualquier tipo de contenedor y de elementos
	*buscar un elemento (find/find_if)
	*buscar mayor y menor(min_element/max_element)
	*ordenar menor a mayor (sort) y desordenar (shuffle)
	*ordenar mayor a menor (sort y despues reverse)
	*reemplazar (replace/replace_if)
	*contar (count/count_if), sumar(accumulate)
	*eliminar por valor (remove/remove_if)
	*eliminar repetidos(unique) //Devuelve un iterador apuntando a la parte a la que hay q borrar
	*hallar distancia(distance(v.begin(),it))encuentra q dcia. hay desde el inicio hasta donde apunte el it 
	*y muchos mas

	
	
	
	
	
	
	
	
	
	
	
	
	












