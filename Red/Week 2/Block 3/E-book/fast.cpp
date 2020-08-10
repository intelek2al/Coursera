#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <iterator>
#include <sstream>
#include <map>
#include <set>
// #include "profile.h"
// #include "test.h"

using namespace std;

class ReadingManager
{
public:
	ReadingManager() = default;
	void READ(bool flag) const
	{
		if (flag)
			for (const auto &[user, page] : users_to_page)
			{
				cout << "===================================================" << endl;
				cout << "User: #" << user << " --> " << page << "p." << endl;
				cout << "===================================================" << endl;
			}
		else
			for (const auto &[page, users] : pages_to_user)
			{
				cout << "===================================================" << endl;
				cout << "Page: #" << page << " --> " << *users.begin() << endl;
				cout << "===================================================" << endl;
			}
	}
	void Read(int user_id, int page_count)
	{
		int old_p;
		if (users_to_page.count(user_id) == 1)
		{
			old_p = users_to_page.at(user_id);
			pages_to_user[old_p].erase(user_id);
			if (pages_to_user[old_p].size() == 0)
				pages_to_user.erase(old_p);
		}
		users_to_page[user_id] = page_count;
		pages_to_user[page_count].insert(user_id);
	}

	double Cheer(int user_id) const
	{
		if (users_to_page.count(user_id) == 0)
		{
			return 0;
		}
		if (users_to_page.size() == 1)
		{
			return 1;
		}
		// READ(false);
		const int page_count = users_to_page.at(user_id);
		auto it = pages_to_user.lower_bound(page_count);
		// cout << endl
		// 	 << PRINT_MAC(*(it->second.begin())) << endl;
		int low_users = 0;
		for (auto iter = pages_to_user.begin(); iter != it; iter++)
			low_users += iter->second.size();
		if (static_cast<long long unsigned int>(low_users) >= users_to_page.size())
			return 0;
		return low_users * 1.0 / (users_to_page.size() - 1);
	}

private:
	static const int MAX_USER_COUNT_ = 100'000;

	map<int, int> users_to_page;
	map<int, set<int>> pages_to_user;
	// static const int MAX_USER_COUNT_ = 100'000;
	// vector<int> user_page_counts_;
	// vector<int> sorted_users_;	 // отсортированы по убыванию количества страниц
	// vector<int> user_positions_; // позиции в векторе sorted_users_
};

// void TestRead()
// {
// 	ReadingManager manager;

// 	ASSERT_EQUAL(0, manager.Cheer(5));
// 	manager.Read(1, 10);
// 	ASSERT_EQUAL(1, manager.Cheer(1));
// 	manager.Read(2, 5);
// 	manager.Read(3, 7);
// 	ASSERT_EQUAL(0, manager.Cheer(2));
// 	ASSERT_EQUAL(0.5, manager.Cheer(3));
// 	manager.Read(3, 10);
// 	ASSERT_EQUAL(0.5, manager.Cheer(3));
// 	manager.Read(3, 11);
// 	ASSERT_EQUAL(1, manager.Cheer(3));
// 	ASSERT_EQUAL(0.5, manager.Cheer(1));
// 	manager.Read(2, 11);
// 	ASSERT_EQUAL(0.5, manager.Cheer(3));
// 	ASSERT_EQUAL(0.5, manager.Cheer(2));
// 	manager.Read(2, 12);
// 	ASSERT_EQUAL(0.5, manager.Cheer(3));
// 	ASSERT_EQUAL(1, manager.Cheer(2));
// 	manager.Read(1, 13);
// 	manager.Read(2, 13);
// 	manager.Read(3, 13);
// 	ASSERT_EQUAL(0, manager.Cheer(1));
// 	ASSERT_EQUAL(0, manager.Cheer(2));
// 	ASSERT_EQUAL(0, manager.Cheer(3));
// 	cout << "TestRead OK" << endl;
// }

// void TestRead2()
// {
// 	{
// 		ReadingManager manager;
// 		ASSERT_EQUAL(manager.Cheer(5), 0);
// 		manager.Read(1, 10);
// 		manager.Read(2, 10);
// 		manager.Read(3, 9);
// 		manager.Read(2, 11);
// 		ASSERT_EQUAL(manager.Cheer(1), 0.5);
// 	}
// 	{
// 		ReadingManager manager;
// 		ASSERT_EQUAL(manager.Cheer(5), 0);
// 		manager.Read(1, 10);
// 		manager.Read(2, 11);
// 		ASSERT_EQUAL(manager.Cheer(1), 0);
// 	}
// 	cout << "TestRead2 OK" << endl;
// }

// TEST2(ReadingManager, mgr)

int main()
{
	// TestRead();
	// TestRead2();
	// Для ускорения чтения данных отключается синхронизация
	// cin и cout с stdio,
	// а также выполняется отвязка cin от cout
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ReadingManager manager;
	// stringstream ss;

	int query_count;
	cin >> query_count;

	for (int query_id = 0; query_id < query_count; ++query_id)
	{
		string query_type;
		cin >> query_type;
		int user_id;
		cin >> user_id;

		if (query_type == "READ")
		{
			int page_count;
			cin >> page_count;
			{
				// LOG_DURATION("Read");
				manager.Read(user_id, page_count);
			}
		}
		else if (query_type == "CHEER")
		{
			cout << setprecision(6) << manager.Cheer(user_id) << "\n";
		}
	}
	// cout << ss.str();

	return 0;
}