#include <query.h>
#include <responses.h>
#include <bus_manager.h>

using namespace std;
using type_map = map<string, vector<string>>;

// void PrintMap(const type_map &m)
// {
// 	for (const auto &[key, value] : m)
// 	{
// 		cout << key << " :  ";
// 		for (const auto &v : value)
// 			cout << v << " ";
// 		cout << endl;
// 	}
// }

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