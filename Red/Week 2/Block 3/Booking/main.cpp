#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
#include <set>
#include <deque>
#include <tuple>
#include <deque>
// #include <stdint>

using namespace std;

struct Room
{
	long long int time;
	int client_id;
	int room_count;
};

// bool operator<(const Room &lhs, const Room &rhs)
// {
// 	return tie(lhs.time/*, lhs.client_id, lhs.room_count*/) < tie(rhs.time/*, rhs.client_id, rhs.room_count*/);
// }

class Booking
{
public:
	void Print() const {
		cout << "================================================================" << endl;
		for (const auto &[hotel, orders] : table) {
			cout << "---------------------" << endl;
			cout << "HOTEL: " << hotel << ":" << endl;
			for (const auto &order : orders) {
				cout << "\tTime: " << order.time << "s;\tClient: #" << order.client_id << ";\tCount rooms: " << order.room_count << endl;
			}
			cout << endl;
			for (const auto&[client, count] : users.at(hotel)) {
				cout << "\tClient #" << client << " has: " << count << " orders" << endl;
			}
			cout << endl;
			cout << "---------------------" << endl;
		}
		cout << "================================================================" << endl;
	}
	Booking() = default;
	~Booking() = default;
	void Book(const Room &data, const string &hotel)
	{
		/*auto it = */(table[hotel].push_back(data))/*.first*/;
		rooms[hotel] += data.room_count;
		users[hotel][data.client_id]++;
		max_time = max(data.time, max_time);
		new_user_flag[hotel] = true;
		CheckBooks(hotel);
		// cout << "MAX_TIME " << max_time<<endl;
	}
	int Clients(const string &hotel)
	{
		CheckBooks(hotel);
		return users[hotel].size();
	}
	int Rooms(const string &hotel)
	{
		CheckBooks(hotel);
		// int rooms = 0;
		// for (const auto& order:table[hotel])
		// 	rooms += order.room_count;
		return rooms[hotel];
	}

private:
	map<string, bool> new_user_flag;
	map<string, deque<Room>> table;
	map<string, map<int, int>> users;
	map<string, int> rooms;
	long long max_time = -1'000'000'000'000'000'001;
	// template <typename Iterator>
	void CheckBooks(const string& hotel)
	{
		auto& clients = table[hotel];
		while (!clients.empty() && clients.front().time <= max_time - 86400) {
			int temp_room = clients.front().room_count;
			int temp_client = clients.front().client_id;

			clients.pop_front();
			rooms[hotel] -= temp_room;

			if (users[hotel][temp_client] == 1) {
				users[hotel].erase(temp_client);
			}
			else {
				--users[hotel][temp_client];
			}
		}
		// while (!clients.empty() && clients.begin()->time + 86400 <= max_time) {
	// 	users[hotel][clients.begin()->client_id]--;
	// 	rooms[hotel] -= clients.begin()->room_count;
	// 	clients.pop_front();
	// 	if (users[hotel][clients.begin()->client_id] == 0)
	// 	{
	// 		users[hotel].erase(clients.begin()->client_id);
	// 		// it++
	// 		continue;
	// 	}
	// }
	}
};

int main()
{
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);
	string request;
	int n;
	Booking bk;
	// stringstream out;

	cin >> n;

	// for (;;)
	for (int i = 0; i < n; i++)
	{
		cin >> request;
		if (request == "BOOK")
		{
			long long int time;
			string hotel;
			int client_id;
			int room_count;
			cin >> time >> hotel >> client_id >> room_count;
			bk.Book({ time, client_id, room_count }, hotel);
			// cout << "asdasd" << endl;
			// bk.Print();
		}
		else if (request == "CLIENTS")
		{
			string hotel;
			cin >> hotel;
			cout << bk.Clients(hotel) << '\n';
			// bk.Print();
		}
		else if (request == "ROOMS")
		{
			string hotel;
			cin >> hotel;
			cout << bk.Rooms(hotel) << '\n';
			// bk.Print();
		}
	}
	// cout << out.str() << endl;
}
