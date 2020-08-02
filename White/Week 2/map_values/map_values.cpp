#include <iostream>
#include <set>
#include <map>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
    set<string> a;
    
    for (auto i : m) {
        a.insert(i.second);
    }
    return a;
}

// int main()
// {
//     map<int, string> k {
//     {1, "odd"},
//     {2, "even"},
//     {3, "odd"},
//     {4, "even"},
//     {5, "odd"}
//     };
//     set<string> values = BuildMapValuesSet(k);

//     for (const string& value : values) {
//         cout << value << endl;
//     }
//     return 0;
// }

