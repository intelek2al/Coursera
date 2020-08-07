#include "main.h"
// #include "test_runner.h"

#include <iostream>

using namespace std;

Date ParseDate(istringstream &date_stream)
{
	bool ok = true;
	string date = date_stream.str();

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
	ok = ok && date_stream.eof();

	if (!ok)
	{
		throw logic_error("Wrong date format: " + date);
	}
	return Date(year, month, day);
}

string ParseEvent(istream &is)
{
	string event;
	while (getline(is, event))
		continue;
	return event;
}

void TestAll();

int main()
{
	// TestAll();

	Database db;

	for (string line; getline(cin, line);)
	{
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add")
		{
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}
		else if (command == "Print")
		{
			db.Print(cout);
		}
		else if (command == "Del")
		{
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date &date, const string &event) {
				return condition->Evaluate(date, event);
			};
			int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find")
		{
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date &date, const string &event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto &entry : entries)
			{
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last")
		{
			try
			{
				cout << db.Last(ParseDate(is)) << endl;
			}
			catch (invalid_argument &)
			{
				cout << "No entries" << endl;
			}
		}
		else if (command.empty())
		{
			continue;
		}
		else
		{
			throw logic_error("Unknown command: " + command);
		}
	}

	return 0;
}

// void TestParseEvent()
// {
// 	{
// 		istringstream is("event");
// 		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
// 	}
// 	{
// 		istringstream is("   sport event ");
// 		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
// 	}
// 	{
// 		istringstream is("  first event  \n  second event");
// 		vector<string> events;
// 		events.push_back(ParseEvent(is));
// 		events.push_back(ParseEvent(is));
// 		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
// 	}
// }

// void TestAll()
// {
// 	TestRunner tr;
// 	tr.RunTest(TestParseEvent, "TestParseEvent");
// 	tr.RunTest(TestParseCondition, "TestParseCondition");
// }
