#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> temper;
    vector<int> new_t;
    int n = 0;
    float sum = 0;

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int tmp;
        cin >> tmp;
        sum += tmp;
        temper.push_back(tmp);
    }
    sum /= n;
    for (const auto &a : temper)
        if (a > sum)
        {
            new_t.push_back(a);
        }
    cout << new_t.size() << endl;
    for (int i = 0; i < n; i++)
    {
        if (temper[i] > sum)
        {
            cout << i;
            if (i < n - 1)
                cout << " ";
        }
    }
    return 0;
}
