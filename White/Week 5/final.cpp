#include <iostream>
#include <vector>
#include <map>
#include <string.h>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date()
	{
		day = 1;
		month = 1;
		year = 1;
	}

	Date(int d, int m, int y)
	{
		if (m < 1 || m > 12)
			throw runtime_error("Month value is invalid: " + to_string(m));
		if (d < 1 || d > 31)
			throw runtime_error("Day value is invalid: " + to_string(d));
		day = d;
		month = m;
		year = y;
	}
	int GetYear() const
	{
		return year;
	}
	int GetMonth() const
	{
		return month;
	}
	int GetDay() const
	{
		return day;
	}
};

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
			else
				throw runtime_error("Wrong date format: " + str_d);
			if (stream && c0 == '-' && c1 == '-' && ss.eof())
			{
				date = Date(day, month, year);
			}
			else
				throw runtime_error("Wrong date format: " + str_d);
		}
		else
			throw runtime_error("Wrong date format: " + str_d);
	}
	return stream;
}

ostream &operator<<(ostream &stream, Date date)
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

bool operator<(const Date &lhs, const Date &rhs)
{
	if (lhs.GetYear() == rhs.GetYear())
	{
		if (lhs.GetMonth() == rhs.GetMonth())
		{
			return lhs.GetDay() < rhs.GetDay();
		}
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetYear() < rhs.GetYear();
	return tuple({})
}

class Database
{
private:
	map<Date, vector<string>> table;

public:
	void AcceptSort()
	{
		for (auto &t : table)
		{
			sort(t.second.begin(), t.second.end());
		}
	}
	void AddEvent(const Date &date, const string &event)
	{
		bool flag = true;
		if (table.count(date) != 0)
			for (const auto &ev : table[date])
			{
				if (ev == event)
				{
					flag = false;
					break;
				}
			}
		if (flag)
			table[date].push_back(event);
		AcceptSort();
	}
	bool DeleteEvent(const Date &date, const string &event)
	{
		auto itr = find(table[date].begin(), table[date].end(), event);

		if (distance(table[date].begin(), itr) >= table[date].size())
			return false;
		table[date].erase(itr);
		return true;
	}
	int DeleteDate(const Date &date)
	{
		size_t size = table[date].size();

		table[date].clear();
		table.erase(date);
		return size;
	}

	string Find(const Date &date) const
	{
		if (table.count(date) <= 0)
			return "";
		vector<string> t = table.at(date);
		string back = "";

		for (const auto &a : table.at(date))
			back += a + '\n';
		return back;
	}

	void Print() const
	{
		for (const auto &d : table)
		{
			for (const auto &e : d.second)
				cout << d.first << ' ' << e << endl;
		}
	};
};

void parse_ADD(stringstream &ss, Database &db)
{
	string event;
	Date date;
	ss >> date >> event;
	db.AddEvent(date, event);
}

string parse_DEL(stringstream &ss, Database &db)
{
	string event;
	Date date;
	string back = "";

	ss >> date >> event;
	if (event == "")
		back = "Deleted " + to_string(db.DeleteDate(date)) + " events";
	else if (db.DeleteEvent(date, event))
		back = "Deleted successfully";
	else
		back = "Event not found";
	return back;
}

void parse_PRNT(Database &db)
{
	db.Print();
}

string parse_FND(stringstream &ss, Database &db)
{
	Date date;

	ss >> date;
	return db.Find(date);
}

void Parse(const string &line, Database &db)
{
	stringstream ss(line);
	string command;

	ss >> command;
	if (command == "Add")
		parse_ADD(ss, db);
	else if (command == "Del")
		cout << parse_DEL(ss, db) << endl;
	else if (command == "Print")
		parse_PRNT(db);
	else if (command == "Find")
		cout << parse_FND(ss, db);
	else if (command == "")
		return;
	else
		throw runtime_error("Unknown command: " + command);
}

int main()
{
	Database db;
	string command;
	while (getline(cin, command))
	{
		try
		{
			Parse(command, db);
		}
		catch (const exception &e)
		{
			cout << e.what() << endl;
			return 1;
		}
	}

	return 0;
}
