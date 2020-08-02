#include <iostream>
#include <numeric>
#include <sstream>
#include <string.h>
#include <map>
#include <set>
#include <vector>
#include <exception>

using namespace std;

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
		if (denominator == 0) {
			throw invalid_argument("Denominator is " + to_string(denominator));
		}
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
	if (b.Numerator() == 0) {
		throw domain_error("Dev By Zero");
	}
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

int main()
{
	try
	{
		Rational r(1, 0);
		cout << "Doesn't throw in case of zero denominator" << endl;
		return 1;
	}
	catch (invalid_argument &)
	{
	}

	try
	{
		auto x = Rational(1, 2) / Rational(0, 1);
		x = Rational();
		cout << "Doesn't throw in case of division by zero" << endl;
		return 2;
	}
	catch (domain_error &)
	{
	}

	cout << "OK" << endl;
	return 0;
}
