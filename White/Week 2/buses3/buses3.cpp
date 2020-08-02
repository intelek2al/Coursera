#include <iostream>
#include <map>
#include <set>

using namespace std;

set<string> read_line() {
    set<string> stops;
    int n;
    string s;
    
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> s;
        stops.insert(s);
    }
    return stops;
}

int main()
{
    int n;
    map<set<string>, int> table;
    set<string> stops;
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

