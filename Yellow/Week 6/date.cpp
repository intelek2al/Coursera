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

Date ParseDate(istream& date_stream)
{
    bool ok = true;
    // stringstream ss(date_stream.c);


    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
    ok = ok && (date_stream.peek() == ' ' || date_stream.eof());
    date_stream.ignore(1);

    // if (!ok)
    // {
    //     throw logic_error("Wrong date format: " + date);
    // }
    return Date(year, month, day);
}

Date::Date(int new_year, int new_month, int new_day)
{
    year = new_year;
    if (new_month > 12 || new_month < 1)
    {
        throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1)
    {
        throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
}

int Date::GetYear() const
{
    return year;
}
int Date::GetMonth() const
{
    return month;
}
int Date::GetDay() const
{
    return day;
}

ostream &operator<<(ostream &stream, const Date &date)
{
    stream << setw(4) << setfill('0') << date.GetYear() << '-'
           << setw(2) << setfill('0') << date.GetMonth() << '-'
           << setw(2) << setfill('0') << date.GetDay();
    return stream;
}
