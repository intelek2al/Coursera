#include <iostream>
#include <string>
#include <deque>

using namespace std;

void GetBr(deque<string> &str)
{
    str.push_front("(");
    str.push_back(")");
}
void GetLine(deque<string> &str, const char &op, const int &n)
{
    GetBr(str);
    str.push_back(" ");
    str.push_back({op});
    str.push_back(" ");
    str.push_back(to_string(n));
}

int main()
{
    deque<string> str;
    int n = 0;

    cin >> n;
    str.push_front(to_string(n));
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char oper;
        int num;
        cin >> oper >> num;
        GetLine(str, oper, num);
    }
    for (const auto &s : str)
        cout << s;
}