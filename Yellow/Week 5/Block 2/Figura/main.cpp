#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <memory>
#include <cmath>

using namespace std;

class Figure
{
public:
	Figure(const string &type = "FIGURE") : _type(type) {}
	virtual ~Figure() = default;
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;

protected:
	const string _type;
};

class Triangle : public Figure
{
public:
	Triangle(const string &type, const double &a, const double &b, const double &c) : Figure(type), _p((a + b + c) / 2)
	{
		_a = a;
		_b = b;
		_c = c;
	}
	string Name() const override
	{
		return _type;
	}
	double Perimeter() const override
	{
		return _a + _b + _c;
	}
	double Area() const override
	{
		return sqrt(_p * (_p - _a) * (_p - _b) * (_p - _c));
	}

private:
	double _a;
	double _b;
	double _c;
	const double _p;
};

class Rect : public Figure
{
public:
	Rect(const string &type, const double &w, const double &h) : Figure(type)
	{
		_h = h;
		_w = w;
	}
	string Name() const override
	{
		return _type;
	}
	double Perimeter() const override
	{
		return (_h + _w) * 2;
	}
	double Area() const override
	{
		return _w * _h;
	}

private:
	double _h;
	double _w;
};

class Circle : public Figure
{
public:
	Circle(const string &type, const double &r) : Figure(type)
	{
		_r = r;
	}
	string Name() const override
	{
		return _type;
	}
	double Perimeter() const override
	{
		return 2 * PI * _r;
	}
	double Area() const override
	{
		return PI * _r * _r;
	}

private:
	const double PI = 3.14;
	double _r;
};

shared_ptr<Figure> CreateFigure(istream &is)
{
	string type;

	is >> type;
	if (type == "TRIANGLE")
	{
		double a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(type, a, b, c);
	}
	else if (type == "RECT")
	{
		double w, h;
		is >> w >> h;
		return make_shared<Rect>(type, w, h);
	}
	else if (type == "CIRCLE")
	{
		double r;
		is >> r;
		return make_shared<Circle>(type, r);
	}
	return NULL;
	// return make_shared<Figure>("Fig");
}

int main()
{
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line);)
	{
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD")
		{
			is >> ws;
			figures.push_back(CreateFigure(is));
		}
		else if (command == "PRINT")
		{
			for (const auto &current_figure : figures)
			{
				cout << fixed << setprecision(3)
					 << current_figure->Name() << " "
					 << current_figure->Perimeter() << " "
					 << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}