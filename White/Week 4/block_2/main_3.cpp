#include <iostream>
#include <numeric>
#include <sstream>
#include <string.h>

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

int main()
{
	{
		ostringstream output;
		output << Rational(-6, 8);
		if (output.str() != "-3/4")
		{
			cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
			return 1;
		}
	}

	{
		istringstream input("5/7");
		Rational r;
		input >> r;
		bool equal = r == Rational(5, 7);
		if (!equal)
		{
			cout << "5/7 is incorrectly read as " << r << endl;
			return 2;
		}
	}

	{
		istringstream input("5/7 10/8");
		Rational r1, r2;
		input >> r1 >> r2;
		bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct)
		{
			cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
			return 3;
		}

		input >> r1;
		input >> r2;
		correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
		if (!correct)
		{
			cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
			return 4;
		}
	}
	{
		istringstream input("5/f 6/4");
		Rational r1, r2;
		input >> r1 >> r2;
		printf("r1 %d/%d, r2 %d/%d\n", r1.Numerator(), r1.Denominator(), r2.Numerator(), r2.Denominator());
		bool equal1 = r1 == Rational(0, 1);
		bool equal2 = r2 == Rational(3, 2);
		if (!equal1 || !equal2)
		{
			cout << "read:\n"
				 << r1 << '\n'
				 << r2;
			return 1;
		}
	}

	cout << "OK" << endl;
	return 0;
}
