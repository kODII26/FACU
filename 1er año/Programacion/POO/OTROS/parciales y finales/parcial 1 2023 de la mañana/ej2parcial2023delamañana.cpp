#include <iostream>
#include <vector>
using namespace std;
struct QA{
	string pregunta;
	string respuesta;
};
class IA{
	string m_nom;
public:
	IA (string nom): m_nom(nom) {} 
	string verNombre () {return m_nom;}
	virtual string ObtenerRespuesta (string pregunta) =0;
};
class Memory : public IA {
	vector<QA> m_qa;
public:
	Memory (vector<QA> qa): IA("Memory"),m_qa(qa) {}
	string ObtenerRespuesta(string pregunta)  override {
		for (size_t i=0;i<m_qa.size();++i){
			if (pregunta==m_qa[i].pregunta){
				return m_qa[i].respuesta;
			}
		}
		return m_qa[0].respuesta;
	}
};
class Multivac : public IA {
public:
	Multivac () : IA("Multvac"){}
	string ObtenerRespuesta(string pregunta) override {
		string resp= "No se";
		return resp;
	}
};
int main() {
	IA *p= new Multivac;
	cout<<p->ObtenerRespuesta("Sos gay?");
	return 0;
}

