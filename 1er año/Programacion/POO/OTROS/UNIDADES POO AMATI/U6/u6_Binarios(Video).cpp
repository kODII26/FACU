#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

/* ******************************************************************************************************************/
///ESCRIBIR UN ARCHIVO BINARIO.
/*
int main() {
	
	ofstream archi("ArchBinario.poo",ios::binary);
	
	char x;
	archi.write(reinterpret_cast<char*>(&x), sizeof(x));
	
	archi<<100<<" HOLAA"<<endl;
	return 0;
}
*/



/* ******************************************************************************************************************/
//EJEMPLO 1: escribir ints y doubles en un archivo binario.
/*
struct Par {
	int i;
	double d;
};

int main() {
	ofstream archi("ArchBinario.poo",ios::binary);
	for(int i=0;i<10;++i) {
		Par p;
		p.i = rand()%100+1;
		p.d = (rand()%1001)/1000.0;
		archi.write(reinterpret_cast<char*>(&p),sizeof(p));
		cout<< p.i <<"  "<< p.d <<endl;
	}
	
	return 0;
}

*/

/* ******************************************************************************************************************/
//EJEMPLO 1: leer ints y doubles en un archivo binario.
/*
struct Par {
	int i;
	double d;
};

int main() {
	ifstream archi("ArchBinario.poo",ios::binary|ios::ate);//ate me lleva al final del archivo.
	
	int N = archi.tellg()/sizeof(Par);//tellg() pregunta la pos en la que está archi y luego divido por el tamanio del struct para saber la cant. de Pares.
	archi.seekg(0);// vuelvo a la primera posición.
	for(int i=0;i<N;++i) {
		Par p;
		archi.read(reinterpret_cast<char*>(&p),sizeof(p));
		cout<< p.i <<"  "<< p.d <<endl;
	}
	return 0;
}

*/

/* ******************************************************************************************************************/
//CAMBIAR UN DATO DE UN ARCHIVO BINARIO(sabiendo la pos).
/*
struct Par {
	int i;
	double d;
};

int main() {
	ofstream archi("ArchBinario.poo",ios::binary|ios::in);
	archi.seekp(1*sizeof(Par));
	Par p; p.i = 0; p.d = 0.992;
	archi.write(reinterpret_cast<char*>(&p),sizeof(p));
}


*/


/* ******************************************************************************************************************/
//ENCONTRAR EL MAYOR Y REEMPLAZAR.

struct Par {
int i;
double d;
};

int main() {
fstream archi("ArchBinario.poo",ios::binary|ios::in|ios::out|ios::ate);
int n = archi.tellg()/sizeof(Par);//para saber la cantidad de pares(n = tamanio del arreglo).
archi.seekg(0);
Par mayor = {0,0};
int pos_mayor;

for(int i=0; i<n; ++i) {
Par p;
archi.read(reinterpret_cast<char*>(&p),sizeof(p));
if( p.d > mayor.d ) {
mayor = p;
pos_mayor = i;
}
}

archi.seekp(pos_mayor*sizeof(Par));
mayor.i = 777;
archi.write(reinterpret_cast<char*>(&mayor),sizeof(mayor));


return 0;
}
*/


/* ******************************************************************************************************************/
//ESCRIBIR Y LEER UN ARCHIVO BINARIO,(con variables tipo char).
/*
int main() {
	//no se puede escribir dentro de write o read algo que tenga punteros como: vector,string,list,...(funciona pero no es correcto).
	//por eso se hace esto: 
	string str = "Hola Mundo!";
	char aux[256];
	strcpy( aux, str.c_str() );	
	
	//para escribir.
	ofstream arch("ArchBinario.dat",ios::binary);
	arch.write( aux,sizeof(aux) );
	arch.close();
	
	//para leer.
	char aux2[256];
	ifstream arch2("ArchBinario.dat",ios::binary);
	arch2.read( aux2,sizeof(aux2) );
	string s = aux2;
	cout<< s <<endl;
	arch2.close();
	
	return 0;
}

*/

/* ******************************************************************************************************************/
//REEMPLAZAR UNA CADENA DE TEXTO EN UN ARCHIVO BINARIO.
/*
int main() {
//creamos el archivo con un texto.
ofstream arch("ArchBinario.dat",ios::binary);
string frase = "Hola como vas xlr8 anshe wuwu jajaja xd.";

char f[256];
strcpy( f, frase.c_str() );
arch.write(f, sizeof(f));
arch.close();

//reemplazamos una palabra a la frase y lo reescribimos.
string s = f;
s.replace(14,4,"MoMo");
char f1[256];
strcpy( f1, s.c_str() );

ofstream archi("ArchBinario.dat",ios::binary);
archi.write(f1, sizeof(f1));
archi.close();

//leemos.
char f2[256];
ifstream arch2("ArchBinario.dat",ios::binary);

arch2.read(f2,sizeof(f2));
string s2 = f2;
cout<<s2<<endl;
arch2.close();

return 0;
}

/*


/* ******************************************************************************************************************/
//CAMBIAR UN ENTERO EN UNA POS X POR OTRO ENTERO.(CON fstream)
/*
int main() {
	
	fstream archi("ArchBinario.dat",ios::binary|ios::in|ios::out);
	
	archi.seekp(239);
	int num = 2002;
	archi.write(reinterpret_cast<char*>(&num), sizeof(num));
	
	archi.seekg(239);
	int num2;
	archi.read(reinterpret_cast<char*>(&num2), sizeof(num2));
	cout<<"anterior: "<<num2<<endl<<endl;
	
	archi.seekp(239);
	num = 2012;
	archi.write(reinterpret_cast<char*>(&num), sizeof(num));
	
	archi.seekg(239);
	archi.read(reinterpret_cast<char*>(&num2), sizeof(num2));
	cout<<"modificado: "<<num2<<endl<<endl;
	
	
	return 0;
}
*/
	
	
/* ******************************************************************************************************************/
//CAMBIAR UN STRING EN UNA POS X POR OTRO STRING.(CON fstream) + pasar de string a char.(strcpy(...))
/*
int main() {
	
	int main() {
	
	fstream archi("ArchBinario.dat",ios::binary|ios::in|ios::out);
	
	archi.seekp(178);
	string anio = "2002";
	char m_anio[256];
	strcpy(m_anio, anio.c_str());
	archi.write(m_anio, sizeof(m_anio));
	
	archi.seekg(178);
	char anio2[256];
	archi.read(anio2, sizeof(anio2));
	cout<<"anterior: "<<anio2<<endl<<endl;
	
	archi.seekp(178);
	anio = "2012";
	strcpy(m_anio, anio.c_str());
	archi.write(m_anio, sizeof(m_anio));
	
	archi.seekg(178);
	archi.read(anio2, sizeof(anio2));
	cout<<"modificado: "<<anio2<<endl<<endl;
	
	archi.close();
	return 0;
}
}
*/
