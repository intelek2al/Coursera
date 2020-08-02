#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

bool comp (string a, string b) {
    for (auto& s : a)
        s = (s <= 90) ? s + 32 : s;
    for (auto& s : b)
        s = (s <= 90) ? s + 32 : s;
    for (int i = 0; a[i] && b[i]; i++)
        if (a[i] != b[i])
            return a[i] < b[i];
    return true;
}

int main()
{
    int n = 0;
    string a;
    
    cin >> n;
    vector<string> v;
    for (int i = 0; i < n; i++) {
        cin >> a;
        v.push_back(a);
    }
    sort(begin(v), end(v), comp);
    for (auto a : v)
        cout << a << " ";
    return 0;
}
