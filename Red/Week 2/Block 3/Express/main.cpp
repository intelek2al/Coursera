#include <iostream>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class MapList
{
public:
    MapList() = default;
    ~MapList() = default;
    void AddPath(const int &start, const int &finish)
    {
        path[start].insert(finish);
        path[finish].insert(start);
    }

    int FindNearestDistans(const int &start, const int &finish)
    {
        int result = abs(start - finish);
        if (path.count(start) < 1)
        {
            return result;
        }
        const set<int> &reachable_stations = path.at(start);
        const auto finish_pos = reachable_stations.lower_bound(finish);
        if (finish_pos != end(reachable_stations))
        {
            result = min(result, abs(finish - *finish_pos));
        }
        if (finish_pos != begin(reachable_stations))
        {
            result = min(result, abs(finish - *prev(finish_pos)));
        }
        return result;
    }

private:
    map<int, set<int>> path;
};

int main()
{
    string request;
    MapList ml;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int start, finish;
        cin >> request;
        cin >> start;
        cin >> finish;
        if (request == "ADD")
        {
            ml.AddPath(start, finish);
        }
        else if (request == "GO")
        {
            cout << ml.FindNearestDistans(start, finish) << endl;
        }
    }
}
