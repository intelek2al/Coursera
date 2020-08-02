#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Person {
public:
    Person (const string& name, const string& sname, const int& year) {
        year_bd = year;
        pers[year] = {name, sname};
    }
    
    void ChangeFirstName(int year, const string& first_name) {
        if (year < year_bd)
            return;
        if (pers[year].size() == 0) {
            (pers[year]).push_back("0");
            (pers[year]).push_back("0");
        }
        (pers[year])[0] = first_name;
    }
    
    void ChangeLastName(int year, const string& last_name) {
        if (year < year_bd)
            return;
        if (pers[year].size() == 0) {
            (pers[year]).push_back("0");
            (pers[year]).push_back("0");
        }
        (pers[year])[1] = last_name;
    }
    
    string GetFullName(int year) const {
        string full_name = "";
        vector <string> full = get_last_year_name(year);
        
        if (year < year_bd)
            return "No person";
        
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
    
    string GetFullNameWithHistory(int year) const {
        string full_name = "";
        vector <string> full = get_last_year_name(year);
        vector<string> extr_names;
        vector<string> extr_snames;
        
        if (year < year_bd)
            return "No person";
        
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
    string join_str(const string& name, const vector<string>& before) const {
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
                                    vector<string>& extr_snames) const {
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
    
    vector<string> get_last_year_name(int year) const {
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
    int year_bd;
    map<int, vector<string>> pers;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }
  
  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
