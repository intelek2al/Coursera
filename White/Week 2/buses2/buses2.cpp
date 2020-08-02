#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<string> read_line() {
    vector<string> stops;
    int n;
    string s;
    
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> s;
        stops.push_back(s);
    }
    return stops;
}

int main()
{
    int n;
    map<vector<string>, int> table;
    vector<string> stops;
    int number = 1;

    cin >> n;
    for (int i = 0; i < n; i++) {
        stops = read_line();
        if (table[stops] == 0) {
            table[stops] = number;
            number++;
            cout << "New bus " << table[stops] << endl;
        }
        else {
            cout << "Already exists for " << table[stops] << endl; 
        }
    }
    return 0;
}
