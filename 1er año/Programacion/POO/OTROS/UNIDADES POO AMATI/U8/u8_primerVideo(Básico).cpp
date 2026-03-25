#include <iostream>
#include <vector>
using namespace std;
/* *****************************************************************************************************************/
///RECORRER UN VECTOR CON ITERADORES.
/*
int main() {
	vector<int> v(10,0);
	int cont=0;
	for(vector<int>::iterator it = v.begin(); it!= v.end(); ++it) {
		*it = 1+rand()%100;
		cout<<*it<<endl;
	}
	
	return 0;
}
*/
/* *****************************************************************************************************************/
///LO MISMO PERO CON LA PALABRA AUTO.
/*
int main() {
	vector<int> v(10,0);
	int cont=0;
	for(auto it = v.begin(); it!= v.end(); ++it) {
		*it = 1+rand()%100;
		cout<<*it<<endl;
	}
	
	return 0;
}
*/
/* *****************************************************************************************************************/
///GENERAR UNA LIST Y MOSTRARLA
/*
int main() {
	list<int> l;
	for(int i=0; i<15; ++i) {
		l.push_back(1+rand()%100);
	}
	for(list<int>::iterator it = l.begin(); it != l.end(); ++it) {
		cout<<*it<<" ";
	}
}
*/

/* *****************************************************************************************************************/
//GENERAR UNA LIST Y MOSTRARLA(diferente)
/*
int main() {
	list<int> l(15,0);
	for(list<int>::iterator it = l.begin(); it != l.end(); ++it) {
		*it = rand()%100;
		cout<<*it<<" ";
	}
	cout<<endl;
	
	//mostrar de otra forma: 
	for(int x:l) cout<<x<<" ";
}
*/

/* *****************************************************************************************************************/
///AGREGAR UN VALOR A LA LIST EN UNA POS DETERMINADA.
/*
int main() {
	list<int> l(15,0);
	for(list<int>::iterator it = l.begin(); it != l.end(); ++it) {
		*it = rand()%100;
		cout<<*it<<" ";
	}
	cout<<endl;
	int val,pos;
	cout<<"Ingrese valor a depositar: ";cin>>val;
	cout<<"Ingrese su posición: ";cin>>pos;
	
	list<int>::iterator it2 = l.begin();
	
	for(int i=0;i<pos;++i) ++it2;
	
	l.insert(it2,val);
	
	cout<<"LISTA NUEVA: "<<endl;
	for(int x:l) cout<<x<<" ";
	
}
*/


/* *****************************************************************************************************************/
///LOS MISMO PERO CON ADVANCE() Y GENERATE().
/*
int rand_mas_chico() {
return rand()%100;
}

int main() {
list<int> l(15,0);
generate(l.begin(),l.end(),rand_mas_chico);

int val,pos;
cout<<"Ingrese valor a depositar: ";cin>>val;
cout<<"Ingrese su posición: ";cin>>pos;

list<int>::iterator it2 = l.begin();

advance(it2,pos);

l.insert(it2,val);

cout<<"LISTA NUEVA: "<<endl;
for(int x:l) cout<<x<<" ";

}
*/


/* *****************************************************************************************************************/
///ELIMINAR UN ELEMENTO SEGÚN SU POSICIÓN EN UNA LIST.
/*
int main() {
list<int> l(10);

for(list<int>::iterator it= l.begin(); it!=l.end(); ++it) {
*it = rand()%100;
cout<<*it<<" ";
}

int pos;
cout<<endl<<"Ingrese pos a eliminar: ";cin>>pos;
auto it2 = l.begin();
advance(it2,pos);
l.erase(it2);

for(int x:l) cout<<x<<" ";

return 0;
}
*/

/* *****************************************************************************************************************/
///REEMPLAZAR LOS -1 DE UNA LISTA(no estan al final y no hay -1 juntos)
/*
template<typename T>
void arreglar_lista(T &l) {
	if(l.size()<2) return;
	for( auto it = next(l.begin()); it!=prev(l.end()); ++it ) {
		if(*it==-1) {
			auto it2 = it; --it2;
			auto it3 = it; ++it3;
			*it = (*it2+*it3)/2;
		}
	}
}

int main() {
	
	list<int> l(10);
	int i=0;
	for(auto it= l.begin(); it != l.end(); ++it) {
		cout<<"ingrese valor["<<i<<"]: ";cin>>*it;
		++i;
	}
	
	arreglar_lista(l);
	cout<<endl;
	for(int x:l) cout<<x<<" ";
	
	return 0;
}
*/

/* *****************************************************************************************************************/
///	INSERTAR EL PROMEDIO ENTRE LOS NUMEROS CONSECUTIVOS DE UNA LIST.( con .insert(...) )
	Segundo Ejemplo.(21:05)

	tener cuidado con el .insert(...) en los for o while ya que suele ser confuso el recorrido de los mismos.(1:25:40)
	/*
		int main() {
		list<float> l(5);
		int i=0;
		for(list<float>::iterator it=l.begin(); it!=l.end(); ++it) {
			cout<<"Elemento nro("<<i<<"): ";cin>>*it;
			++i;
		}
		
		//El for empieza desde la 2da pos, porque ahí corresponde hacer la primera inserción(si empieza en pos=0,explota);
		//y avanza de a 2 pos, porque it queda apuntando al nuevo elemento (prom) después de la inseción.
		for(auto it = next(l.begin()); it!=l.end(); advance(it,2)) {
			float prom = (*prev(it)+*it)/2;
			it = l.insert(it,prom);
		}
		i=0;
		cout<<endl<<" LISTA NUEVA: "<<endl<<endl;
		for(list<float>::iterator it=l.begin(); it!=l.end(); ++it) {
			cout<<"Elemento nro("<<i<<"): "<<*it<<endl;
			++i;
		}
		
		return 0;
	}
		
	/*



