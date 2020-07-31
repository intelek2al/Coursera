#include <iostream>
#include <fstream>

using namespace std;

int main() {
	string buffer;
	ifstream in("input.txt");

	if (in)
		while (getline(in, buffer)) {
			cout << buffer << endl;
		}
	return 0;
}
