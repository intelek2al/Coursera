#include <iostream>
#include <vector>

using namespace std;

void PrintVector(const vector<int>& v) {
    for (auto a : v)
        cout << a << endl;
}

/*24
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
NEXT
ADD 5 Salary
ADD 31 Walk
ADD 30 WalkPreparations
NEXT
DUMP 5
DUMP 28
NEXT
DUMP 31
DUMP 30
DUMP 28
ADD 28 Payment
DUMP 28*/

void NEXT(vector<vector<string>>& v, int& next) {
    vector<int> mounth{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (mounth[next % 12] > mounth[((next + 1) % 12)]) {
        for (int i = mounth[next % 12] - 1; i >= mounth[((next + 1) % 12)]; i--) {
            v[i - 1].insert(end(v[i - 1]), begin(v[i]), end(v[i]));
            for (string& x : v[i])
                v[i].pop_back();
        }
    }
    next++;
    // cout << "----- " << next%12 << " : " << mounth[next % 12] << endl;
}

void DUMP(vector<vector<string>>& res, vector<vector<string>>& v, int day) {
    res.resize(res.size() + 1);
    res[res.size() - 1].insert(end(res[res.size() - 1]), begin(v[day]), end(v[day]));
}

void ADD(vector<vector<string>>& v, int day) {
    string s = "";
    cin >> s;
    v[day].push_back(s);
}

void ReadLine(string keyword, vector<vector<string>>& res, vector<vector<string>>& v) {
    int day;
    string s;

    cin >> day;
    if (keyword == "ADD")
        ADD(v, day - 1);
    else if (keyword == "DUMP")
        DUMP(res, v, day - 1);
}

int main()
{
    int inter;
    vector<vector<string>> day(31);
    vector<vector<string>> result;
    int next = 0;
    int iter;
    string keyword;

    cin >> iter;
    for (int i = 0; i < iter; i++) {
        cin >> keyword;
        if (keyword == "NEXT")
            NEXT(day, next);
        else
            ReadLine(keyword, result, day);
    }
    for (auto v : result) {
        cout << v.size();
        for (auto s : v) {
            cout << " " << s;
        }
        cout << endl;
    }
    return 0;
}