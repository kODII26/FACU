#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

/* *****************************************************************************************************************/
///VERIFICACIÓN DE OPEN. 
/*

int main() {
	ifstream archi("notas.txt");
	if(!archi.is_open()) {
		cerr<< "No se pudo abrir el archivo";
		return 1;
	}
	
	archi.close();//cerrar el programa(evita errores).
	return 0;
}
//Nota: El archivo txt debe estar guardado junto con el archivo zinjai en la misma carpeta.

*/

/* *****************************************************************************************************************/
///ESCRIBIR UN TXT.
/*
int main() {
	
	ofstream archi("numeros.txt",ios::app);//ios::trunc para crear el archivo si no existe.
											//ios::trunc borra y crea de nuevo.
										    //--> ios::app almacena los datos sin borrar nada(si el archivo no está creado, tmb lo crea).
	if(!archi.is_open()) {
		cout << "No pude abrir el archivo" << endl;
	}
	
	for(int i=0; i<10; ++i) {
		archi<<" "<<rand()%100;
	}
	archi<<" PUEDO ESCRIBIR LO QUE QUIERA.{{}{}{}{}{//gvdgv" <<endl;
	
	archi.close();
	return 0;
}

*/

/* *****************************************************************************************************************/
//LEER UN TXT.
/*
int main(){
	ifstream archi("numeros.txt");
	//is_open(verificar)
	
	int x;
	while( archi>>x ) { //tambien sirve dentro del for con un condicional if( archi>>x ) {}
						// puede fallar si no es un entero.
		cout<< x <<endl;
	}
	 
	return 0;
}
	
	*/
/* *****************************************************************************************************************/
///HALLAR PROMEDIO DE LA LISTA.(prom = suma/n, sin saber el valor de n).
/*
int main() {
	ifstream archi("numeros.txt");
	if(!archi.is_open()) {cout<<"!error."<<endl; return 1;}
	
	int x, n = 0, suma =0;
	while( archi>>x ){
		suma += x;
		n++;
		cout<<x<<" ";
	}
	float prom = suma/n;
	
	cout<<endl<<"promedio = "<<prom<<endl;
	archi.close();
	return 0;
}

*/

/* *****************************************************************************************************************/
///LEER NOMBRES Y NOTAS, Y DEBOLVER EL PROMEDIO MODIFICANDO EL ARCHIVO TXT.
/*
struct Alumno {
	string nombre;
	int n1,n2,n3;
};

int main() {
	
	ifstream archi("numeros.txt");
	if(!archi.is_open()) { cout<<"No se pudo abrir el programa."<<endl; return 1;}
	Alumno a;
	vector<Alumno> v;  
	
	while( getline(archi,a.nombre) and archi>>a.n1>>a.n2>>a.n3) {
	cout<< a.nombre <<endl;
	cout<< a.n1 <<" "<< a.n2 <<" "<< a.n3 <<endl;
	v.push_back(a);  
	archi.ignore();
	}
	
	archi.close();//cuando se deja de utilizar archi.
	
	ofstream archi2("numeros.txt");
	for( size_t i=0; i<v.size(); ++i) {
		archi2 << v[i].nombre <<endl;
		float prom = (v[i].n1+v[i].n2+v[i].n3)/3.0;
		archi2 << prom <<endl;
	}
	return 0;
}
*/

/* *****************************************************************************************************************/
///EXTRACCIÓN DE CADENAS STRING.

int main() {
	string s1 = "Al infinito y más allá!";
	
	string s2 = s1.substr(3,8);
	cout<< s2 <<endl;// muesta "infinito"
	
	string s3 = s1.substr(14);
	cout<< s3 <<endl;// muestra "más allá!"
	
	
	return 0;
}
*/

/* *****************************************************************************************************************/
///BORRADO DE CADENAS STRING.
/*
int main() {
	string s1 = "Es menester que sea rock!";
	s1.erase(3,17);
	cout<< s1 <<endl;// muestra "Es rock!"
	
	string s2 = "Vengo remando de larga distancia";
	s2.erase(13);
	cout<< s2 <<endl;// muestra "Vengo remando"
	
	string s3 = "Andarás bien por la 66";
	s3.clear();
	cout << s3 <<endl;// muestra ""
	
	return 0;
}
*/

/* *****************************************************************************************************************/
///MODIFICAR REEMPLAZANDO CADENA STRING.
/*
int main() {
	string s1 = "Hola a todos, yo soy el león!";
	s1.replace(5,7,"mundo");//desde pos 5, toma 7 espacios y reemplaza por "mundo"
	cout<< s1 <<endl;// muestra "Hola mundo, yo soy el león!"

	return 0;
}
*/


/* *****************************************************************************************************************/
///INSERTAR STRING DENTRO DE OTRO.
/*
int main() {
	string s1 = "Maderas de nogal";
	//string cadena = "nuevoTP_nro"+to_tring(1)+".tetas";
	s1.insert(11,cadena);
	cout << s1 <<endl;// muestra "Maderas de viejo nogal"
	
	
	return 0;
}

*/

/* *****************************************************************************************************************/
///MODIFICACIÓN DE CARACTERES( MAYÚSCULAS Y MINÚSCULAS).
/*
int main() {
	string s = "847358 ghg437434 matias";//se opera como un vector<char>
	for( size_t i=0; i<s.size(); ++i) {
		s[i] = toupper(s[i]);//pasa a mayúsculas.
	}
	
	cout << s <<endl;
	
	for( size_t i=0; i<s.size(); ++i) {
		s[i] = tolower(s[i]);//pasa a minúsculas.
	}
	
	cout << s <<endl;
	
	return 0;
}
*/


/* *****************************************************************************************************************/
///CORREGIR UN TEXTO.(la primer letra en mayúsculas y las otras en minúsculas)
/*
string Corregir(string str) {
	if (!str.empty()) {// empty() sirve para saber si el texto está vacío.
		str[0] = toupper(str[0]);
		for( size_t i=1; i<str.size(); ++i) {
			str[i] = tolower(str[i]);
		}
	}
	
	return str;
}

int main() {
	string str = "hOlA CóMo VaS? <3, HaCe TIEmpo no Se de Tí.";
	
	str = Corregir(str);
	cout << str <<endl;// muestra "Hola cómo vas?..."
}
*/


/* *****************************************************************************************************************/
///BUSQUEDA DE UN STRING.
/*
int main() {
	string frase = "Ser el elegido es como estar enamorado";
	
	string palabra;
	cout<<"Indique la palabra a buscar: ";cin>>palabra;
	
	size_t p = frase.find(palabra);
	if ( p == string::npos ){ // string::npos es un valor raro que la funcion podria devolver si no ha encontrado la palabra.
		cout<< "La palabra no está en la frase."<<endl;
	} else {
		cout<< "La palabra comienza en la posición: "<< p <<endl;
	}
	return 0;
}

//Nota: Devuelve solo la primera palabra coincidente.
*/

/* *****************************************************************************************************************/
///BUSQUEDA DE TODAS LAS SILABAS COINCIDENTES.(si fuese la búsqueda de palabra: "es", no debería encontrarse en "estar"
/*
int main() {
	string frase = "Ser el elegido es como estar enamorado";
	
	string palabra;
	cout<<"Indique la palabra a buscar: ";cin>>palabra;//ingresar "es"
	
	int cant = 0;
	size_t p = frase.find(palabra , 0);// frase.find(palabra , desde que pos)
	
	while ( p != string::npos ) {// p != valor raro.
		cant++;
		p = frase.find( palabra , p+palabra.size() );
	}
	 
	cout<< "La palabra está "<< cant <<" veces."<<endl;
	
	return 0;
}
*/

/* *****************************************************************************************************************/ 
///BUSQUEDA DE UNA PALABRA.(no debe comenzar en la pos 0 del string)
/*
//se verifica si hay o no espacios entre la palabra o si hay letras.
bool no_es_letra(char c) {
	if((c>='a' and c<='z') or (c>='A' and c<='Z')) {
		return false;
	}else{
		return true;
	}

}

int main() {
	
	int cont =0;
	string s = "Ser el elegido es como estar enamorado es anashei";
	string palabra = "es";
	
	size_t p = s.find(palabra);
	cout<<s[p]<<endl;
	while(p != string::npos ) {
		
		if(no_es_letra(s[p+palabra.size()]) and no_es_letra(s[p-1])){
			cout<< p <<endl;
			cont++;
		}
		
		p = s.find(palabra,p+2);
		
	}
	
	cout<<"La palabra se encuentra "<< cont <<" veces."<<endl;
}

*/


/* *****************************************************************************************************************/
///PASAR DE UN INT A STRING CON OSTRINGSTREAM.
/*
using namespace std;

int main() {
	int i=10;
	ostringstream oss;
	oss<<i;
	
	string numCom = oss.str();
	
	ofstream archi("comision("+numCom+").txt");
	
	return 0;
}
*/



/* *****************************************************************************************************************/
///DEFINITIVO:lee lineas de nombres y números dentro de un archivo y las guarda en un vector de tipo struct.

/*
struct Contacto {
	string nombre; 
	int numero;
};

int ContarRenglones() {
	ifstream archi("archivo_de_practica.txt");
	string x;
	int N = 0;
	while( getline(archi,x) ) {
		N++;
	}
	
	return N;
}

int main() {
	ifstream archi("archivo_de_practica.txt");
	
	vector<Contacto> v;
	Contacto c;
	
	int N = ContarRenglones()/2;///cuento los renglones y los divido 2 ya que dos renglones le pertenecen a un solo contacto
	string x;
	for(int i=0; i<N ;++i) {
		int cont = 0;
		while( cont<2 ){
			if( getline(archi,x) and (cont%2) == 0){
				c.nombre = x;
				cout<<"nombre: "<<c.nombre<<endl;
			}else{
				string x2 = x;
				int newX;
				istringstream iss(x2);
				iss >> newX;
				
				c.numero = newX;
				cout<<"numero: "<<c.numero<<endl;
			}
			++cont;
			
		}
		v.push_back(c);
	}
	
	cout<<"***************************************"<<endl;
	for( size_t i=0; i<v.size(); ++i ) {
		cout<<"nombre: "<<v[i].nombre<<endl;
		cout<<"numero: "<<v[i].numero<<endl;
	}
	return 0;
}
*/








