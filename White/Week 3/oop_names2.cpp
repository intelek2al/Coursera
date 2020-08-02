#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        // if (pers[year].size() == 2 && (pers[year])[0] != "0")
        //     return;
        if (pers[year].size() == 0) {
            (pers[year]).push_back("0");
            (pers[year]).push_back("0");
        }
        (pers[year])[0] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        // if (pers[year].size() == 2 && (pers[year])[1] != "0")
        //     return;
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
    string GetFullNameWithHistory(int year) {
        string full_name = "";
        vector <string> full = get_last_year_name(year);
        vector<string> extr_names;
        vector<string> extr_snames;
        
        find_name_before(year, extr_names, extr_snames);
        if (full[0] == "0" && full[1] == "0") {
            full_name = "Incognito";
        }
        else if (full[0] == "0" && full[1] != "0") {
            full_name = join_str(full[1], extr_snames) + " with unknown first name";
        }
        else if (full[0] != "0" && full[1] == "0") {
            full_name = join_str(full[0], extr_names) + " with unknown last name";
        }
        else
            full_name += join_str(full[0], extr_names) + " " + join_str(full[1], extr_snames);
        return full_name;
    }
private:
    string join_str(const string& name, const vector<string>& before) {
        string new_s = "";
        
        if (before.size() == 0)
            return name;
        else if (before.size() == 1)
            return name + " (" + before[0] + ")";
            
        new_s += name + " (";
        for (int i = 0; i < before.size(); i++) {
            new_s += before[i];
            new_s += (i != before.size() - 1) ? ", " : "";
        }
        new_s += ")";
        return new_s;
    }
    
    void find_name_before(int year, vector<string>& extr_names,
                                    vector<string>& extr_snames) {
        for (auto p : pers)
            if (p.first <= year) {
                if ((p.second)[0] != "0") {
                    if (extr_names.size() > 0) {
                        if (extr_names[0] != (p.second)[0])
                            extr_names.insert(extr_names.begin(), (p.second)[0]);
                    }
                    else
                        extr_names.insert(extr_names.begin(), (p.second)[0]);
                }
                if ((p.second)[1] != "0") {
                    if (extr_snames.size() > 0) {
                        if (extr_snames[0] != (p.second)[1])
                            extr_snames.insert(extr_snames.begin(), (p.second)[1]);
                    }
                    else
                        extr_snames.insert(extr_snames.begin(), (p.second)[1]);
                }
                
            }
        if (extr_names.size() > 0)
            extr_names.erase(extr_names.begin());
        if (extr_snames.size() > 0)
            extr_snames.erase(extr_snames.begin());
    }
    
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

int main() {
  Person person;

  person.ChangeFirstName(1965, "Polina");
  person.ChangeFirstName(1965, "Appolinaria");

  person.ChangeLastName(1965, "Sergeeva");
  person.ChangeLastName(1965, "Volkova");
  person.ChangeLastName(1965, "Volkova-Sergeeva");

  for (int year : {1964, 1965, 1966}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}