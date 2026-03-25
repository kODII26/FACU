#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

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


