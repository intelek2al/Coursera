#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        if (pers[year].size() == 2 && (pers[year])[0] != "0")
            return;
        if (pers[year].size() == 0) {
            (pers[year]).push_back("0");
            (pers[year]).push_back("0");
        }
        (pers[year])[0] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        if (pers[year].size() == 2 && (pers[year])[1] != "0")
            return;
        if (pers[year].size() == 0) {
            (pers[year]).push_back("0");
            (pers[year]).push_back("0");
        }
        (pers[year])[1] = last_name;
    }
    string GetFullName(int year) {
        string full_name = "";
        vector <string> full = get_last_year_name(year);
        
        if (full[0] == "0" && full[1] == "0") {
            full_name = "Incognito";
        }
        else if (full[0] == "0" && full[1] != "0") {
            full_name = full[1] + " with unknown first name";
        }
        else if (full[0] != "0" && full[1] == "0") {
            full_name = full[0] + " with unknown last name";
        }
        else
            full_name += full[0] + " " + full[1];
        return full_name;
    }
private:
    vector<string> get_last_year_name(int year) {
        vector<string> full {"0", "0"};
        
        for (auto p : pers) {
            if (p.first <= year) {
                if ((p.second)[0] != "0")
                    full[0] = (p.second)[0];
                if ((p.second)[1] != "0")
                    full[1] = (p.second)[1];
            }
            else
                break;
        }
        return full;
    }
    map<int, vector<string>> pers;
};

// int main() {
//     Person person;

// 	person.ChangeFirstName(1, "1_first");
//     person.ChangeLastName (1, "1_second");

// 	cout << person.GetFullName(2) << endl;
//     return 0;
// }

