#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <list>
#include <tuple>

using namespace std;

#define PRINT(x)                             \
	cout << "Action " << #x << ": " << endl; \
	Print()

template <typename T>
class PriorityCollection
{
	struct Object;
	void Print()
	{
		cout << endl
			 << "=================================" << endl;
		for (auto o = group.begin(); o != group.end(); o++)
		{
			cout << "+++++++++++++++++++++++++++++++++" << endl;
			cout << "Object: " << o->obj << "$\t"
				 << "Id: " << o - group.begin() << endl
				 << "Priority: " << o->priority << endl;
			cout << "+++++++++++++++++++++++++++++++++" << endl;
		}
		cout << "---------------------------------" << endl
			 << endl;
		cout << "set<>" << endl;
		for (auto o = priority_set.begin(); o != priority_set.end(); o++)
		{
			cout << "+++++++++++++++++++++++++++++++++" << endl;
			cout << "Object: " << group[o->first].obj << "$\t"
				 << "Id: " << o->second << endl
				 << "Priority: " << o->first << endl;
			cout << "+++++++++++++++++++++++++++++++++" << endl;
		}
		cout << "=================================" << endl
			 << endl;
	}

public:
	using Id = int;

	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object)
	{
		Object obj;
		Id id = group.size();
		obj.obj = move(object);
		obj.priority = 0;
		priority_set.insert({0, id});
		group.push_back(move(obj));
		return id;
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end, IdOutputIt ids_begin)
	{
		// PRINT(Add);
		for (auto it = range_begin; it != range_end; it++)
		{
			*(ids_begin++) = Add(move(*it));
		}
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const
	{
		// PRINT(IsValid);
		if (id >= group.size() || id >= group[id].priority == -1)
			return false;
		for (auto &[key, id_] : priority_set)
			if (id_ == id)
				return true;
		return false;
	}

	// Получить объект по идентификатору
	const T &Get(Id id) const
	{
		// PRINT(get);
		return group[id].obj;
	}

	// Увеличить приоритет объекта на 1
	void Promote(Id id)
	{
		// PRINT(Promote);
		Object &tmp = group[id];
		priority_set.erase({tmp.priority, id});
		tmp.priority++;
		priority_set.insert({tmp.priority, id});
	}

	// Получить объект с максимальным приоритетом и его приоритет
	pair<const T &, int> GetMax() const
	{
		// PRINT(GetMax);
		return {group[prev(priority_set.end())->second].obj, prev(priority_set.end())->first};
	}

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, int> PopMax()
	{
		// PRINT(PopMax);
		auto it = prev(priority_set.end());
		int prior = it->first;
		auto o = move(group[it->second]);
		int t = it->second;

		group[t].priority = -1;
		// group.erase(group.begin() + t);
		// it->first = -1;
		priority_set.erase(it);

		return {move(o.obj), prior};
	}

private:
	struct Object
	{
		int priority;
		T obj;
	};

	vector<Object> group;
	set<pair<int, Id>> priority_set;
};

// bool operator<(const pair<int, Id> &lhs, const pair<int, Id> &rhs) {
// 	return
// }

class StringNonCopyable : public string
{
public:
	using string::string; // Позволяет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable &) = delete;
	StringNonCopyable(StringNonCopyable &&) = default;
	StringNonCopyable &operator=(const StringNonCopyable &) = delete;
	StringNonCopyable &operator=(StringNonCopyable &&) = default;
};

void TestNoCopy()
{
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id);

	for (int i = 0; i < 2; ++i)
	{
		strings.Promote(red_id);
	}

	strings.Promote(yellow_id);

	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}

	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}

	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

// void TestFFF()
// {
// 	PriorityCollection<StringNonCopyable> s;
// 	const auto white_id = s.Add("white");
// 	s.Promote(white_id);
// 	const auto yellow_id = s.Add("yellow");
// 	ASSERT_EQUAL(yellow_id->object, "yellow");
// 	ASSERT_EQUAL(yellow_id->prior, 0);
// }

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	// RUN_TEST(tr, TestFFF);

	return 0;
}