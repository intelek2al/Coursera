#include <iostream>

using namespace std;

long long unsigned ReadV()
{
	long long unsigned mult = 1;

	for (size_t i = 0; i < 3; i++)
	{
		unsigned tmp;
		cin >> tmp;
		mult *= tmp;
	}
	return mult;
}

int main()
{
	size_t c_blocks;
	unsigned ro;
	long long unsigned sum = 0;

	cin >> c_blocks >> ro;
	for (size_t i = 0; i < c_blocks; i++)
	{
		sum += ReadV() * ro;
	}
	cout << sum;
	return 0;
}