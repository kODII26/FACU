#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int *modificar_arreglo(int *v,int n,int n2) {
	int pos=0;
	while( pos<n2 ){
		for(int i=10; i<n; ++i) {
			v[i] = v[i+1];
		}
		++pos;
	}
	
	for(int i=0; i<n; ++i) {
		if(&v[i] == nullptr) {
			delete &v[i];
		}
	}

	return v;
}

void mostrar_arreglo(int *v,int n) {
	for(int i=0;i<n;++i) {
		cout<<v[i]<<" ";
	}
	cout<<endl;
}

int *ordenar_arreglo(int *v,int desde,int hasta) {

	for(int i=desde;i<=hasta;++i) {
		int min = i;
		
		for(int j=i+1;j<=hasta;++j) {
			if(v[min]>v[j]) {
				min = j;
			}
		}
		int aux = v[i];
		v[i] = v[min];
		v[min] = aux;
	}
	return v;
}

int VerCantDeApariciones(int *v,int n,int num) {
	int cont =0;
	for(int i=0;i<n;++i) {
		if(num==v[i]) {
			++cont;
		}
	}
	return cont;
}



int *eliminar_apariciones(int *v,int n,int num,int cant) {
	
	vector<int> w(n);
	for(size_t i=0;i<w.size();++i) {
		w[i] = v[i];
	}
	for(auto it=w.begin();it!=w.end();++it){
		if( *it == num ){
			auto it2 = remove(w.begin(),w.end(),*it);
			w.erase(it2,w.end());
		}
	}

	for(size_t i=0;i<w.size();++i) {
		v[i] = w[i];
	}
	
	
	for(int i=w.size();i<n;++i) {
		delete &v[i];
	}
	return v;
}




int main() {
	int n = 30;
	int *v = new int [n];
	for(int i=0; i<n; ++i) {
		v[i] = rand()%25;
	}
	
	cout<<"ARREGLO ORIGINAL: "<<endl;
	mostrar_arreglo(v,n);
	
	ordenar_arreglo(v,10,20);
	cout<<"ARREGLO ORDENADO(10-20): "<<endl;
	mostrar_arreglo(v,n);
	
	int n2 = 11;
	int *v2 = new int[n2];
	int j=0;
	for(int i=10;i<=20;++i) {
		v2[j] = v[i];
		++j;
	}
	cout<<"ARREGLO NUEVO V2(10-20): "<<endl;
	mostrar_arreglo(v2,n2);
	
	cout<<"ARREGLO MODIFICADO V(-V2): "<<endl;
	v = modificar_arreglo(v,n,n2);
	n = n-n2;
	mostrar_arreglo(v,n);
	
	int num;
	cout<<"Ingrese un numero a encontrar x veces: ";cin>>num;
	int cant = VerCantDeApariciones(v,n,num);
	cout<<"El numero se encuentra "<<cant<<" veces en el arreglo."<<endl;
	
	v = eliminar_apariciones(v,n,num,cant);
	n = n-cant;
	cout<<"ARREGLO MODIFICADO(-apariciones): "<<endl;
	mostrar_arreglo(v,n);
	return 0;
}

