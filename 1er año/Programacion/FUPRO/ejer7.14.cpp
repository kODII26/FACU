#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
	int dato, contador;
	string opcion;
	cout<<"      "<<"CALCULOS"<<endl;
	cout<<"A- Ingresar nuevo dato"<<endl;
	cout<<"B- Calcular el doble del dato"<<endl;
	cout<<"C- Determinar si es par"<<endl;
	cout<<"D- Determinar si es primo"<<endl;
	cout<<"E- Salir"<<endl;
	cout<<"Elija una opcion"<<endl;
	cin>>opcion;
	while (opcion !="E") {
			contador=0;
			if (opcion=="A") {
				cout<<"Ingrese nuevo dato"<<endl;
				cin>>dato;
			}
			if (opcion=="B") {
				int datodoble= dato*2;
				cout<<"El doble del dato ingresado ("<<dato<<") es: "<<datodoble<<endl;
			}
			if (opcion=="C") {
				int resto= dato%2;
				if (resto==0) 
					cout<<"El numero ingresado es par"<<endl;
				else 
					cout<<"El numero ingresado no es par"<<endl;
			}
			if (opcion=="D") {
				for (int i = 2; i < dato; i++) {
						if (dato % i == 0) 
						contador = contador + 1;
				}
				if (contador != 0)
					cout<<"No es primo"<<endl;
				else 
					cout<<"Es primo"<<endl;
			}
			cout<<"      "<<"CALCULOS"<<endl;
			cout<<"A- Ingresar nuevo dato"<<endl;
			cout<<"B- Calcular el doble del dato"<<endl;
			cout<<"C- Determinar si es par"<<endl;
			cout<<"D- Determinar si es primo"<<endl;
			cout<<"E- Salir"<<endl;
			cout<<"Elija una opcion"<<endl;
			cin>>opcion;
	}
		


	return 0;
}

