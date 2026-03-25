#include <iostream>
#include "include/btree.hpp"
#include "include/util.hpp"
#include "include/util_btree.hpp"
#include "include/lisp.hpp"
#include "include/make_random.hpp"
#include "include/graphviz.hpp"
#include "include/str_convs.hpp"

using namespace std;
using namespace aed;

typedef map<int,list<int>> Graph;

template<typename T>
void show_list(const list<T> &L){
    cout << "[ ";
    for_each(L.begin(),L.end(),[](T v){cout << v << " ";});
    cout << "] \n";
}

/*
 *
 * ListarAB. Escribir procedimientos para listar un  ́arbol ordenado orientado siguiendo los  ́ordenes
 * prefijo, infijo y postfijo.
 *
 */

//prefijo
void prefijo(btree<int> &T,list<int> &L,btree<int>::iterator it){

    if (it!=T.end()){
        L.push_back(*it);
    }else{
        return;
    }

    prefijo(T,L,it.left());
    prefijo(T,L,it.right());

}

void prefijo(btree<int> &T,list<int> &L){
    btree<int>::iterator it = T.begin();
    prefijo(T,L,it);
}

//postfijo
void postfijo(btree<int> &T,list<int> &L,btree<int>::iterator it){

    if (it==T.end()){
        return;
    }

    postfijo(T,L,it.left());
    postfijo(T,L,it.right());

    L.push_back(*it);
}

void postfijo(btree<int> &T,list<int> &L){
    btree<int>::iterator it = T.begin();
    postfijo(T,L,it);
}

//infijo
void infijo(btree<int> &T,list<int> &L,btree<int>::iterator it){

    if (it==T.end()) return;

    infijo(T,L,it.left());

    L.push_back(*it);

    infijo(T,L,it.right());

}

void infijo(btree<int> &T,list<int> &L){
    btree<int>::iterator it = T.begin();
    infijo(T,L,it);
}


// Determinar si dos arboles tienen la misma estructura.

bool chk_estructura(btree<int> &A , btree<int> &B,btree<int>::iterator itA,btree<int>::iterator itB){

    if (itA==A.end() && itB==B.end()) {
        return true;
    }

    if ( (itA!=A.end() && itB==B.end()) || (itA==A.end() && itB!=B.end())  ){
        return false;
    }
    if (!chk_estructura(A,B,itA.left(),itB.left())) return false;
    if (!chk_estructura(A,B,itA.right(),itB.right())) return false;

    return true;

}

bool chk_estructura(btree<int> &A , btree<int> &B){

    return chk_estructura(A,B,A.begin(),B.begin());
}

//Determinar si la estructura de un  ́arbol es la espejada de otro.


bool chk_espejo(btree<int> &A , btree<int> &B,btree<int>::iterator itA,btree<int>::iterator itB){

    btree<int>::iterator la = itA.left();
    btree<int>::iterator ra = itA.right();
    btree<int>::iterator lb = itB.left();
    btree<int>::iterator rb = itB.right();

    if (la == A.end() && rb == A.end()) return true;
    if (ra == A.end() && lb == A.end()) return true;

    if ( (la != A.end() && rb == B.end()) || (la == A.end() && rb != B.end()) ) return false;
    if ( (ra != A.end() && lb == B.end()) || (ra == A.end() && lb != B.end()) ) return false;

    if (!chk_espejo(A,B,itA.left(),itB.right())) return false;
    if (!chk_espejo(A,B,itA.right(),itB.left())) return false;

    return true;

}

// Determina si dos  ́arboles son iguales, en estructura y contenido.

bool chk_estructura_contenido(btree<int> &A , btree<int> &B,btree<int>::iterator itA,btree<int>::iterator itB){

    if (itA==A.end() && itB==B.end()) {
        return true;
    }
    if (itA==A.end() xor itB == B.end()){
        return false;
    }
    /*
    if ( (itA!=A.end() && itB==B.end()) || (itA==A.end() && itB!=B.end())  ){
        return false;
    }
    */
    if (*itA!=*itB){
        return false;
    }

    if (!chk_estructura_contenido(A,B,itA.left(),itB.left())) return false;
    if (!chk_estructura_contenido(A,B,itA.right(),itB.right())) return false;

    return true;

}

bool chk_estructura_contenido(btree<int> &A , btree<int> &B){

    return chk_estructura_contenido(A,B,A.begin(),B.begin());
}



bool chk_espejo(btree<int> &A , btree<int> &B){

    return chk_espejo(A,B,A.begin(),B.begin());

}

bool es_menor(btree<int> &A,btree<int>::iterator itA, btree<int> &B,btree<int>::iterator itB){

    if (itA == A.end() && itB == B.end()) return false;
    if (itA == A.end()) return true;
    if (itB == B.end()) return false;
    if (*itA < *itB) return true;
    if (*itA > *itB) return false;
    if (es_menor(A, itA.left(),B, itB.left())) return true;
    if (es_menor(B, itB.left(),A, itA.left())) return false;
    return es_menor(A, itA.right(),B, itB.right());
}

bool es_menor(btree<int> &A, btree<int> &B){
    return es_menor(A,A.begin(),B, B.begin());
}
/*
bool contenido(btree<int> &A,btree<int>&B,btree<int>::iterator itA,btree<int>::iterator itB){
    bool condicIzq,condicDer;

    if( itA==A.end()&&itB!=B.end() ) {
        return true;
    } else if( itA!=A.end()&&itB==B.end() ) {
        return false;

    } else if( itA==A.end()&&itB==B.end() ){
        return true;

    }else if( itA!=A.end()&&itB!=B.end() ){

        if( *itA<*itB ){
            condicIzq = contenido(A, B, itA.left(),itB.left());
            condicDer = contenido(A, B, itA.right(),itB.right());
        }else{
            return false;
        }
    }
    return (condicIzq && condicDer);
}

bool contenido(btree<int> &A, btree<int> &B){

    return contenido(A,B,A.begin(),B.begin());
}
*/

bool contenido(btree<int> &A, btree<int> &B,  btree<int>::iterator itA, btree<int>::iterator itB   ){
    if(itB == B.end())return true;
    if(itA == A.end())return false;
    if(*itA >= *itB)return false;
    if(contenido(A,B,itA.left(),itB.left())){
        if(contenido(A,B,itA.right(),itB.right()))
            return true;
    }
    return false;

}

bool contenido(btree<int> &A, btree<int> &B, btree<int>::iterator itA){

    if(itA!=A.end()){
        if(contenido(A,B,itA,B.begin()))
            return true;
        contenido(A,B,itA.left());
        contenido(A,B,itA.right());
    }
    return false;
}

bool contenido(btree<int> &A, btree<int> &B){
    return contenido(A,B,A.begin());
}

bool is_balanced(btree<int> &T, btree<int>::iterator it, int &altura){
    altura = -1;
    if (it==T.end()) return true;
    btree<int>::iterator itl = it.left();
    btree<int>::iterator itr = it.right();
    int al,ar;
    altura = INT_MAX;
    if (!is_balanced(T,itl,al)) return false;
    if (!is_balanced(T,itr,ar)) return false;
    altura = ( al > ar ? al : ar ) + 1;
    return abs(al-ar)<=1;
}

bool is_balanced(btree<int> &T){
    int altura;
    return is_balanced(T,T.begin(),altura);
}


struct huffman_tree {
    btree<char> T;
    float p;
};

btree<char> make_huffman_tree(map<char,float>& A) {

    list<huffman_tree> bosque;

    map<char,float>::iterator itA = A.begin();
    for (int i=0; i<A.size(); i++){
        auto it = bosque.insert(bosque.begin(), huffman_tree());
        it->T.insert(it->T.begin(), itA->first);
        it->p = itA->second;
        itA++;
    }

    btree<char> temp;

    while(bosque.size() > 1){

        temp.insert(temp.begin(), '.');
        float temp_p = 0.0;

        for (int j = 0; j<2 ; j++){

            list<huffman_tree>::iterator it = bosque.begin(), itMin = it;
            while (it != bosque.end()){
                if (it->p < itMin->p) {
                    itMin = it;
                }
                it++;
            }

            btree<char>::iterator nodo = temp.begin();
            if (j==0){
                nodo = nodo.left();
            } else {
                nodo = nodo.right();
            }

            temp.splice(nodo, itMin->T.begin() );
            temp_p += itMin->p;

            bosque.erase(itMin);

        }

        auto it = bosque.insert(bosque.begin(), huffman_tree());
        it->T.splice(it->T.begin(), temp.begin());
        it->p = temp_p;

    }

    return (bosque.begin())->T;

}

int main()
{
    /*
    btree<int> T;
    list<int> L;
    //make_random_btree(T, 5);
    lisp2btree("(1 2 (3 4 (5 6 7)))",T);
    btree2dot(T);

    //postfijo
    //deberia dar:
    //postfijo(T,L);
    //show_list(L);

    //infijo
    //deberia dar: 2 1 4 3 6 5 7
    //infijo(T,L);
    //show_list(L);

    return 0;
     */

    btree<int> T;
    //lisp2btree("(1 2 (3 4) )",T);
    //btree2dot(T,"arbol",true,true);
    btree<int> T2;
    //lisp2btree("(4 5 (6 7 (9 10 11)))", T2);
    lisp2btree("(3 (2 3 3) (6 8 (7 (1 11))))", T);

    //lisp2btree("(3 (2 3 3) (6 8 7))", T);
    //lisp2btree("(3 (2 3 3) (6 7 .))", T2);

    bool r = is_balanced(T);
    cout<<r;

    return 0;
}



