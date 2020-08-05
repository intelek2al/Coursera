#include <algorithm>
#include <iostream>
#include "sum_reverse_sort.h"

int Sum(int x, int y)
{
    return x + y;
}

string Reverse(string s)
{
    int n = s.length();

    for (int i = 0; i < n / 2; i++)
        swap(s[i], s[n - i - 1]);
    return s;
}

void Sort(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
}

// int main()
// {
//     string str = "Hello";
//     cout << Reverse(str) << endl;
//     vector<int> v = {1, 3, 2};
//     Sort(v);
//     cout << v[0] << v[1] << v[2] << endl;
//     return 0;
// }