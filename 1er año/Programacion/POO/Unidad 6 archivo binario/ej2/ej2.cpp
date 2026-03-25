#include <iostream>
#include <fstream>
using namespace std;
struct Par {
	int i;
	float f;
};
int main() {
	int ent,pos; float flot;
	cout<<"ingrese entero, flotante y posicion a cambiar"<<endl;
	cin>>ent>>flot>>pos;
	pos--;
	ofstream archi("grupo.dat",ios::binary|ios::in);
	archi.seekp(pos*sizeof(Par));
	Par p; p.i=ent; p.f= flot;
	archi.write(reinterpret_cast<char*>(&p),sizeof(p));
	
	
	archi.close();
	ifstream archi2("grupo.dat",ios::binary|ios::in);
	for (int i=0;i<200;++i){
		Par x;
		archi2.read(reinterpret_cast<char*>(&x),sizeof(x));
		cout<<x.i<<"   "<<x.f<<endl;
	}
	return 0;
}

