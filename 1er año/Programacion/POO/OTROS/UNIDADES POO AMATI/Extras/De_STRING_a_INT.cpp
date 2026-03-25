#include <iostream>
#include <sstream>
using namespace std;

int main() {
	string numStr = "350";
	
	int num;
	istringstream iss(numStr);
	iss >> num;
	cout<< num + 50 <<endl;
	return 0;
}

