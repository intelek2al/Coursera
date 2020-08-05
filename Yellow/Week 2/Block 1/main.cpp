#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;
using type_map = map<string, vector<string>>;

enum class QueryType
{
	NewBus,
	BusesForStop,
	StopsForBus,
	AllBuses
};

struct Query
{
	QueryType type;
	string bus;
	string stop;
	vector<string> stops;

	void FreeStruct(Query &q)
	{
		q.bus = q.stop = "";
		q.stops.clear();
	}
};

istream &operator>>(istream &is, Query &q)
{
	string req;

	q.FreeStruct(q);
	is >> req;
	if (req == "NEW_BUS")
	{
		int stop_count = 0;
		q.type = QueryType::NewBus;
		is >> q.bus;
		is >> stop_count;
		for (int i = 0; i < stop_count; i++)
		{
			string stop;
			is >> stop;
			q.stops.push_back(stop);
		}
	}
	else if (req == "BUSES_FOR_STOP")
	{
		q.type = QueryType::BusesForStop;
		is >> q.stop;
	}
	else if (req == "STOPS_FOR_BUS")
	{
		q.type = QueryType::StopsForBus;
		is >> q.bus;
	}
	else if (req == "ALL_BUSES")
	{
		q.type = QueryType::AllBuses;
	}
	return is;
}

struct BusesForStopResponse
{
	bool is_exist;
	vector<string> buses;
	string stop;

	BusesForStopResponse(bool is, string s, vector<string> b)
	{
		is_exist = is;
		buses = b;
		stop = s;
	}
};

ostream &operator<<(ostream &os, const BusesForStopResponse &r)
{
	if (!r.is_exist)
	{
		os << "No stop";
	}
	else
	{
		for (const string &bus : r.buses)
		{
			os << bus << " ";
		}
	}
	return os;
}

struct StopsForBusResponse
{
	bool is_exist;
	type_map stops;
	type_map buses;
	string bus;

	StopsForBusResponse(bool is_e, type_map ss, type_map bs, string b)
	{
		is_exist = is_e;
		bus = b;
		buses = bs;
		stops = ss;
	}
};

ostream &operator<<(ostream &os, const StopsForBusResponse &r)
{
	if (!r.is_exist)
	{
		os << "No bus";
	}
	else
	{
		vector<string> tmp = r.buses.at(r.bus);
		auto it = tmp.begin();
		for (const auto &stop : tmp)
		{
			os << "Stop " << stop << ": ";
			if (r.stops.at(stop).size() == 1)
			{
				os << "no interchange";
			}
			else
			{
				for (const string &other_bus : r.stops.at(stop))
				{
					if (r.bus != other_bus)
					{
						os << other_bus << " ";
					}
				}
			}
			if (it != (tmp.end() - 1))
			{
				os << endl;
			}
			it++;
		}
	}
	return os;
}

struct AllBusesResponse
{
	bool is_exist;
	type_map buses;
};

ostream &operator<<(ostream &os, const AllBusesResponse &r)
{
	if (r.is_exist)
	{
		auto it = r.buses.begin();
		for (const auto &bus_item : r.buses)
		{
			os << "Bus " << bus_item.first << ": ";
			for (const string &stop : bus_item.second)
			{
				os << stop << " ";
			}
			it++;
			if (it != r.buses.end())
				os << endl;
				}
	}
	else
		os << "No buses";
	return os;
}

class BusManager
{
private:
	type_map table_for_bus;	 // [bus] = vector<stop>
	type_map table_for_stop; // [stop] = vector<bus>

public:
	void AddBus(const string &bus, const vector<string> &stops)
	{
		table_for_bus[bus] = stops;
		for (const auto &stop : stops)
			table_for_stop[stop].push_back(bus);
	}

	BusesForStopResponse GetBusesForStop(const string &stop) const
	{
		bool is_exist = table_for_stop.count(stop) != 0;
		vector<string> value;

		if (is_exist)
			value = table_for_stop.at(stop);
		return BusesForStopResponse(is_exist, stop, value);
	}

	StopsForBusResponse GetStopsForBus(const string &bus) const
	{
		// vector<string> cstops;
		bool is_exist = table_for_bus.count(bus) != 0;

		// if (table_for_bus.count(bus) != 0)
		// {
		// 	is_exist = true;
		// 	cstops = table_for_bus.at(bus);
		// 	for (const auto &stop : cstops)
		// 	{
		// 		stop_map[stop] = table_for_stop.at(stop);
		// 	}
		// }
		return {is_exist, table_for_stop, table_for_bus, bus};
	}

	AllBusesResponse GetAllBuses() const
	{
		return {!table_for_bus.empty(), table_for_bus};
	}
};

void PrintMap(const type_map &m)
{
	for (const auto &[key, value] : m)
	{
		cout << key << " :  ";
		for (const auto &v : value)
			cout << v << " ";
		cout << endl;
	}
}

int main()
{
	stringstream ss;
	int query_count;
	Query q;

	cin >> query_count;

	BusManager bm;
	for (int i = 0; i < query_count; ++i)
	{
		cin >> q;
		switch (q.type)
		{
		case QueryType::NewBus:
			bm.AddBus(q.bus, q.stops);
			break;
		case QueryType::BusesForStop:
			ss << bm.GetBusesForStop(q.stop) << endl;
			break;
		case QueryType::StopsForBus:
			ss << bm.GetStopsForBus(q.bus) << endl;
			break;
		case QueryType::AllBuses:
			ss << bm.GetAllBuses() << endl;
			// PrintMap(bm.table_for_bus);
			// cout << "----------------" << endl;
			// PrintMap(bm.table_for_stop);
			break;
		}
	}
	cout << ss.str();

	return 0;
}