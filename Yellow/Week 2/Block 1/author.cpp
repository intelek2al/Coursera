#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    int q;
    cin >> q;
    stringstream ss;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i)
    {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS")
        {

            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            vector<string> &stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string &stop : stops)
            {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }
        }
        else if (operation_code == "BUSES_FOR_STOP")
        {

            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0)
            {
                ss << "No stop" << endl;
            }
            else
            {
                for (const string &bus : stops_to_buses[stop])
                {
                    ss << bus << " ";
                }
                ss << endl;
            }
        }
        else if (operation_code == "STOPS_FOR_BUS")
        {

            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0)
            {
                ss << "No bus" << endl;
            }
            else
            {
                for (const string &stop : buses_to_stops[bus])
                {
                    ss << "Stop " << stop << ": ";
                    if (stops_to_buses[stop].size() == 1)
                    {
                        ss << "no interchange";
                    }
                    else
                    {
                        for (const string &other_bus : stops_to_buses[stop])
                        {
                            if (bus != other_bus)
                            {
                                ss << other_bus << " ";
                            }
                        }
                    }
                    ss << endl;
                }
            }
        }
        else if (operation_code == "ALL_BUSES")
        {

            if (buses_to_stops.empty())
            {
                ss << "No buses" << endl;
            }
            else
            {
                for (const auto &bus_item : buses_to_stops)
                {
                    ss << "Bus " << bus_item.first << ": ";
                    for (const string &stop : bus_item.second)
                    {
                        ss << stop << " ";
                    }
                    ss << endl;
                }
            }
        }
    }
    cout << ss.str();
    return 0;
}