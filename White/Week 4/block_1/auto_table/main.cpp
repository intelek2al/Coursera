#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main() {
    int n = 0;
    int m = 0;
    // vector<vector<double>> vc;
	int buffer;
	ifstream in("input.txt");

	if (in)
        in >> n;
        in >> m;

		for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
            {
                in >> buffer;
                in.ignore(1);
			    cout << setw(10) << buffer;
                if (j + 1 != m)
                    cout << " ";
            }
            if (i + 1 != n)
                cout << "\n";
		}
	return 0;
}
