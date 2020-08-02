#include <iostream>
#include <vector>
#include <map>

using namespace std;

void NEW_BUS(map<string, vector<string>> &table, map<string, vector<string>>& t_s) {
    int n;
    string bus;
    string stop;
    vector<string> stops;
    
    cin >> bus;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> stop;
        stops.push_back(stop);
        t_s[stop].push_back(bus);
    }
    table[bus] = stops;
}

void ALL_BUSES(const map<string, vector<string>>& table) {
    if (table.size() == 0) {
        cout << "No buses" << endl;
        return;
    }
    for (auto bus : table) {
        cout << "Bus " << bus.first << ": ";
        for (auto stop : bus.second) {
            cout << stop << " ";
        }
        cout << endl;
    }
}

void PrintBus (map<string, vector<string>> &t_s, string stop, string cur_bus) {
    bool flag = false;
    // vector<string> s = ;
    
    for (auto bus : t_s[stop]) {
        if (bus != cur_bus) {
            cout << bus << " ";
            flag = true;
        }
    }
    // for (auto bus : table) {
    //     if (bus.first != cur_bus)
    //         for (auto stops : bus.second) {
    //             if (stops == stop) {
    //                 cout << bus.first << " ";
    //                 flag = true;
    //                 break;
    //             }
    //         }
    // }
    if (!flag)
        cout << "no interchange";
}

void STOPS_FOR_BUS(const map<string, vector<string>>& table, map<string, vector<string>>& t_stop) {
    string bus;
    
    cin >> bus;
    if (table.size() == 0 || table.count(bus) == 0) {
        cout << "No bus" << endl;
        return;
    }
    for (auto buses : table) {
        if (buses.first == bus) {
            for (auto stop : buses.second) {
                cout << "Stop " << stop << ": ";
                PrintBus(t_stop, stop, bus);
                cout << endl;
            }
        }
    }
}

void BUSES_FOR_STOP(map<string, vector<string>>& table) {
    string stop;
    bool flag = false;
    
    cin >> stop;
    if (table.size() == 0 || table.count(stop) == 0) {
        cout << "No stop" << endl;
        return;
    }
    for (auto bus : table[stop]) {
        cout << bus << " ";
    }
    // cout << "Stop " << stop << ": ";
    // for (auto bus : table) {
    //     for (auto stops : bus.second) {
    //         if (stops == stop) {
    //             cout << bus.first << " ";
    //             flag = true;
    //             break;
    //         }
    //     }
    // }
    cout << endl;
    // if (!flag)
    //     cout << "No stop" << endl;
}

int main()
{
    map<string, vector<string>> table;
    map<string, vector<string>> t_stop;
    string keyword;
    int n;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> keyword;
        if (keyword == "ALL_BUSES")
            ALL_BUSES(table);
        else if (keyword == "NEW_BUS")
            NEW_BUS(table, t_stop);
        else if (keyword == "BUSES_FOR_STOP")
            BUSES_FOR_STOP(t_stop);
        else if (keyword == "STOPS_FOR_BUS")
            STOPS_FOR_BUS(table, t_stop);
    }
    return 0;
}

// 4
// NEW_BUS 32 3 Tolstopaltsevo Marushkino Vnukovo
// NEW_BUS 32K 6 Tolstopaltsevo Marushkino Vnukovo Peredelkino Solntsevo Skolkovo
// STOPS_FOR_BUS 23
// ALL_BUSES
