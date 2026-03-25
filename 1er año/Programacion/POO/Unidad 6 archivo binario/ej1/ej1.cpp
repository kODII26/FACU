#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;
struct Par {
	int i;
	float f;
};
int main() {
	ofstream archi("grupo.dat",ios::binary|ios::trunc);
	for (int i=0;i<200;++i){
		Par p;
		p.i =rand()%101;
		p.f =rand()%1001/1000.0;
		archi.write(reinterpret_cast<char*>(&p),sizeof(p));
	}
	archi.close();
	ifstream archi2("grupo.dat",ios::binary|ios::in);
	for (int i=0;i<200;++i){
		Par x;
		archi2.read(reinterpret_cast<char*>(&x),sizeof(x));
		cout<<x.i<<"   "<<x.f<<endl;
	}
	return 0;
}

