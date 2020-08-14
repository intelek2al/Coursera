#include "test_runner.h"
#include "profile.h"

#include <cstdint>
#include <iterator>
#include <numeric>
#include <vector>
#include <array>
#include <list>

using namespace std;

template <typename RandomIt, typename Container>
auto MoveIter(Container &container, RandomIt it, size_t step)
{
	for (size_t i = 1; i < step; i++)
	{
		it = (next(it) == container.end()) ? container.begin() : next(it);
	}
	return it;
}
template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
{
	list<typename RandomIt::value_type> pool;
	move(first, last, back_inserter(pool));
	auto pos = pool.begin();
	while (!pool.empty())
	{
		// cout << "asdasd" << endl;
		*(first++) = move(*pos);
		if (pool.size() <= 1)
		{
			break;
		}
		auto next_pos = (next(pos) == pool.end()) ? pool.begin() : next(pos);
		pool.erase(pos);
		pos = next_pos;
		pos = MoveIter(pool, pos, step_size);
	}
}

// template <typename RandomIt>
// void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size)
// {
// 	vector<typename RandomIt::value_type> pool;
// 	size_t cur_pos = 0;
// 	move(first, last, back_inserter(pool));
// 	while (!pool.empty())
// 	{
// 		*(first++) = move(pool[cur_pos]);
// 		pool.erase(pool.begin() + cur_pos);
// 		if (pool.empty())
// 		{
// 			break;
// 		}
// 		cur_pos = (cur_pos + step_size - 1) % pool.size();
// 	}
// }

vector<int> MakeTestVector()
{
	vector<int> numbers(10);
	iota(begin(numbers), end(numbers), 0);
	return numbers;
}

void TestIntVector()
{
	const vector<int> numbers = MakeTestVector();
	// {
	// 	vector<int> numbers_copy = numbers;
	// 	MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
	// 	ASSERT_EQUAL(numbers_copy, numbers);
	// }
	{
		cout << "start" << endl;
		LOG_DURATION("Test Max: ");
		vector<int> numbers_copy = numbers;
		MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
		ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
	}
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt
{
	int value;

	NoncopyableInt(const NoncopyableInt &) = delete;
	NoncopyableInt &operator=(const NoncopyableInt &) = delete;

	NoncopyableInt(NoncopyableInt &&) = default;
	NoncopyableInt &operator=(NoncopyableInt &&) = default;
};

bool operator==(const NoncopyableInt &lhs, const NoncopyableInt &rhs)
{
	return lhs.value == rhs.value;
}

ostream &operator<<(ostream &os, const NoncopyableInt &v)
{
	return os << v.value;
}

void TestAvoidsCopying()
{
	vector<NoncopyableInt> numbers;
	numbers.push_back({1});
	numbers.push_back({2});
	numbers.push_back({3});
	numbers.push_back({4});
	numbers.push_back({5});

	MakeJosephusPermutation(begin(numbers), end(numbers), 2);

	vector<NoncopyableInt> expected;
	expected.push_back({1});
	expected.push_back({3});
	expected.push_back({5});
	expected.push_back({4});
	expected.push_back({2});

	ASSERT_EQUAL(numbers, expected);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	RUN_TEST(tr, TestAvoidsCopying);
	return 0;
}
