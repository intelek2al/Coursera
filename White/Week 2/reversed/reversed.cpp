#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
    int tmp;
    vector<int> n = v;
    for(int i = 0; i < n.size() / 2; i++){
        tmp = n[i];
        n[i] = n[n.size() - 1 - i];
        n[n.size() - 1 - i] = tmp;
    }
    return n;
}
// int main () {
//     vector<int> numbers = {1, 5, 3, 4, 2};
//     vector<int> v = Reversed(numbers);
//     for(auto a : v)
//         cout << a;
//     return 0;
// }
