#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>
#include <responses.h>

using namespace std;

using type_map = map<string, vector<string>>;

class BusManager
{
private:
    type_map table_for_bus;  // [bus] = vector<stop>
    type_map table_for_stop; // [stop] = vector<bus>

public:
    void AddBus(const string &bus, const vector<string> &stops);

    BusesForStopResponse GetBusesForStop(const string &stop) const;

    StopsForBusResponse GetStopsForBus(const string &bus) const;

    AllBusesResponse GetAllBuses() const;
};