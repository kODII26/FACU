///PASAR DE UN INT A STRING CON OSTRINGSTREAM.
using namespace std;

int main() {
int i=10;
ostringstream oss;
oss<<i;

string numCom = oss.str();

ofstream archi("comision("+numCom+").txt");

return 0;
}
