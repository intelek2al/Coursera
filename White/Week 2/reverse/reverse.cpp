#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Reverse (vector<int> &n) {
    int tmp;
    for(int i = 0; i < n.size() / 2; i++){
        tmp = n[i];
        n[i] = n[n.size() - 1 - i];
        n[n.size() - 1 - i] = tmp;
    }
}

// int main () {
//     vector<int> numbers = {1, 5, 3, 4, 2};
//     Reverse(numbers);
//     for(auto a : numbers)
//         cout << a;
//     return 0;
// }
