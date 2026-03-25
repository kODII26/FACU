#include <iostream>
#include <vector>
using namespace std;

struct FichaMedico {
	string nombreMedico;
	vector<long> dniPacientes;
};

class Clinica{ 
	vector<FichaMedico> v;
public:
	Clinica(vector<FichaMedico> w) : v(w) {}
	
	void AgregarPaciente(int nroM,long dniP) {
		v[nroM].dniPacientes.push_back(dniP);
	}
	
	void DictarMedicosYPacientes() {
		for(size_t i=0;i<v.size();++i) {
			cout<<"Doctor: "<<v[i].nombreMedico<<endl;
			for(size_t j=0; j<v[i].dniPacientes.size(); ++j) {
				cout<<"paciente["<<j<<"]: "<<v[i].dniPacientes[j]<<endl;
			}
		}
	}
	
	void EliminarPaciente(long dni) {
		for(size_t i=0;i<v.size();++i) {
			for(auto it=v[i].dniPacientes.begin();it!=v[i].dniPacientes.end();++it) {
				if( dni == *it ) {
					v[i].dniPacientes.erase(it,v[i].dniPacientes.end());
				}
			}
		}
	}
};

int main() {
	
	return 0;
}

