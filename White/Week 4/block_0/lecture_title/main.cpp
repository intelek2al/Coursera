#include <iostream>

using namespace std;

struct Specialization {
	string value;

	explicit Specialization(string new_val) {
		value = new_val;
	}
};

struct Course {
	string value;

	explicit Course(string new_val) {
		value = new_val;
	}	
};

struct Week {
	string value;

	explicit Week(string new_val) {
		value = new_val;
	}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;

	LectureTitle(Specialization sp, Course cr, Week wk) {
		specialization = sp.value;
		course = cr.value;
		week = wk.value;
	}
};

int main() {
	LectureTitle title(Specialization("C++"), Course("White belt"), Week("4th"));
}