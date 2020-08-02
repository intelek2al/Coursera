#include <iostream>
#include <map>
#include <vector>

using namespace std;

void CHANGE_CAPITAL(map<string, string> &world, vector<string> &out) {
    string n_cap;
    string country;
    
    cin >> country;
    cin >> n_cap;
    if (world.count(country) == 0) {
        out.push_back("Introduce new country " + country + " with capital " + n_cap);
        world[country] = n_cap;
    }
    else if (world[country] == n_cap) {
        out.push_back("Country " + country + " hasn't changed its capital");
    }
    else {
        out.push_back("Country " + country + " has changed its capital from "
        + world[country] + " to " + n_cap);
        world[country] = n_cap;
    }
}

void RENAME(map<string, string> &world, vector<string> &out) {
    string n_country;
    string o_country;
    
    cin >> o_country;
    cin >> n_country;
    if (o_country == n_country || world.count(o_country) == 0
        || world.count(n_country) != 0) {
            out.push_back("Incorrect rename, skip");
            return;
    }
    else {
        out.push_back("Country " + o_country + " with capital " + world[o_country]
        + " has been renamed to " + n_country);
        world[n_country] = world[o_country];
        world.erase(o_country);
    }
}

void ABOUT(map<string, string> &world, vector<string> &out) {
    string country;
    
    cin >> country;
    if (world.count(country) == 0)
        out.push_back("Country " + country + " doesn't exist");
    else
        out.push_back("Country " + country + " has capital " + world[country]);
}

void DUMP(map<string, string> &world, vector<string> &out) {
    string s = "";
    
    if (world.empty()) {
        out.push_back("There are no countries in the world");
    }
    else {
        for (auto country : world)
            s += country.first + "/" + country.second + " ";
        out.push_back(s);
    }
}

int main()
{
    int n;
    cin >> n;
    
    map<string, string> world;
    vector<string> out;
    string keyword;
    
    for (int i = 0; i < n; i++){
        cin >> keyword;
        if (keyword == "CHANGE_CAPITAL")
            CHANGE_CAPITAL(world, out);
        else if (keyword == "RENAME")
            RENAME(world, out);
        else if (keyword == "ABOUT")
            ABOUT(world, out);
        else if (keyword == "DUMP")
            DUMP(world, out);
    }
    for (auto s : out)
        cout << s << endl;
    return 0;
}
