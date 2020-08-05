#include <query.h>

using namespace std;

istream &operator>>(istream &is, Query &q)
{
    string req;

    q.FreeStruct(q);
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