#include <iostream>
#include <vector>

using namespace std;

struct Date
{
	long long int day;
	long long int mounth;
	long long int year;
};

class Student {
	public:
		string get_full_name() const {
			return first_n + " " + second_n;
		}
		string get_b_day() const {
			return to_string(bth.day) + '.' + to_string(bth.mounth) + '.' + to_string(bth.year);
		}
		void set_first_n(string name) {
			first_n = name;
		}
		void set_second_n(string name) {
			second_n = name;
		}
		void set_b_day(Date date) {
			bth = date;
		}
	private:
		Date bth;
		string first_n;
		string second_n;
};

string get_info(vector<Student> list, string type, int indx) {
	if (indx > 0 && indx <= (int)list.size()) {
		if (type == "name")
			return list[indx - 1].get_full_name();
		else if (type == "date")
			return list[indx - 1].get_b_day();
	}
	return "bad request";
}

int main() {
    int n = 0;
    vector<Student> list;

	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Student std;
		string name;
		int d, m, y;

		cin >> name;
		std.set_first_n(name);
		cin >> name;
		std.set_second_n(name);
		cin >> d;
		cin >> m;
		cin >> y;
		std.set_b_day({d, m, y});
		list.push_back(std);
	}
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		string type;
		int indx;

		cin >> type;
		cin >> indx;
		cout << get_info(list, type, indx) << endl;
	}
	
	

	return 0;
}