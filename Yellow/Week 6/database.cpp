#include "main.h"

using namespace std;

void Database::Add(const Date& date, const string& event) {
    storage_v[date].push_back(event);
    storage_s[date].insert(event);
}

void Database::Print(ostream &out) {
    for (const auto &item : storage_v)
    {
        for (const string &event : item.second)
        {
            out << item.first << " " << event << endl;
        }
    }
}

template<class Predicat>
int Database::RemoveIf(Predicat predicat) {
    if (predicat())
}

template<class Predicat>
vector<string> Database::FindIf(Predicat predicat) {

}

string Database::Last(const Date& date) {

}
