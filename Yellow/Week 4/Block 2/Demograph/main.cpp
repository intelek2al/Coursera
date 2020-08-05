#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

enum class Gender
{
	FEMALE,
	MALE
};

struct Person
{
	int age;		  // возраст
	Gender gender;	  // пол
	bool is_employed; // имеет ли работу
};

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end)
{
	if (range_begin == range_end)
	{
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
		begin(range_copy), middle, end(range_copy),
		[](const Person &lhs, const Person &rhs) {
			return lhs.age < rhs.age;
		});
	return middle->age;
}

void PrintStats(vector<Person> persons)
{
	cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;
	sort(persons.begin(), persons.end(), [](const Person &a, const Person &b) { return a.gender < b.gender; });
	auto itM = find_if(persons.begin(), persons.end(), [](const Person &p) { return p.gender == Gender::MALE; });
	sort(persons.begin(), itM, [](const Person &a, const Person &b) { return a.is_employed && !b.is_employed; });
	sort(itM, persons.end(), [](const Person &a, const Person &b) { return a.is_employed && !b.is_employed; });
	cout << "Median age for females = " << ComputeMedianAge(persons.begin(), itM) << endl;
	cout << "Median age for males = " << ComputeMedianAge(itM, persons.end()) << endl;
	auto it_fu = find_if(persons.begin(), itM, [](const Person &p) { return !p.is_employed; });
	auto it_mu = find_if(itM, persons.end(), [](const Person &p) { return !p.is_employed; });
	cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), it_fu) << endl;
	cout << "Median age for unemployed females = " << ComputeMedianAge(it_fu, itM) << endl;
	cout << "Median age for employed males = " << ComputeMedianAge(itM, it_mu) << endl;
	cout << "Median age for unemployed males = " << ComputeMedianAge(it_mu, persons.end()) << endl;
}

int main()
{
	vector<Person> persons = {
		{31, Gender::MALE, false},
		{24, Gender::MALE, true},
		{40, Gender::FEMALE, true},
		{20, Gender::FEMALE, true},
		{80, Gender::FEMALE, false},
		{78, Gender::MALE, false},
		{10, Gender::FEMALE, false},
		{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}