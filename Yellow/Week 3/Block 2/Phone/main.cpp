#include <iostream>
#include <sstream>
#include <vector>
#include "phone_number.h"

using namespace std;

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const
{
    return '+' + country_code_ + '-' + city_code_ + '-' + local_number_;
}

PhoneNumber::PhoneNumber(const string &international_number)
{
    stringstream ss(international_number);
    vector<string> v;
    char start = '\0';
    string temp;
    char c = '-';

    ss >> start;
    if (start == '+')
        for (int i = 0; i < 3 && getline(ss, temp, c); i++)
        {
            c = i == 1 ? '\0' : '-';
            v.push_back(temp);
        }
    else
        throw invalid_argument(to_string(start));
    if (v.size() == 3 && v[0].length() > 0 && v[1].length() > 0 && v[2].length() > 0)
    {
        country_code_ = v[0];
        city_code_ = v[1];
        local_number_ = v[2];
    }
    else
        throw invalid_argument("Invalid argument");
    ;
}

// int main()
// {
//     PhoneNumber p("-1-2-coursera-cppasd");
//     cout << p.GetInternationalNumber();
// }