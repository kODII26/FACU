#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;


int main() {
	int i=1;
	while( i<=10 ) {
		
		ostringstream oss;
		oss << i;
		string n = oss.str();
		string nomArchi = "desing"+n+".wds";
		
		fstream archi(nomArchi,ios::binary|ios::in|ios::out);
		
		//------------------------> escribir:
		archi.seekp(178);
		string palabra = "mswxp";
		char m_palabra[256];
		strcpy(m_palabra, palabra.c_str());
		archi.write(m_palabra, sizeof(m_palabra));
		
		archi.seekp(239);
		int num = 2003;
		archi.write(reinterpret_cast<char*>(&num), sizeof(num));
		//------------------------> leer: 
		archi.seekg(178);
		char palabra2[256];
		archi.read(reinterpret_cast<char*>(&palabra2), sizeof(palabra2));
		cout<<"anterior: "<<palabra2<<endl<<endl;
		
		archi.seekg(239);
		int num2;
		archi.read(reinterpret_cast<char*>(&num2), sizeof(num2));
		cout<<"anterior: "<<num2<<endl<<endl;		
		//------------------------> escribir: 
		archi.seekp(178);
		palabra = "msw10";
		strcpy(m_palabra, palabra.c_str());
		archi.write(reinterpret_cast<char*>(&m_palabra), sizeof(m_palabra));
		
		archi.seekp(239);
		num = 2016;
		archi.write(reinterpret_cast<char*>(&num), sizeof(num));		
		//------------------------> leer: 
		archi.seekg(178);
		archi.read(reinterpret_cast<char*>(&palabra2), sizeof(palabra2));
		cout<<"modificado: "<<palabra2<<endl<<endl;
		
		archi.seekg(239);
		archi.read(reinterpret_cast<char*>(&num2), sizeof(num2));
		cout<<"modificado: "<<num2<<endl<<endl;

		archi.close();
		
		++i;
	}
	
	return 0;
}

