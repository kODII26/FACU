#include <iostream>
#include <list>
#include <string>

using namespace std;

void show_list(list<int>& L) {
	cout<<"(";
	for(list<int>::iterator it=L.begin();it!=L.end();it++) {
		cout<<*it<<" ";
	}
	cout<<")";
}

void show_list(list<char>& L) {
	cout<<"(";
	for(list<char>::iterator it=L.begin();it!=L.end();it++) {
		cout<<*it<<" ";
	}
	cout<<")";
}

list<char> string_to_list(char * S) {
	list<char> letras;
	int i = 0;
	while (S[i] != '\0') {
		if (S[i] != ' '){
			letras.push_back(S[i]);
		}
		i++;
	}
	return letras;
}

bool is_palindromo (char * S) {
	list<char> aux= string_to_list(S);
	auto it1= aux.begin();
	auto it2= aux.begin();
	advance(it2,aux.size()-1);
	while (it1!=it2 and it2!=prev(it1)){ //la primer cond es si es impar , por ejemplo en este caso, corta cuando los 2 llegan al char "Y"
		if (*it1==*it2){				// ya que no tiene sentido seguir comparando dsp de eso, y la segunda cond es por si es par,
			++it1;						//el while corta una vez que el it2 pasa al it1
			--it2;
		} else {
			return false;
		}
	}
	return true;
}

int main(int argc, char *argv[]) {
	char predicado[] = "alli si maria avisa y asi va a ir a mi silla";	
	
	cout << "Predicado: " << predicado << endl;
	
	bool z = is_palindromo(predicado);
	if (z) 
	{
	cout << "Es palíndromo" <<	endl;	
	}
	else
	{
	cout << "No es palíndromo" <<	endl;
	}
	
	return 0;
}





