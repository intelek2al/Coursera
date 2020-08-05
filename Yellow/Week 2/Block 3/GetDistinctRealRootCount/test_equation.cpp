#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <ostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream &operator<<(ostream &os, const vector<T> &s)
{
	os << "{";
	bool first = true;
	for (const auto &x : s)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s)
{
	os << "{";
	bool first = true;
	for (const auto &x : s)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream &operator<<(ostream &os, const map<K, V> &m)
{
	os << "{";
	bool first = true;
	for (const auto &kv : m)
	{
		if (!first)
		{
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template <class T, class U>
void AssertEqual(const T &t, const U &u, const string &hint = {})
{
	if (t != u)
	{
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty())
		{
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string &hint)
{
	AssertEqual(b, true, hint);
}

class TestRunner
{
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string &test_name)
	{
		try
		{
			func();
			cerr << test_name << " OK" << endl;
		}
		catch (exception &e)
		{
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		}
		catch (...)
		{
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner()
	{
		if (fail_count > 0)
		{
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

int GetDistinctRealRootCount(double a, double b, double c)
{
	double D = b * b - 4 * a * c;
	// cout << D << endl;
	if (a != 0 && b == 0)
		return 1;
	if (a == 0)
		return b == 0 ? 0 : 1;
	if (D < 0)
		return 0;
	else if (D == 0)
		return 1;
	return 2;
}

void TestDiscrNone()
{
	mt19937 gen;
	uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i)
	{
		const auto a = unif(gen);
		const auto b = unif(gen);
		const auto c = unif(gen);

		const auto count = GetDistinctRealRootCount(a, b, c);

		Assert(count >= 0 && count <= 2,
			   "Quadratic equation has only 0, 1 or 2 real roots.");
	}
}

void TestDiscrStandart()
{
	mt19937 gen;
	uniform_real_distribution<> unif(-10, 10);

	for (auto i = 0; i < 100; ++i)
	{
		const auto x_1 = unif(gen);

		const auto p = x_1 + x_1;
		const auto q = x_1 * x_1;

		const auto count = GetDistinctRealRootCount(1, p, q);
		stringstream description;
		description << showpos << "x^2" << p << "x" << q
					<< " = 0 has 1 real root.";

		AssertEqual(count, 1, description.str());
	}
}

void TestDiscrQadr()
{
	AssertEqual(GetDistinctRealRootCount(1, 0, 1), 0,
				"x^2+1 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, 3, 4), 0,
				"x^2+3x+4 = 0 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(1, -2, 10), 0,
				"x^2-2x+10 = 0 has 0 real roots.");
}

void TestDiscrOnlyA()
{
	AssertEqual(GetDistinctRealRootCount(0, 2, 1), 1,
				"2x+1 = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, -1, 0), 1,
				"-x = 0 has 1 real root.");
	AssertEqual(GetDistinctRealRootCount(0, 120, -10), 1,
				"120x - 10 = 0 has 1 real root.");
}

void TestDiscrOnlyB()
{
	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0,
				"c = 0, where c = 1 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0,
				"c = 0, where c = -10 has 0 real roots.");
	AssertEqual(GetDistinctRealRootCount(0, 0, 189238910), 0,
				"c = 0, where c = 189238910 has 0 real roots.");
}

// void TestDiscrNone()
// {
// 	AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "a == 0 b == 0 c == 1 | 0");
// 	AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "a == 0 b == 1 c == 0 | 1");
// 	AssertEqual(GetDistinctRealRootCount(1, 0, 0), 1, "a == 1 b == 0 c == 0 | 1");
// }

// void TestDiscrStandart()
// {
// 	AssertEqual(GetDistinctRealRootCount(1, -3, 2), 2, "a == 1 b == -3 c == 2 | 2");
// 	AssertEqual(GetDistinctRealRootCount(1, -5, 6), 2, "a == 1 b == -5 c == 6 | 2");
// 	AssertEqual(GetDistinctRealRootCount(1, -5, -6), 2, "a == 1 b == -5 c == -6 | 2");
// 	AssertEqual(GetDistinctRealRootCount(1, 5, -6), 2, "a == 1 b == -5 c == -6 | 2");
// }

// void TestDiscrQadr()
// {
// 	AssertEqual(GetDistinctRealRootCount(1, 2, 1), 1, "a == 1 b == 2 c == 1 | 1");
// 	AssertEqual(GetDistinctRealRootCount(1, 6, 9), 1, "a == 1 b == 6 c == 9 | 1");
// 	AssertEqual(GetDistinctRealRootCount(1, -6, 9), 1, "a == 1 b == -6 c == 9 | 1");
// }

// void TestDiscrOnlyC()
// {
// 	AssertEqual(GetDistinctRealRootCount(0, 0, 5), 0, "a == 0 b == 0 c == 5 | 0");
// 	AssertEqual(GetDistinctRealRootCount(0, 0, -10), 0, "a == 0 b == 0 c == -10 | 0");
// 	AssertEqual(GetDistinctRealRootCount(0, 0, 10000), 0, "a == 0 b == 0 c == 10000 | 0");
// }

// void TestDiscrOnlyB()
// {
// 	AssertEqual(GetDistinctRealRootCount(0, 5, 0), 1, "a == 0 b == 5 c == 5 | 1");
// 	AssertEqual(GetDistinctRealRootCount(0, -10, 0), 1, "a == 0 b == -10 c == 0 | 1");
// 	AssertEqual(GetDistinctRealRootCount(0, 100000, 0), 1, "a == 0 b == 100000 c == 0 | 1");
// }

// void TestDiscrOnlyA()
// {
// 	AssertEqual(GetDistinctRealRootCount(5, 0, 0), 1, "a == 5 b == 0 c == 0 | 1");
// 	AssertEqual(GetDistinctRealRootCount(-10, 0, 0), 1, "a == -10 b == 0 c == 0 | 1");
// 	AssertEqual(GetDistinctRealRootCount(100000, 0, 0), 1, "a == 100000 b == 0 c == 0 | 1");
// }

// void TestDiscrNull()
// {
// 	AssertEqual(GetDistinctRealRootCount(5, 0, 5), 0, "a == 5 b == 0 c == 5 | 0");
// 	AssertEqual(GetDistinctRealRootCount(5, 3, 6), 0, "a == 5 b == 3 c == 6 | 0");
// 	AssertEqual(GetDistinctRealRootCount(-10, 7, -5), 0, "a == -10 b == 7 c == -5 | 0");
// }

// void TestDiscrNoneB()
// {
// 	AssertEqual(GetDistinctRealRootCount(5, 0, -225), 1, "a == 5 b == 0 c == -255 | 1");
// 	AssertEqual(GetDistinctRealRootCount(1, 0, -2), 1, "a == 1 b == 0 c == -2 | 1");
// 	AssertEqual(GetDistinctRealRootCount(-10, 0, 500), 1, "a == -10 b == 0 c == 500 | 1");
// }

int main()
{
	TestRunner runner;
	runner.RunTest(TestDiscrNone, "TestDiscrNone");
	runner.RunTest(TestDiscrStandart, "TestDiscrStandart");
	runner.RunTest(TestDiscrQadr, "TestDiscrQadr");
	runner.RunTest(TestDiscrOnlyA, "TestDiscrOnlyA");
	runner.RunTest(TestDiscrOnlyB, "TestDiscrOnlyB");
	return 0;
}
