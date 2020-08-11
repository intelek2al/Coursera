#include "test_runner.h"
#include <string>
#include <vector>
#include <deque>

using namespace std;

class Translator
{
public:
	void Add(string_view source, string_view target)
	{
		auto saved_source = SavedString(source);
		auto saved_target = SavedString(target);
		s_t[saved_source] = saved_target;
		t_s[saved_target] = saved_source;
	}

	string_view TranslateForward(string_view source) const
	{
		return GetWordFromDict(s_t, source);
	}
	string_view TranslateBackward(string_view target) const
	{
		return GetWordFromDict(t_s, target);
	}

private:
	string_view GetWordFromDict(const map<string_view, string_view> &dict, string_view word) const
	{
		auto it = dict.find(word);
		if (it != dict.end())
		{
			return it->second;
		}
		else
			return {};
	}
	string_view SavedString(string_view word)
	{
		for (auto *dt : {&s_t, &t_s})
		{
			auto it = dt->find(word);
			if (it != dt->end())
			{
				return it->first;
			}
		}
		return all_dict.emplace_back(word);
	}

	map<string_view, string_view> s_t;
	map<string_view, string_view> t_s;
	deque<string> all_dict;
};

void TestSimple()
{
	Translator translator;
	translator.Add(string("okno"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

void TestSimp()
{
	Translator translator;
	translator.Add(string("privet"), string("window"));
	translator.Add(string("stol"), string("table"));

	ASSERT_EQUAL(translator.TranslateForward("privet"), "window");
	ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
	ASSERT_EQUAL(translator.TranslateBackward("privet"), "");
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestSimple);
	RUN_TEST(tr, TestSimp);
	return 0;
}
