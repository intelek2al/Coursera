#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

using type_map = map<string, vector<string>>;

enum class QueryType
{
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query
{
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;

    void FreeStruct(Query &q)
    {
        q.bus = q.stop = "";
        q.stops.clear();
    }
};

istream &operator>>(istream &is, Query &q);