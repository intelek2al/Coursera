#include <iostream>
#include <vector>

using namespace std;

void PrintVector (const vector<int> &v) {
    for (auto a : v)
    cout << a << endl;
}

int main()
{   
    string s1;
    int a;
    vector<bool> iter;
    int loop;
    vector<int> couter;

    cin >> loop;
    for (int c = 0; c < loop;  c++) {
        cin >> s1;
        if (s1 == "WORRY_COUNT") {
            couter.push_back(0);
            for (auto k : iter)
                couter[couter.size() - 1] += k ? 1 : 0;
        }
        else {
            cin >> a;
            if (s1 == "COME") {
                if (a > 0) {
                    vector<bool> t;
                    t.assign(a, false);
                    iter.insert(iter.end(), t.begin(), t.end());
                    t.clear();
                }
                else
                    iter.resize(iter.size() + a);
            }
            else if (s1 == "WORRY")
                iter[a] = true;
                else if (s1 == "QUIET")
                iter[a] = false;
        }
    }
    PrintVector(couter);
    return 0;
}
