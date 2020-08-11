#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    unsigned int sp;
    unsigned int next;
    list<int> row;
    vector<list<int>::iterator> pool(100'001, row.end());
    size_t n;

    cin >> n;
    for (size_t i = 0; i < n; i++)
    {
        cin >> sp >> next;
        pool[sp] = row.insert(pool[next], sp);
    }
    for (const auto& el : row) {
        cout << el << '\n';
    }

}
