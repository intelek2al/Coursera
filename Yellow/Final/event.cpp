#include "main.h"

using namespace std;

Event::Event() {}
Event::~Event() {
    event_s.clear();
    event_v.clear();
}

Event::Event(const string &event) {
    event_v.push_back(event);
    event_s.insert(event);
}

void Event::AddEvent(const string &event) {
    event_v.push_back(event);
    event_s.insert(event);
}

vector<string> Event::GetEventByComp(Comp cmp) {
    return event_v;
}

vector<string> Event::GetEvents() {
    return event_v;
}

