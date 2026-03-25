#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
using namespace std;

///ESCRIBIR UN ARCHIVO BINARIO.
///Se lee y escribe con read y write

int main() {
	
	ofstream archi("ArchBinario.poo",ios::binary); //Si no pones binary lo abre en modo texto
	
	char x;
	archi.write(reinterpret_cast<char*>(&x), sizeof(x));
	// Los argumentos siempre son:
		*un puntero de tipo char que apunta al dato que se quiere leer/escribir
		*la cantidad de bytes que se leen/escribe
	archi<<100<<" HOLAA"<<endl;
	return 0;
}

/// Banderas nuevas
ios::binary = se accedera en modo binario
ios::in = se abre para lectura, no eliminar el contenido previo <-Es lo contrario al trunc, sirve
	para ir a una determinada posicion y modificar solo un pedazito
ios::out = se abre para escritura
ios::ate = el "cursor" se ubica al final al abrir el archivo <-Con el ate podes ir al final y volver
	con el app solo ir al final

//Banderas para seekg dadas en la u7
	archi.seekg(10,ios::beg) //<- A partir del comienzo del archivo, moverse 10 bytes
	archi.seekg(10,ios::cur) //<- A partir del lugar en el que estas, moverse 10 bytes
	archi.seekg(0,ios::end) //<- util para ir al final sin el ate,si pones -10 te mueve 10bytes para la izq
	
///EJEMPLO 1: escribir ints y doubles en un archivo binario.
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

///EJEMPLO 1: leer ints y doubles en un archivo binario.
///Como leer sin saber la cantidad (tellg y seekg)
struct Par {
	int i;
	double d;
};

int main() {
	ifstream archi("ArchBinario.poo",ios::binary|ios::ate);//ate me lleva al final del archivo.
	//Con ate te lleva al final del archivo y ahi usas tellg para saber cuantas posiciones tiene
	int N = archi.tellg()/sizeof(Par);//tellg() pregunta la pos en la que está archi y luego divido por el tamanio del struct para saber la cant. de Pares.
	archi.seekg(0);// vuelvo a la primera posición.
	for(int i=0;i<N;++i) {
		Par p;
		archi.read(reinterpret_cast<char*>(&p),sizeof(p));
		cout<< p.i <<"  "<< p.d <<endl;
	}
	return 0;
}

///ACESSO ALEATORIO EN ARCHIVOS BINARIOS
*Si no se especifica otra cosa, los datos se leen o escriben uno a continuacion de otro
*Hay metodos para modificar o consultar la posicion donde se leera/escribira la proxima vez
	teelg()/tellp() = consulta la posicion
	seekg(...)/seekp(...) = cambia la posicion 
	
///CAMBIAR UN DATO DE UN ARCHIVO BINARIO(sabiendo la pos).
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

///ENCONTRAR EL MAYOR Y REEMPLAZAR.

struct Par {
int i;
double d;
};

int main() {
	fstream archi("ArchBinario.poo",ios::binary|ios::in|ios::out|ios::ate);
	int n = archi.tellg()/sizeof(Par);//para saber la cantidad de pares(n = tamanio del arreglo).
	archi.seekg(0);
	Par mayor = {0,0};
	int pos_mayor; //Esta no es la posicion que el mayor ocupa en el archivo, desp tenes q multiplicarla por 
					// lo que mide un Par
	
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
///ESCRIBIR Y LEER UN ARCH IVO BINARIO,(con variables tipo char).

int main() {
	//no se puede escribir dentro de write o read algo que tenga punteros como: vector,string,list,...(funciona pero no es correcto).
	//por eso se hace esto: 
	
	strcpy( aux, str.c_str() );	//<- PARA CONVERTIR DE STRING A CHAR*
	string s1(aux), s2;	//<- PARA CONVERTIR DE CHAR* A STRING
	s2=aux;				//<- PARA CONVERTIR DE CHAR* A STRING	
	
	//para escribir.
	string str = "Hola Mundo!";
	char aux[256];
	ofstream arch("ArchBinario.dat",ios::binary);
	arch.write( aux,sizeof(aux) ); //no hace falta convertirlo pq ya es puntero char
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

///REEMPLAZAR UNA CADENA DE TEXTO EN UN ARCHIVO BINARIO.

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

///CAMBIAR UN ENTERO EN UNA POS X POR OTRO ENTERO.(CON fstream)

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

///CAMBIAR UN STRING EN UNA POS X POR OTRO STRING.(CON fstream) + pasar de string a char.(strcpy(...))	
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

