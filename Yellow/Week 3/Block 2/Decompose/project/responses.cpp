#include <responses.h>

using namespace std;

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
    if (!r.is_exist)
    {
        os << "No stop";
    }
    else
    {
        for (const string &bus : r.buses)
        {
            os << bus << " ";
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
    if (!r.is_exist)
    {
        os << "No bus";
    }
    else
    {
        vector<string> tmp = r.buses.at(r.bus);
        auto it = tmp.begin();
        for (const auto &stop : tmp)
        {
            os << "Stop " << stop << ": ";
            if (r.stops.at(stop).size() == 1)
            {
                os << "no interchange";
            }
            else
            {
                for (const string &other_bus : r.stops.at(stop))
                {
                    if (r.bus != other_bus)
                    {
                        os << other_bus << " ";
                    }
                }
            }
            if (it != (tmp.end() - 1))
            {
                os << endl;
            }
            it++;
        }
    }
    return os;
}

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
    if (r.is_exist)
    {
        auto it = r.buses.begin();
        for (const auto &bus_item : r.buses)
        {
            os << "Bus " << bus_item.first << ": ";
            for (const string &stop : bus_item.second)
            {
                os << stop << " ";
            }
            it++;
            if (it != r.buses.end())
                os << endl;
        }
    }
    else
        os << "No buses";
    return os;
}