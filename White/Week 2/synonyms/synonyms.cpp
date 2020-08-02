#include <iostream>
#include <map>
#include <set>

using namespace std;

void ADD(map<string, set<string>> &dict) {
    string w1;
    string w2;
    // set<string> d1;
    // set<string> d2;
    
    cin >> w1;
    cin >> w2;
    // d1.insert(w2);
    (dict[w1]).insert(w2);
    // d2.insert(w1);
    (dict[w2]).insert(w1);
}

void COUNT(map<string, set<string>> &dict) {
    string w;
    
    cin >> w;
    cout << dict[w].size() << endl;
}

void CHECK(map<string, set<string>> &dict) {
    string w1;
    string w2;
    
    cin >> w1;
    cin >> w2;
    if ((dict[w1]).count(w2) == 1)
        cout << "YES" << endl;
    else if ((dict[w1]).count(w2) == 0)
        cout << "NO" << endl;
}

int main() {
    map<string, set<string>> dict;
    int n;
    string keyword;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> keyword;
        if (keyword == "ADD")
            ADD(dict);
        else if (keyword == "COUNT")
            COUNT(dict);
        else if (keyword == "CHECK")
            CHECK(dict);
    }
}