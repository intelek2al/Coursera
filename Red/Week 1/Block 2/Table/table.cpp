#include "test_runner.h"

using namespace std;

// template <typename T>
// class Table
// {
// public:
// 	Table(const size_t &_h, const size_t &_w)
// 	{
// 		Resize(_h, _w);
// 	}
// 	~Table()
// 	{
// 		for (size_t i = 0; i < h; i++)
// 		{
// 			table[i].clear();
// 		}
// 		table.clear();
// 	}
// 	void Resize(const size_t &_h, const size_t &_w)
// 	{
// 		table.resize(_h);
// 		for (auto &r : table)
// 			r.resize(_w);
// 		h = table.size();
// 		w = table[0].size();
// 	}

// 	const vector<T> &operator[](const size_t &indx) const
// 	{
// 		return table[indx];
// 	}

// 	vector<T> &operator[](const size_t &indx)
// 	{
// 		return table[indx];
// 	}

// 	pair<size_t, size_t> Size() const
// 	{
// 		return make_pair(h, w);
// 	}

// private:
// 	size_t h;
// 	size_t w;
// 	vector<vector<T>> table;
// };

template <typename T>
class Table
{
private:
	vector<vector<T>> data;

public:
	Table(size_t rows, size_t columns)
	{
		Resize(rows, columns);
	}

	const vector<T> &operator[](size_t idx) const
	{
		return data[idx];
	}

	vector<T> &operator[](size_t idx)
	{
		return data[idx];
	}

	void Resize(size_t rows, size_t columns)
	{
		data.resize(rows);
		for (auto &item : data)
		{
			item.resize(columns);
		}
	}

	pair<size_t, size_t> Size() const
	{
		if (!data.empty() && !data[0].empty())
		{
			return {data.size(), data[0].size()};
		}

		return {0, 0};
	}
};

void TestTable()
{
	Table<int> t(1, 1);
	// cout << "ASDASD" << endl;
	ASSERT_EQUAL(t.Size().first, 1u);
	// cout << "ASDASD" << endl;
	ASSERT_EQUAL(t.Size().second, 1u);
	// cout << "ASDASD" << endl;
	t[0][0] = 42;
	// cout << "ASDASD" << endl;
	ASSERT_EQUAL(t[0][0], 42);
	// cout << "ASDASD" << endl;
	t.Resize(3, 4);
	// cout << "ASDASD" << endl;
	ASSERT_EQUAL(t.Size().first, 3u);
	// cout << "ASDASD" << endl;
	ASSERT_EQUAL(t.Size().second, 4u);
	// cout << "ASDASD" << endl;
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestTable);
	return 0;
}
