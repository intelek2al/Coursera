#include <bus_manager.h>

using namespace std;

void BusManager::AddBus(const string &bus, const vector<string> &stops)
{
    table_for_bus[bus] = stops;
    for (const auto &stop : stops)
        table_for_stop[stop].push_back(bus);
}

BusesForStopResponse BusManager::GetBusesForStop(const string &stop) const
{
    bool is_exist = table_for_stop.count(stop) != 0;
    vector<string> value;

    if (is_exist)
        value = table_for_stop.at(stop);
    return BusesForStopResponse(is_exist, stop, value);
}

StopsForBusResponse BusManager::GetStopsForBus(const string &bus) const
{
    bool is_exist = table_for_bus.count(bus) != 0;
    return {is_exist, table_for_stop, table_for_bus, bus};
}

AllBusesResponse BusManager::GetAllBuses() const
{
    return {!table_for_bus.empty(), table_for_bus};
}
