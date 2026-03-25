#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Polinomio {
	int m_t;
	vector<int> v;
public:
	Polinomio(int grado,vector<int> &w) : m_t(grado),v(w) {
		v.resize(m_t);
		for(int i=0;i<m_t;i++) {
			v[i] = 0;
		}
	}

	void AsignarValor(int i,int val, vector<int> &w) {//o cambiar valor
		v[i] = val;
		w[i] = val;
	}
	
	int Evaluar(int x) {
		int i=0;
		int resultado = 0;
		while(i<m_t){
			resultado += v[i]*pow(x,i);
			i++;
		}
		return resultado;
	}
	
	void MostrarPolinomio(const vector<int> &v) {
		int i=v.size()-1;
		cout<<v[i]<<"*(x^"<<i<<") ";
		for(int i=v.size()-2; i>=0; i--) {
			cout<<"+ "<<v[i]<<"*(x^"<<i<<") ";
		}
		cout<<endl;
	}
	
	vector<int> SumarPolinomios(vector<int> &w, vector<int> &w2) {
		vector<int> Result_Sum;
		int  menor,mayor;
		if ( w.size() > w2.size() ){
			Result_Sum.resize(w.size());
			menor = w2.size();mayor = w.size();
		}else{
			Result_Sum.resize(w2.size());
			menor = w.size(); mayor = w2.size();
		}
		int i=0;
		while(mayor>i) {
			if( menor>=i ){
				Result_Sum[i] = w[i]+w2[i];
			}else{
				if( mayor == w.size() ){
					Result_Sum[i] = w[i];
				}else{
					Result_Sum[i] = w2[i];
				}
			}
			i++;
		}
		
		return Result_Sum;
	}
	
};




int main() {
	int grado;
	vector<int> v(20,0);

	cout<<"Indique el grado del polinomio: ";cin>>grado;
	v.resize(grado);
	Polinomio p(grado+1,v);//si es un polinomio de grado n, debes ser un arreglo de n+1 elementos.
	int i=0,val;
	while(i<=grado) {
		cout<<"-Asigne valor al coef. de grado "<<i<<" = ";cin>>val;
		p.AsignarValor(i,val,v);
		i++;
	}
	
	for(size_t i=0; i<=v.size(); ++i) {
		cout<<v[i]<<" ";
	}
	cout<<endl;
 	
	int x;
	cout<<"Indique una valor para la x = ";cin>>x;
	cout<<"Resultado = "<<p.Evaluar(x)<<endl<<endl;
	
	p.MostrarPolinomio(v);
	int grado2;
	vector<int> v2(20);
	
	cout<<endl<<"Para el nuevo polinomio (v2), indique su grado: ";cin>>grado2;
	v2.resize(grado2+1);
	Polinomio p2(grado2+1,v2);//si es de grado m, debe ser un arreglo de m+1 elementos.
	i=0;int val2;
	while(i<=grado2) {
		cout<<"-Asigne valor al coef. de grado "<<i<<" = ";cin>>val2;
		p2.AsignarValor(i,val2,v2);
		v2[i] = val2;
		i++;
	}
	p2.MostrarPolinomio(v2);
	
	vector<int> Result_Sum = p.SumarPolinomios(v,v2);
	for(size_t i=0; i<Result_Sum.size(); ++i) {
		cout<<Result_Sum[i]<<" ";
	}
	cout<<endl;
	
	p.MostrarPolinomio(Result_Sum);
	return 0;
}


///Nota: El ejercicio es simple pero muy largo, está hecho sin entenderlo del todo, lo que imposibilita la compresión del mismo.Sugiero hacerlo de nuevo

