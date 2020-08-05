#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin < 2)
        return;
    else
    {
        vector<typename RandomIt::value_type> elements(range_begin, range_end);
        RandomIt mid = elements.begin() + elements.size() / 2;
        MergeSort(mid, elements.end());
        MergeSort(elements.begin(), mid);
        merge(elements.begin(), mid, mid, elements.end(), range_begin);
    }
}

int main()
{
    vector<int> v = {6, 4, 7, 6, 4, 0, 1, 5};
    MergeSort(begin(v), end(v));
    for (int x : v)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

// Compile error : b "/tmp/submissionlql0tjc7/main.cpp:128:5: fatal error: use of undeclared identifier 'MergeSort'
//                 MergeSort(values.begin(), values.end());
// ^1 error generated."