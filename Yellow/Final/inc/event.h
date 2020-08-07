#pragma once

#include "main.h"

using namespace std;


class Event {
public:
    Event();
    Event(const string &event);
    void AddEvent(const string &event);
    template<class Comp>
    vector<string> GetEventByComp(Comp cmp) const;
    vector<string> GetEvents() const;
    ~Event();
private:
    vector<string> event_v;
    set<string> event_s;
};

