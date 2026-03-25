#include <iostream>
#include <sstream>
using namespace std;

class Fecha {
	int m_d,m_m,m_a;
public:
	Fecha(int d,int m,int a) : m_d(d),m_m(m),m_a(a) {}
	
	string VerFecha() { 
		ostringstream oss;
		oss<<m_d<<"/"<<m_m<<"/"<<m_a;
		string fecha = oss.str();
		return fecha;
	}
	
	int VerDia() { return m_d; }
	int VerMes() { return m_m; }
	int VerAnio() { return m_a; }
};

int DiferenciaEnAnios(Fecha a,Fecha b) {
	int resta = a.VerAnio()-b.VerAnio();
	if( resta<0 ){
		resta*= -1;
	}
	return resta;
}

//alta paja calcular los dias ...
string SignoSodiacal(Fecha a) {
	int dias = a.VerDia() + a.VerMes()*30;
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 141<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	if( 111<=dias and dias<=140 ) { return "Aries"; }
	return "Picis";
}

int main() {
	Fecha f(15,7,2023);
	cout<<f.VerFecha()<<endl;
	Fecha f2(30,3,2000);
	cout<<DiferenciaEnAnios(f,f2);
	return 0;
}

