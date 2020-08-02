#include <iostream>
#include <vector>
#include <string>

using namespace std;

int GetMid(const vector<int> &v) {
    int c = 0;
    for (int i = 0; i < v.size(); i++)
        c += v[i];
    return c / v.size();
}
void PrintVector(const vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
            cout << v[i] << " ";
    }
}

int main () {
    int n;
    int mid;
    cin >> n;
    vector<int> day(n);
    vector<int> newD;
    for (int i = 0; i < day.size(); i++)
        cin >> day[i];
    mid = GetMid(day);
    for (int i = 0; i < day.size(); i++) {
        if (day[i] > mid)
            newD.push_back(i);
    }
    cout << newD.size() << endl;
    PrintVector(newD);
    return 0;
}
