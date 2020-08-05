#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> SplitIntoWords(const string &s)
{
    vector<string> arr;
    stringstream ss(s);
    string temp;

    while (getline(ss, temp, ' '))
    {
        arr.push_back(temp);
    }
    return arr;
}

int main()
{
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it)
    {
        if (it != begin(words))
        {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}
