#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main() {
	
	for (int i=0;i<10;++i){
		string a="design"+to_string(i+1)+".wds";
		fstream archi(a,ios::binary|ios::in|ios::out);
		if (!archi.is_open()){
			return 1;
		}
		string s="mswxp";
		char aux[50];
		strcpy( aux, s.c_str());
		archi.seekp(178);
		archi.write(aux, sizeof(aux));
		
		archi.seekg(178);
		archi.read(aux,sizeof(aux));
		cout<<aux<<endl;
		
		string d="msw10";
		char aux1[50];
		strcpy( aux1, d.c_str());
		archi.seekp(178);
		archi.write(aux1, sizeof(aux1));
		
		
		archi.seekg(178);
		archi.read(aux1,sizeof(aux1));
		cout<<aux1<<endl;
		
	}
	
	return 0;
}

