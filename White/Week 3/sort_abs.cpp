#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool comp (int a, int b) {
    return abs(a) < abs(b);
}

int main()
{
    int n = 0;
    
    cin >> n;
    vector<int> arr;
    for (int i = 0, a = 0; i < n; i++) {
        cin >> a;
        arr.push_back(a);
    }
    sort(begin(arr), end(arr), comp);
    for (auto a : arr)
        cout << a << " ";
    return 0;
}
