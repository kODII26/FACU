#include <iostream>
#include <matrix>
using namespace std;
int getCasos(const matrix<int> &A, int dep){
	dep--;
	int sumacasos=0;
	for (size_t c=0;c<A.size(1);c++){
		sumacasos += A[dep][c];
	}
	return sumacasos;
	
}
vector<int> getNoCasos (const matrix<int> &A) {
	vector<int> mesesSin;
	for (size_t f=0;f<A.size(0);f++){
		if (A[f][4]==0){
			mesesSin.push_back(f);
		}
	}
	return mesesSin;
}
int getMayor (const matrix<int> &A){
	int depmay, sumamay=0;
	for (size_t f=0;f<A.size(0);f++){
		int  sumatot=0;
		for (size_t c=0;c<A.size(1);c++){
			sumatot += A[f][c];
		}
		if (sumatot>sumamay) {
			depmay= f;
			sumamay= sumatot;
		}
	}
	return depmay;
}
int main() {
	int cant, mes,cod_dep;
	matrix<int> A(19,12,0);
	cout<<" cod dep"<<endl;
	cin>>cod_dep;
	while (cod_dep!=0) {
		cod_dep--;
		cout<<" mes y cant"<<endl;
		cin>>mes>>cant;
		mes--;
		A[cod_dep][mes] += cant;
		cout<<" cod dep"<<endl;
		cin>>cod_dep;
	}

	int dep, casostotal;
	cout<<" en que departamento queres ver cuantos casos hay"<<endl;
	cin>>dep;
	casostotal= getCasos(A,dep);
	cout<<"en el departamento "<<dep<<" hay: "<<casostotal<<" casos"<<endl;
	
	vector<int> sinCasos= getNoCasos(A);
	cout<<"Los codigos de departamento que no tuvieron casos en mayo son:" <<endl;
	for (size_t i=0;i<sinCasos.size();i++){
		sinCasos[i]++;
		cout<<sinCasos[i]<<endl;
	}
	
	cout<<" en el departamento 5 se detectaron: "<<A[4][6]<<" casos en julio de 2021"<<endl;
	
	int depmay;
	depmay = getMayor (A);
	depmay++;
	cout<<" el dep con mas casos es: "<<depmay;
	
	return 0;
}

