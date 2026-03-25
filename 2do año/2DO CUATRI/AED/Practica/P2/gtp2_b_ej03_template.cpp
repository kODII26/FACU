#include <iostream>
#include <list>
#include <string> 
#include <queue>
#include <stack>
#include <iterator>
using namespace std;

void show_stack(stack<int> S){
	while(!S.empty()){
		cout<<S.top()<< ', ';
		S.pop();
	}
	cout <<endl;
}

bool chequeo(list<char>&z){
	stack<char> parentesis;
	for (auto it=z.begin();it!=z.end();++it){
		if (*it=='('){
			parentesis.push(*it);
			++it;
		} 
		if (*it==')'){
			if (parentesis.empty()){
				return false;
			} else {
				parentesis.pop();
				++it;
			}
		}
	}
	if (parentesis.empty())
		return true;
	return false;
}

int main() {
	std::string str = "((a - b)*(5 - c))/4 "; 
	std::list<char> z; 
	
	for (char c : str) { 
		z.push_back(c); 
	} 
	cout << chequeo(z);
	return 0;
}







