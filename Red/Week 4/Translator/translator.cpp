#include "test_runner.h"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class Translator {
public:
	Translator() = default;
	void Add(string_view source, string_view target) {
		s_t[source] = SavedString(target);
		t_s[target] = source;
	}
	string_view TranslateForward(string_view source) const {
		return s_t.at(source);
	}
	string_view TranslateBackward(string_view target) const {
		return t_s.at(target);
	}

private:
	string_view SavedString(string_view word) {
		
	}
	map<string_view, string_view> s_t;
	map<string_view, string_view> t_s;
	deque<string> dict;
};

void TestSimple() {
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	return 0;
}
