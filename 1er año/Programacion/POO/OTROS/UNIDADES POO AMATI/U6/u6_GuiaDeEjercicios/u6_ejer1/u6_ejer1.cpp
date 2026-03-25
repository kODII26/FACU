#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct Par{
	int ent;
	double dou;
};

int main() {
	ofstream archi("grupo.dat",ios::binary);
	
	for(int i=0;i<200;++i) {
		Par p;
		p.ent = rand()%90+10;
		p.dou = (rand()%90+10)/100.0; 
		
		archi.write(reinterpret_cast<char*>(&p), sizeof(p));
	}
	archi.close();
	
	ifstream archi2("grupo.dat",ios::binary);
	for(int i=0;i<200;++i) {
		Par p2;
		archi2.read(reinterpret_cast<char*>(&p2), sizeof(p2));
		cout<<p2.ent<<" "<<p2.dou<<endl;
	}
	archi2.close();
	return 0;
}

