#include <iostream>
#include <fstream>

using namespace std;

int main() {
	string buffer;
	ifstream in("input.txt");
	ofstream out("output.txt");

	if (in)
		while (getline(in, buffer)) {
			out << buffer << endl;
		}
	return 0;
}
