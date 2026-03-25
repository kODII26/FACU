#include <iostream>
#include <matrix>
#include <iomanip>
using namespace std;
void mostrarMatriz(const matrix<int> &ventas){
	for (size_t f=0;f<ventas.size(0);f++){
		for (size_t c=0;c<ventas.size(1);c++){
			cout<<setw(6)<<ventas[f][c];
		}
		cout<<endl;
	}
}

void totales(matrix<int> &ventas){
	ventas.resize(5,25);
	for (size_t c=0;c<ventas.size(1);c++){
		int suma=0;
		for (size_t f=0;f<ventas.size(0)-1;f++){
			suma += ventas[f][c];
			ventas[4][c]= suma;
		}
	
	}
}
	
	
int encontrarMayor(const matrix<int> &ventas){
	int may=0,pos;
	for (size_t f=0;f<ventas.size(0)-1;f++){
		if (ventas[f][7]>may) {
			may= ventas[f][7];
			pos = f ;
		 }
	}
	return pos;
}
int main() {
//	int cod_suc, cod_art, cant_vend;
	matrix<int> ventas(4,25);
//	cout<<"cod sucursal"<<endl;
//	cin>>cod_suc;
	for (size_t f=0;f<ventas.size(0);f++){
		for (size_t c=0;c<ventas.size(1);c++){
			ventas[f][c]= 50+rand()%(99-50+1);
		}
	}
	
//	while (cod_suc!= -1){
//		cout<<"cod art y cant vend"<<endl;
//		cin>>cod_art>>cant_vend;
//		cod_suc--, cod_art--;
//		ventas[cod_suc][cod_art]= cant_vend;
//		
//		cout<<"cod sucursal"<<endl;
//		cin>>cod_suc;
//	}
	
	mostrarMatriz(ventas);
	cout<<endl;
	totales(ventas);
	mostrarMatriz(ventas);
	
	int suma3=0;
	for (size_t c=0;c<ventas.size(1);c++){
		suma3 += ventas[2][c];
	}
	cout<<endl<<"la sucursal 3 vendio: "<<suma3<<" unidades en total"<<endl;
	
	int suma1= ventas[0][5];
	cout<<"la sucursal 1 vendio: "<<suma1<<" unidades del articulo 6"<<endl;
	
	int pos_may= encontrarMayor(ventas);
	pos_may++;
	cout<<"la sucursal que vendio mas unidades del articulo 8 es la: "<<pos_may<<endl;
	return 0;
}

