#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>

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

/* ************************************************************************************************************************ */

class Rational
{
public:
	Rational()
	{
		num = 0;
		den = 1;
	}

	Rational(int numerator, int denominator)
	{
		if (denominator < 0)
		{
			numerator *= -1;
			denominator *= -1;
		}
		num = numerator / gcd(abs(numerator), abs(denominator));
		den = denominator / gcd(abs(numerator), abs(denominator));
	}

	int Numerator() const
	{
		return num;
	}

	int Denominator() const
	{
		return den;
	}

private:
	int num;
	int den;
};

Rational operator+(const Rational &a, const Rational &b)
{
	int den = lcm(a.Denominator(), b.Denominator());
	int num = a.Numerator() * den / a.Denominator() + b.Numerator() * den / b.Denominator();

	return Rational(num, den);
}

Rational operator-(const Rational &a, const Rational &b)
{
	int den = lcm(a.Denominator(), b.Denominator());
	int num = a.Numerator() * den / a.Denominator() - b.Numerator() * den / b.Denominator();

	return Rational(num, den);
}

bool operator==(const Rational &a, const Rational &b)
{
	return (a.Denominator() == b.Denominator() && a.Numerator() == b.Numerator());
}

Rational operator*(const Rational &a, const Rational &b)
{
	return Rational(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
}

Rational operator/(const Rational &a, const Rational &b)
{
	return Rational(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
}

ostream &operator<<(ostream &stream, const Rational &a)
{
	if (stream)
		stream << a.Numerator() << "/" << a.Denominator();
	return stream;
}

istream &operator>>(istream &stream, Rational &a)
{
	int num = 0;
	int den = 1;
	string str;

	if (getline(stream, str, ' '))
	{
		stringstream strm(str);

		getline(strm, str, '/');
		num = atoi(&str[0]);
		getline(strm, str);
		den = atoi(&str[0]);
		a = den != 0 ? Rational(num, den) : Rational();
	}
	else
		a = Rational();
	return stream;
}

bool operator<(const Rational &a, const Rational &b)
{
	int den = lcm(a.Denominator(), b.Denominator());
	int num1 = a.Numerator() * den / a.Denominator();
	int num2 = b.Numerator() * den / b.Denominator();

	return num1 < num2;
}

/* ***************************************************************************************************************** */

void TestAdd()
{
	{
		Rational q(0, 1);
		Assert(q.Numerator() == 0 && q.Denominator() == 1, "0/1");
	}
	{
		Rational q(1, 1);
		Assert(q.Numerator() == 1 && q.Denominator() == 1, "1/1");
	}
	{
		Rational q(-0, 1);
		Assert(q.Numerator() == 0 && q.Denominator() == 1, "0/1");
	}
	{
		Rational q(-1, 1);
		Assert(q.Numerator() == -1 && q.Denominator() == 1, "-1/1");
	}
	{
		Rational q((int)1.2, (int)1.5);
		Assert(q.Numerator() == 1 && q.Denominator() == 1, "1.2/1.5");
	}
	{
		Rational q(1, -1);
		Assert(q.Numerator() == -1 && q.Denominator() == 1, "1/-1");
	}
	{
		Rational q(-1, -1);
		Assert(q.Numerator() == 1 && q.Denominator() == 1, "-1/-1");
	}
	{
		Rational q(2147483647, 1);
		Assert(q.Numerator() == 2147483647 && q.Denominator() == 1, "2147483647/1");
	}
	{
		Rational q(1, 2147483647);
		Assert(q.Numerator() == 1 && q.Denominator() == 2147483647, "1/2147483647");
	}
	{
		Rational q(-2147483648, 1);
		Assert(q.Numerator() == -2147483648 && q.Denominator() == 1, "-2147483648/1");
	}
	{
		Rational q(1, -2147483647);
		Assert(q.Numerator() == -1 && q.Denominator() == 2147483647, "1/-2147483647");
	}
}

void TestDel()
{
	{
		Rational q;
		Assert(q.Numerator() == 0 && q.Denominator() == 1, "0/1");
	}
	{
		Rational q(0, 4);
		Assert(q.Numerator() == 0 && q.Denominator() == 1, "0/4");
	}
	{
		Rational q(2, 4);
		Assert(q.Numerator() == 1 && q.Denominator() == 2, "2/4");
	}
	{
		Rational q(-2, 4);
		Assert(q.Numerator() == -1 && q.Denominator() == 2, "-2/4");
	}
	{
		Rational q(2, -4);
		Assert(q.Numerator() == -1 && q.Denominator() == 2, "2/-4");
	}
	{
		Rational q(-2, -4);
		Assert(q.Numerator() == 1 && q.Denominator() == 2, "-2/-4");
	}

	{
		Rational q(4, 2);
		Assert(q.Numerator() == 2 && q.Denominator() == 1, "4/2");
	}
	{
		Rational q(-4, 2);
		Assert(q.Numerator() == -2 && q.Denominator() == 1, "-4/2");
	}
	{
		Rational q(4, -2);
		Assert(q.Numerator() == -2 && q.Denominator() == 1, "4/-2");
	}
	{
		Rational q(-4, -2);
		Assert(q.Numerator() == 2 && q.Denominator() == 1, "-4/-2");
	}

	{
		Rational q(24, 21);
		Assert(q.Numerator() == 8 && q.Denominator() == 7, "24/21");
	}
	{
		Rational q(-24, 21);
		Assert(q.Numerator() == -8 && q.Denominator() == 7, "-24/21");
	}
	{
		Rational q(24, -21);
		Assert(q.Numerator() == -8 && q.Denominator() == 7, "24/-21");
	}
	{
		Rational q(-24, -21);
		Assert(q.Numerator() == 8 && q.Denominator() == 7, "-24/-21");
	}
}

int main()
{
	TestRunner runner;
	runner.RunTest(TestAdd, "TestAdd");
	runner.RunTest(TestDel, "TestDel");
	// добавьте сюда свои тесты
	return 0;
}
