#include <iostream>
#include <map>
#include <set>
#include <sstream>
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

bool IsPalindrom(const string &str)
{
	string s = str;
	s = "s";
	return false;
}

void TestDefault()
{
	string str;
	{
		str = "";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "0";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = " ";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "  ";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "ada";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "adda";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = " adda ";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "          madam          ";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "\tmadam\t";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "\nmadam\n";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "mad dam";
		Assert(IsPalindrom(str), "str : " + str);
	}
	{
		str = "mad  dam";
		Assert(IsPalindrom(str), "str : " + str);
	}
}

void TestIsNot()
{
	string str;
	{
		str = "amadam";
		Assert(!IsPalindrom(str), "str : " + str);
	}
	{
		str = "madama";
		Assert(!IsPalindrom(str), "str : " + str);
	}
	{
		str = "   madam    ";
		Assert(!IsPalindrom(str), "str : " + str);
	}
	{
		str = " madam \t";
		Assert(!IsPalindrom(str), "str : " + str);
	}
	{
		str = "  madam \t";
		Assert(!IsPalindrom(str), "str : " + str);
	}
	{
		str = "madcam";
		Assert(!IsPalindrom(str), "str : " + str);
	}
	{
		str = "madcm";
		Assert(!IsPalindrom(str), "str : " + str);
	}
}

int main()
{
	TestRunner runner;
	runner.RunTest(TestDefault, "TestDefault");
	runner.RunTest(TestIsNot, "TestIsNot");
	return 0;
}
