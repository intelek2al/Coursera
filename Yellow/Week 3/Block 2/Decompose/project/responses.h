#pragma once
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

using type_map = map<string, vector<string>>;

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

struct StopsForBusResponse
{
    bool is_exist;
    type_map stops;
    type_map buses;
    string bus;

    StopsForBusResponse(bool is_e, type_map ss, type_map bs, string b)
    {
        is_exist = is_e;
        bus = b;
        buses = bs;
        stops = ss;
    }
};

struct AllBusesResponse
{
    bool is_exist;
    type_map buses;
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r);
ostream &operator<<(ostream &os, const StopsForBusResponse &r);
ostream &operator<<(ostream &os, const AllBusesResponse &r);
