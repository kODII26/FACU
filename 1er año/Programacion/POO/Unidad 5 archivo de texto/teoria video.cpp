/// ARCHIVOS PARTE 1 (FLUJOS DE I/O - TEXTO)
///Parte1

///Streams en c++
Hay tres usos basicos (std) para streams en c++
	*Leer del teclado/escribir en pantalla
		instancias cin/cout/cerr/clog
	*Leer/escribir en strings
		clase stringstream
	*Leer escribir en archivos 		<-Esta unidad trata sobre estos
		clases fstream/ifstream/ofstream 

///¿Qué es un archivo?
*En informatica (segun wikipedia)
	Conjunto de bits almacenados en un dispositivo
*Se almacena y se lee por bytes (8 bits)
	
///Archivos de texto vs archivos binarios
Las categorias "de texto" y "binario" hacen referencia a la forma de
codificar la informacion que se guarda; 	
	Texto: cada byte representa un caracter segun el 
	codigo ASCII (a cada uno de esos valores entre de 0 a 55 le corresponde una letra
				segun el ASCII) <- Los datos no ocupan todos el mismo lugar de memoria 
	Binario: los datos se guardan exactamente como se guardan
	en memoria <- Todos los datos ocupan 4 bites

///Archivos de texto 
Se pueden leer/modificar fácilmente (No se puede modificar una posicion en especifico)
	*Con cualquier editor de texto (ej notepad)
	*Desde cualquier sistema operativo/plataforma
Datos de igual tipo no tiene el mismo tamaño
	*Su acceso es secuencial //<- Desventaja
Los datos que no son cadenas de texto, se convierten al escribir/leer
///Archivos binarios
Los datos se guardan directamente sin conversion
No se pueden leer ni modificar facilmente
	*Usualmente solo el programa que los creo puede operarlos correctamente
	*Su verdadera codificacion puede variar de una plataforma a otra
Datos de igual tipo (en general) ocupan la misma cantidad de bytes
	*Su acceso es aleatorio
///Texto vs binarios: ventajas y desventajas
Los archivos de texto se pueden "pasar" de un programa a otro sin problemas
Operar con archivos binarios es mas rapido porque no implicacion conversion y
permiten el acceso aleatorio
	*Se puede leer/modificar solo una parte del archivo

///Archivos en c++
Para acceder a archivos se utilizan las clases:
	*ifstream: para lectura
	*ofstream: para escritura
	*fstream: para lectura y/o escritura 

Antes de utilizar un archivo, se debe "abrir":
asociar el stream con una ruta del sist. de arch.
	*Mediante el constructor de fstream:
		ifstream archi("notas.txt");
	*Mediante el metodo open:
		ifstream archi;
		archi.open("notas.txt");

Constructor y open aceptan una combinacion de banderas como segundo argumento opcional
	Utiles para ofstreams en modo texto:
	*ios::trucn <- Elimina todo el contenido previo del archivo
	*ios:app <- Se escribia siempre al final
	ej: ofstream archi("notas.txt",ios::trunc);

//Verificar si se abrió correctamente un archivo
	ifstream archi("notas.txt");
	if (!archi.is_open()) {   //is open es un metodo de la clase fstream
		cerr<< " No se pudo abrir el archivo ";
		return 1;
	}
//Luego de utilizarlo se lo debe cerrar
	archi.close(); //Si nos olvidamos, lo hara el destructor de fstream
	
//Lectura / escritura con archivos de texto	
	//Se remplaza cout o cin por el archivo y ya lo escribis o lees
//Se utilizan las mismas funciones y los mismos operadores
//que para leer/escribir en consola
	*Se escribe con <<, se pueden usar manipuladores:
		ofstream archi("notas.txt");
		archi<<nombre<<endl;
		archi<<set_precision(2)<<prom<<endl;
	*Se lee con >> y/o getline:
		ifstream archi("notas.txt");
		getline(archi, nombre);
		archi>>nombre;				//Hay que poner cin.ignore() si venis de leer con >> y pasas a getline
	
///Primer ejemplo video
int main (){
	ofstream archi("numeros.txt",ios::trunc); //Se pone el trunc para que si existe un archivo, lo borre y haga de nuevo, y si no existe, lo cree
	if (!archi.is_open()){
		cout<<"no se pudo abrir"<<endl;
		return 1;
	}
	for (int i=0;i<10;++i){
		archi<<rand()%100<<" ";
	}
return 0;
}	
//Leer datos almacenados en el archivo
int main (){
	ifstream archi("numeros.txt");
	for (int i=0;i<10;++i){
		int x;
		archi>>x;
		cout<<x<<endl;
	}
}
//Si no sabes cuantos elementos hay para leer, lees hasta que falle
	ifstream archi("numeros.txt");
	for (int i=0;i<10;++i){
		int x;
		if (archi>>x) cout<<" Leyo : "<<x<<endl;
		else cout<<"No leyo nda"<<endl;
	}
//Entonces para leer hasta que se acaben los elementos, se usa el while
	int x;
	while (archi>>x) {
		cout<<x;
	}
///Ejemplo como leer sin saber la cantidad 
int n=0;
	float x, suma=0;
	ifstream archi("numeros.txt");
	while (archi>>x){
		suma+=x;
		n++;
	}
	cout<<"Promedio"<<suma/n<<endl;
///Ejemplo cambiar notas por promedios
//Como los archivos de texto no se pueden modificar, vamos a leer todos los datos
// y cuando esten guardados en la memoria, ponemos trunc y lo escribimos todo de nuevo
struct Alumno {
	string nombre;
	int n1,n2,n3;
};
int main() {
	ifstream archi ("numeros.txt");
	//is_open
	vector<Alumno> v;
	
	Alumno a;
	while (getline(archi,a.nombre) and
		   archi>>a.n1>>a.n2>>a.n3) 
	{
		cout<<a.nombre<<endl;
		cout<<a.n1<<" "<<a.n2<<" "<<a.n3<<endl;
		v.push_back(a);
		archi.ignore() 
	}
	archi.close(); //Terminas con la lectura entonces ahora lo cerras para abrirlo de otro modo
	
	ofstream archi2("numeros.txt",ios::trunc);
	for (size_t i=0;i<v.size();++i){
		archi2<<v[i].nombre<<endl;
		float prom=(v[i].n1+v[i].n2+v[i].n3)/3.0;
		archi2<<prom<<endl;
	}
}

///Parte 2 (Strings) archivos de texto
	
///Extraccion de sub-cadenas
string s1 = "Al infinito y mas alla!";

string s2= s1.substr(3,8); //A partir de la pos 3, toma 8 caracteres
cout<<s2; //muestra "infinito"

string s3= s1.substr(14); // Si no le pones hasta donde, va hasta el final, desde el 14 hasta el final
cout<<s3; //muestra "mas alla!"

cout<<s1; //muestra "Al infinito y mas alla!"
	
///Borrar una parte intermedia
string s1="Es menester que sea rock!";
s1.erase(3,17);
cout<<s1; //Muestra "es rock!"
//Borrar desde un punto hasta el final
string s2= "Vengo remando de larga distancia";
s2.erase(13);
cout<<s2; //muestra "Vengo remando"
//Borrar todo
string s3= "Andaras bien por la 66";
s3.clear();
cout<<s3; //muestra ""

///Remplazar un fragmento por otro
string s1= "Hola a todos, yo soy el leon!";
s1.replace(5,7,"mundo");
cout<<s1; //muestra "Hola mundo, yo soy el leon!"
//Insertar un string en medio de otro
string s2= "Maderas de nogal";
s2.insert(11,"viejo");
cout<<s2; //muestra "Maderas de viejo nogal"

///Manipulacion de caracteres
*Se puede operar como si fuera un vector<char>
string corregir (string str){
	if (!str.empty()){
		str[0]= toupper(str[0]);
		for (size_t i=1;i<str.size();i++){
			str[i] = tolower(str[i]);
		}
		return str;
	}
}
int main () {
	string s1= "sIGue AL COnEjo BlaNCO";
	string s2= corregir(s1);
	cout<<s2; //muestra "Sigue al conejo blanco"
}
	
///Búsqueda
string frase = "Ser el elegido es como estar enamorado";

string silaba;
cout<<"ingrese silaba";
cin>>silaba;

int cant=0;
size_t p= frase.find(silaba,0); //que busca y desde que posicion
while (p!=string::npos){
	++cant;
	p= s1.find(silaba,p+2);  //Cada vez que encuentra la silaba "es", se pone a buscar devuelta
							//2 lugares mas adelante para no encontrar la misma otra vez
}
cout<<"la silaba esta "<<cant<< " veces"<<endl;	
	
	
	
	
	
	
	
	
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
