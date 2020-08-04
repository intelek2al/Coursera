#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

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
};

istream &operator>>(istream &is, Query &q)
{
    string req;
    is >> req;
    if (req == "NEW_BUS")
    {
        int stop_count = 0;
        q.type = QueryType::NewBus;
        is >> q.bus;
        is >> stop_count;
        for (int i = 0; i < stop_count; i++)
        {
            string stop;
            is >> stop;
            q.stops.push_back(stop);
        }
    }
    else if (req == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (req == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (req == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse
{
    bool is_exist;
    vector<string> buses;
    string stop;

    BusesForStopResponse(bool is, string s, vector<string> b)
    {
        is_exist = is;
        buses = b;
        stop = s;
    }
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{

    return os;
}

struct StopsForBusResponse
{
    bool is_exist;
    bool is_useful;
    map<string, vector<string>> stops;
    string bus;

    StopsForBusResponse(bool is_e, bool is_u, string b, map<string, vector<string>> s)
    {
        is_exist = is_e;
        is_useful = is_u;
        bus = b;
        stops = s;
    }
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{

    return os;
}

struct AllBusesResponse
{
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{

    return os;
}

class BusManager
{
    map<string, vector<string>> table_for_bus;
    map<string, vector<string>> table_for_stop;

public:
    void AddBus(const string &bus, const vector<string> &stops)
    {
        table_for_bus[bus] = stops;
        for (const auto &stop : stops)
            table_for_stop[stop].push_back(bus);
    }

    BusesForStopResponse GetBusesForStop(const string &stop) const
    {
        return BusesForStopResponse(table_for_stop.count(stop) != 0, stop, table_for_stop.at(stop));
    }

    StopsForBusResponse GetStopsForBus(const string &bus) const
    {
    }

    AllBusesResponse GetAllBuses() const
    {
    }
};

int main()
{
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i)
    {
        cin >> q;
        switch (q.type)
        {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}