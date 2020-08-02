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
		if (denominator == 0)
		{
			throw invalid_argument("Invalid argument");
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
	if (b.Numerator() == 0)
	{
		throw domain_error("Division by zero");
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
	int n, d;
	char c;

	if (stream)
	{
		stream >> n >> c >> d;
		if (stream && c == '/')
		{
			a = Rational(n, d);
		}
	}

	return stream;
}

bool operator<(const Rational &a, const Rational &b)
{
	int den = lcm(a.Denominator(), b.Denominator());
	int num1 = a.Numerator() * den / a.Denominator();
	int num2 = b.Numerator() * den / b.Denominator();

	return num1 < num2;
}

class Calculator
{
private:
	Rational left;
	Rational right;
	char oper;

public:
	Calculator()
	{
		left = Rational();
		right = Rational();
		oper = '+';
	}
	Calculator(const Rational &l, const Rational &r, const char &o)
	{
		left = l;
		right = r;
		oper = o;
	}
	Rational Accept()
	{
		switch (oper)
		{
		case '+':
			return (left + right);
		case '-':
			return (left - right);
		case '*':
			return (left * right);
		case '/':
			return (left / right);
		}
		return Rational();
	}
};

istream &operator>>(istream &stream, Calculator &calc)
{
	Rational t_left = Rational();
	Rational t_right = Rational();
	char t_oper = '+';

	stream >> t_left >> t_oper >> t_right;
	calc = Calculator(t_left, t_right, t_oper);
	return stream;
}

int main()
{
	Calculator calc;

	try
	{
		cin >> calc;
		cout << calc.Accept() << endl;
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}
