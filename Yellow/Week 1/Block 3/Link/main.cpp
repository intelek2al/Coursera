#include <iostream>
#include <map>
#include <vector>
#include <exception>

using namespace std;

template <typename Key, typename Value>
Value &GetRefStrict(map<Key, Value> &mp, Key key);

template <typename Key, typename Value>
Value &GetRefStrict(map<Key, Value> &mp, Key key)
{
    if (mp.count(key) == 1)
    {
        return mp[key];
    }
    throw runtime_error("");
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string &item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl; // выведет newvalue
    return 0;
}
