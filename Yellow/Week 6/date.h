#pragma once

#include "main.h"

using namespace std;


class Date
{
public:
    Date() = default;
    ~Date() = default;
    Date(int new_year, int new_month, int new_day);
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    int year;
    int month;
    int day;
};