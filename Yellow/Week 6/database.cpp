#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <sstream>
#include <tuple>
#include <functional>
#include "database.h"
#include "main.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "token.h"
#include "operators.h"

using namespace std;

string DataJoin(const Date &date, const string &event)
{
    stringstream ss;
    ss << date << ' ' << event;
    return ss.str();
}

void Database::Add(const Date &date, const string &event)
{
    size_t current_size = storage.s[date].size();
    storage.s[date].insert(event);
    if (storage.s[date].size() > current_size)
        storage.v[date].push_back(event);
}

void Database::Print(ostream &out) const
{
    for (const auto &item : storage.v)
    {
        for (const string &event : item.second)
        {
            out << item.first << " " << event << endl;
        }
    }
}

string Database::Last(const Date &date) const
{
    auto it = storage.v.upper_bound(date);
    if (it == storage.v.begin())
        throw invalid_argument("No entries");
    --it;
    return DataJoin(it->first, it->second.back());
}
