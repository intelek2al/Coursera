#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <set>
#include <sstream>
#include <tuple>
#include <functional>
#include "database.h"
#include "main.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "token.h"
#include "operators.h"

using namespace std;

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

ostream &operator<<(ostream &stream, vector<string> t)
{
    for (size_t i = 0; i < t.size(); i++)
    {
        stream << t[i];
        if (i + 1 != t.size())
            stream << ' ';
    }
    return stream;
}

bool operator<(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) < make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}

bool operator<=(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) <= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator==(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) == make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator>=(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) >= make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator>(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) > make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
bool operator!=(const Date &lhs, const Date &rhs)
{
    return make_tuple(lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()) != make_tuple(rhs.GetYear(), rhs.GetMonth(), rhs.GetDay());
}
