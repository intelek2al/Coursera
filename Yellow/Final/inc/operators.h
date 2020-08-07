#pragma once

#include "main.h"

istream &operator>>(istream &stream, Date &date)
{
    int day;
    int month;
    int year;

    if (stream)
    {
        string str_d;
        char c0;
        char c1;
        stream >> str_d;
        stringstream ss(str_d);
        string d;

        if (ss)
        {
            ss >> year;
            ss >> c0;
            ss >> month;
            ss >> c1;
            if (ss.peek() == '+')
                ss.ignore(1);
            if (isdigit(ss.peek()))
                ss >> day;
            if (stream && c0 == '-' && c1 == '-' && ss.eof())
            {
                date = Date(day, month, year);
            }
        }
    }
    return stream;
}

bool operator<(const Date &lhs, const Date &rhs)
{
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
        vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
        << setw(2) << setfill('0') << date.GetMonth() << '-'
        << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

ostream &operator<<(ostream &stream, vector<string> t)
{
    for (int i = 0; i < t.size(); i++)
    {
        stream << t[i];
        if (i + 1 != t.size())
            stream << ' ';
    }
    return stream;
}
