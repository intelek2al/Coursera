#pragma once

// #include <iostream>
// #include "date.h"
#include "main.h"

using namespace std;

class Database {
public:
    Database() = default;
    ~Database() = default;
    void Add(const Date& date, const string& event);
    void Print(ostream& out);
    template<class Predicat>
    int RemoveIf(Predicat predicat);
    template<class Predicat>
    vector<string> FindIf(Predicat predicat);
    string Last(const Date& date);

private:
    map<Date, vector<string>> storage_v;
    map<Date, set<string>> storage_s;
};
