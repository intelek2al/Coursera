#pragma once

// #include <iostream>
// #include "date.h"
#include "main.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "token.h"
#include "operators.h"

using namespace std;

string DataJoin(const Date &date, const string &event);

struct Storage
{
    map<Date, vector<string>> v;
    map<Date, set<string>> s;
};

class Database
{
public:
    Database() = default;
    ~Database() = default;
    void Add(const Date &date, const string &event);
    void Print(ostream &out) const;

    template <typename Iterator>
    int RemoveEv(Iterator begin, Iterator end, const Date &date, Storage &storage)
    {
        size_t size = end - begin;
        for (auto it = begin; it != end; it++)
            storage.s[date].erase(storage.s[date].find(*it));
        storage.v[date].erase(begin, end);
        return size;
    }

    template <typename Predicat>
    int RemoveIf(Predicat predicat)
    {
        int counter = 0;

        for (auto &[date, events] : storage.v)
        {
            auto st_ped = [=, date = date](const string &event) { return predicat(date, event); };
            auto delim_it = stable_partition(events.begin(), events.end(), st_ped);
            counter += RemoveEv(events.begin(), delim_it, date, storage);
        }
        for (auto it = storage.v.begin(); it != storage.v.end();)
        {
            bool flag = true;
            if (it->second.size() == 0)
            {
                flag = false;
                storage.s.erase(it->first);
                it = storage.v.erase(it);
            }
            if (flag)
                it++;
        }
        return counter;
    }

    template <typename Predicat>
    vector<string> FindIf(Predicat predicat) const
    {
        vector<string> found;
        for (const auto &el : storage.v)
        {
            for (const auto &event : el.second)
            {
                if (predicat(el.first, event))
                {
                    found.push_back(DataJoin(el.first, event));
                }
            }
        }
        return found;
    }

    string Last(const Date &date) const;

private:
    Storage storage;
};

// Compile error: Error while compiling unit-tests for contents of file date.h. Details: Compile error: b"
// In file included from /tmp/submissionn8sk_vep/node.cpp:2:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/database.cpp:1:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/condition_parser.cpp:1:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/main.cpp:1:
// In file included from /tmp/submissionn8sk_vep/date.h:3:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:9:23: fatal error: unknown type name 'Date'
// string DataJoin(const Date &date, const string &event);
//                       ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/operators.cpp:1:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/condition_parser_test.cpp:1:
// In file included from /tmp/submissionn8sk_vep/condition_parser.h:3:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/date.cpp:1:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// In file included from /tmp/submissionn8sk_vep/token.cpp:1:
// In file included from /tmp/submissionn8sk_vep/main.h:16:
// /tmp/submissionn8sk_vep/database.h:42:78: fatal error: reference to local binding 'date' declared in enclosing function 'Database::RemoveIf'
//             auto st_ped = [=](const string &event) -> bool { return predicat(date, event); };
//                                                                              ^
// /tmp/submissionn8sk_vep/database.h:40:21: note: 'date' declared here
//         for (auto &[date, events] : storage.v)
//                     ^
// 1 error generated.
// "
