#include <iostream>
#include <numeric>

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

Rational operator+(Rational a, Rational b)
{
	int den = lcm(a.Denominator(), b.Denominator());
	int num = a.Numerator() * den / a.Denominator() + b.Numerator() * den / b.Denominator();

	return Rational(num, den);
}

Rational operator-(Rational a, Rational b)
{
	int den = lcm(a.Denominator(), b.Denominator());
	int num = a.Numerator() * den / a.Denominator() - b.Numerator() * den / b.Denominator();

	return Rational(num, den);
}

bool operator==(Rational a, Rational b)
{
	return (a.Denominator() == b.Denominator() && a.Numerator() == b.Numerator());
}

Rational operator*(Rational a, Rational b)
{
	return Rational(a.Numerator() * b.Numerator(), a.Denominator() * b.Denominator());
}

Rational operator/(Rational a, Rational b)
{
	return Rational(a.Numerator() * b.Denominator(), a.Denominator() * b.Numerator());
}

int main()
{
	{
		Rational a(2, 3);
		Rational b(4, 3);
		Rational c = a * b;
		bool equal = c == Rational(8, 9);
		if (!equal)
		{
			cout << "2/3 * 4/3 != 8/9" << endl;
			return 1;
		}
	}

	{
		Rational a(5, 4);
		Rational b(15, 8);
		Rational c = a / b;
		bool equal = c == Rational(2, 3);
		if (!equal)
		{
			cout << "5/4 / 15/8 != 2/3" << endl;
			return 2;
		}
	}

	cout << "OK" << endl;
	return 0;
}
