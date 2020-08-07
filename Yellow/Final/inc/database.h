#pragma once

#include "main.h"

using namespace std;

class Database
{
public:
    void Add(const Date &date, const string &event)
    {
        storage[date].push_back(event);
    }

    bool DeleteEvent(const Date &date, const string &event)
    {
        if (storage.count(date) > 0 && count(storage[date].begin(), storage[date].end(), (event)) > 0)
        {
            storage[date].erase(find(storage[date].begin(), storage[date].end(), event));
            return true;
        }
        return false;
    }

    template <typename Comp>
    int RemoveIf(Comp predicat)
    {
        int count = 0;
        for (auto &[date, events] : storage)
        {
            auto it = stable_partition(events.begin(), events.end(), predicat);
            if (it != events.end())
            {
                count = events.end() - it;
                events.erase(it, events.end());
                break;
            }
        }
        return count;
    }

    template <typename Comp>
    vector<string> FindIf(Comp predicat) const
    {
        return *find_if(storage.begin(), storage.end(), predicat);
    }

    void Print(ostream &out) const
    {
        for (const auto &item : storage)
        {
            for (const string &event : item.second)
            {
                out << item.first << " " << event << endl;
            }
        }
    }

    string Last(Date date)
    {
        auto it = upper_bound(storage.begin(), storage.end(), date);
        return *(it->second.end() - 1);
    }

private:
    map<Date, vector<string>> storage;
};
