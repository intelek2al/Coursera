#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main()
{
	int n;

	cin >> n;
	vector<int> v(n);
	iota(v.rbegin(), v.rend(), 1);
	do
	{
		for (const auto &l : v)
			cout << l << ' ';
		cout << endl;
	} while (prev_permutation(v.begin(), v.end()));
}