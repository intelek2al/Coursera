#pragma once

#include "main.h"

using namespace std;

istream &operator>>(istream &stream, Date &date);
bool operator<(const Date &lhs, const Date &rhs);
ostream &operator<<(ostream &stream, const Date &date);
ostream &operator<<(ostream &stream, vector<string> t);
bool operator<(const Date &lhs, const Date &rhs);
bool operator<=(const Date &lhs, const Date &rhs);
bool operator==(const Date &lhs, const Date &rhs);
bool operator>=(const Date &lhs, const Date &rhs);
bool operator>(const Date &lhs, const Date &rhs);
bool operator!=(const Date &lhs, const Date &rhs);
