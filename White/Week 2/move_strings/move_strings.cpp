#include <iostream>
#include <vector>
#include <string>

using namespace std;

void MoveStrings (vector<string> &s, vector<string> &d) {
    for(auto a : s)
        d.push_back(a);
    s.clear();
}

// int main () {
//     vector<string> source = {"a", "b", "c"};
//     vector<string> destination = {"z"};
//     MoveStrings(source, destination);
//     for(auto a : destination)
//         cout << a;
//     return 0;
// }
