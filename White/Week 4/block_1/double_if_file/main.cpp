#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
	double buffer;
	ifstream in("input.txt");

	if (in)
		while (in >> buffer) {
			cout << fixed << setprecision(3) << buffer << endl;
		}
	return 0;
}
