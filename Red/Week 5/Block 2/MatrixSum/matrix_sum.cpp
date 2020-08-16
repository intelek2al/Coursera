#include "test_runner.h"
#include <vector>
#include <future>
#include <numeric>
#include <algorithm>

using namespace std;

template <typename Iterator>
class IteratorRange
{
private:
	Iterator first, last;

public:
	IteratorRange(Iterator f, Iterator l)
		: first(f), last(l)
	{
	}
	Iterator begin() const
	{
		return first;
	}
	Iterator end() const
	{
		return last;
	}
	size_t size() const
	{
		return last - first;
	}
};

template <typename Container>
auto Head(Container v, size_t top)
{
	return IteratorRange{
		v.begin(), next(v.begin(), min(top, v.size()))};
}

template <typename Iterator>
auto Head(Iterator bg, Iterator ed, size_t top)
{
	return IteratorRange{
		bg, next(bg, min(top, static_cast<size_t>(ed - bg)))};
}

template <typename Iterator>
class Paginator
{
public:
	Paginator(Iterator _b, Iterator _e, size_t size)
	{
		size_t content_size = _e - _b;
		page_size = size;
		while (content_size > 0)
		{
			IteratorRange<Iterator> it = Head(_b, _e, page_size);
			pages.push_back(it);
			content_size -= it.size();
			_b = it.end();
		}
	}
	size_t size() const
	{
		return pages.size();
	}
	auto begin()
	{
		return pages.begin();
	}

	auto end()
	{
		return pages.end();
	}

private:
	size_t page_size = 0;
	vector<IteratorRange<Iterator>> pages;
};

template <typename C>
auto Paginate(C &c, size_t page_size)
{
	return Paginator{c.begin(), c.end(), page_size};
}

template <typename Matrix>
int64_t SumMx(const Matrix &mx)
{
	int64_t sum = 0;
	for (const auto &row : mx)
	{
		for (const auto &el : row)
			sum += el;
	}
	return sum;
}

int64_t
CalculateMatrixSum(const vector<vector<int>> &matrix)
{
	size_t size = matrix.size();
	// int size_block = size / 4;
	vector<future<int64_t>> resoults;
	for (const auto &row : Paginate(matrix, 2000))
	{
		resoults.push_back(async([=] { return SumMx(row); }));
	}
	int64_t sum = 0;
	for (auto &f : resoults)
	{
		sum += (f.get());
	}
	return sum;
}

void TestCalculateMatrixSum()
{
	const vector<vector<int>> matrix = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12},
		{13, 14, 15, 16}};
	ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
}
