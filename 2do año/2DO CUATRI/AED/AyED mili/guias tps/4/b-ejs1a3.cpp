#include <iostream>
using namespace std;

///listarABB. Programe una funcion void listar_ABB(btree<int> &BT) que muestre en orden
/// ascendente los elementos del conjunto implementado como ABB.
/// Auxiliar
void listar_ABB(btree<int>& BT, btree<int>::iterator p) {
	if(p == BT.end()) return;
	
	listar_ABB(BT, p.left()); // Menores
	cout<<*p<<" ";
	listar_ABB(BT, p.right()); // Mayores
}

void listar_ABB(btree<int>& BT) {
	return listar_ABB(BT, BT.begin());
}

/// Find para ABB
btree<int>::iterator findABB(btree<int>& BT, int v) {
	btree<int>::iterator it = BT.begin();
	
	while(true) {
		if(it == BT.end())
			return it;
		
		if(v<*it)
			it = it.left();
		else if(v>*it)
			it = it.right();
		else
			return it;
	}
}

///insertaABB. Programe una funcion void inserta_ABB(btree<int> &BT, int v) que inserte v
/// en la posicion adecuada de BT que permita la construccion de un arbol binario de busqueda.
void inserta_ABB(btree<int>& BT, int v) {
	btree<int>::iterator pos = findABB(BT, v);
	if(pos == BT.end()) {
		BT.insert(pos, v);
	}
}

///eliminaABB. Programe una funcion void elimina_ABB(btree<int> &BT, int v) que elimina,
/// si existe, el valor v del arbol binario BT de tal manera de preservar el ordenamiento del mismo.
void elimina_ABB(btree<int> &BT, int v) {
	btree<int>::iterator pos = findABB(BT, v);
	
/// Si el valor v no esta en el arbol, no hace nada
/// Si el valor v esta en el arbol, dependera de la cantidad de hijos que tenga
/// - Si tiene un solo hijo, "subir" todo el subarbol de dicho hijo a la posicion del padre
/// - Si tiene dos hijos, se busca un valor cualquiera de las ramas para eliminarlo,
/// y reemplazar por la posicion del valor v
/// Tiene que ser el minimo valor de la rama derecha, o el maximo valor de la rama izquierda
if(pos != BT.end()) {
	/// Si no tiene hijos, elimina el nodo
	if(pos.left() == BT.end() && pos.right() == BT.end()) /// No tiene hijos
		BT.erase(pos);
	else if(pos.right() == BT.end()) { /// Solo tiene hijo izquierdo
		btree<int> temp;
		temp.splice(temp.begin(), pos.left());
		pos = BT.erase(pos);
		BT.splice(pos, temp.begin());
	} else if(pos.left() == BT.end()) { /// Solo tiene hijo derecho
		btree<int> temp;
		temp.splice(temp.begin(), pos.right());
		pos = BT.erase(pos);
		BT.splice(pos, temp.begin());
	} else { /// Si tiene ambos hijos, elegir una estrategia ("minimo de los maximos")
		btree<int>::iterator minR = pos.right();
		while(minR.left() != BT.end()) {
			minR = minR.left();
		}
		int valorTemp = *minR;
		/// NOTA: en lugar de eliminar la hoja con el "minimo de los maximos":
		/// BT.erase(minR);
		/// utilizar el splice para que "suba" el subarbol del hijo derecho
		/// de minR a la posicion de minR
		BT.splice(minR, minR.right());
		*pos = valorTemp;
	}
}
}

int main() {
	
	return 0;
}







