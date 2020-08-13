#include "stats.h"

#include <string_view>

using namespace std;

Stats::Stats()
{
    for (size_t i = 0; i < URI; i++)
    {
        uris[static_uri[i]] = 0;
        if (i < MTH)
            methods[static_methods[i]] = 0;
    }
}
void Stats::AddMethod(string_view method)
{
    size_t i = 0;
    for (; i + 1 < MTH; i++)
    {
        if (method.compare(static_methods[i]) == 0)
            break;
    }
    string_view s = static_methods[i];
    ++methods[s];
    // cout << methods << "$" << endl;
}
void Stats::AddUri(string_view uri)
{
    size_t i = 0;
    for (; i + 1 < URI; i++)
    {
        if (uri.compare(static_uri[i]) == 0)
            break;
    }
    string_view s = static_uri[i];
    ++uris[s];
}
const map<string_view, int> &Stats::GetMethodStats() const
{
    return methods;
}
const map<string_view, int> &Stats::GetUriStats() const
{
    return uris;
}

vector<string_view> SplitIntoWordsView(string_view str, char delim)
{
    vector<string_view> result;
    while (true)
    {
        size_t space = str.find(delim);
        result.push_back(str.substr(0, space));
        if (space == str.npos)
        {
            break;
        }
        else
        {
            str.remove_prefix(space + 1);
        }
    }
    return result;
}

HttpRequest ParseRequest(string_view line)
{
    size_t id = line.find_first_not_of(' ');
    line.remove_prefix(id);
    vector<string_view> v = SplitIntoWordsView(line, ' ');
    return {v[0], v[1], v[2]};
}
