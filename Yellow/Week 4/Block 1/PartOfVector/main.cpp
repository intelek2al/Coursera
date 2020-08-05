#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int> &numbers)
{
    auto neg_it = find_if(numbers.begin(), numbers.end(), [](int number) {
        return number < 0;
    });

    for (auto it = neg_it; it != numbers.begin();)
    {
        cout << *(--it) << " ";
    }
}
