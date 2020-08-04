#include <iostream>
#include <map>
#include <vector>

using namespace std;

template <typename T>
T Sqr(const T &x);

template <typename T>
vector<T> Sqr(const vector<T> &v);

template <typename K, typename V>
pair<K, V> Sqr(const pair<K, V> &p);

template <typename K, typename V>
map<K, V> Sqr(const map<K, V> &m);

template <typename T>
T Sqr(const T &x)
{
    return x * x;
}

template <typename K, typename V>
pair<K, V> Sqr(const pair<K, V> &p)
{
    return make_pair(Sqr(p.first), Sqr(p.second));
}

template <typename K, typename V>
map<K, V> Sqr(const map<K, V> &m)
{
    map<K, V> nm;
    for (const auto &o : m)
    {
        nm[o.first] = Sqr(o.second);
    }
    return nm;
}

template <typename T>
vector<T> Sqr(const vector<T> &v)
{
    vector<T> nv;
    for (const auto &o : v)
        nv.push_back(Sqr(o));
    return nv;
}

int main()
{
    // Пример вызова функции
    // cout << Sqr(2.7);
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v))
    {
        cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
        {4, {2, 2}},
        {7, {4, 3}}};
    cout << "map of pairs:" << endl;
    for (const auto &x : Sqr(map_of_pairs))
    {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}
