#include "test_runner.h"
#include "profile.h"

#include <map>
#include <string>
#include <functional>
#include <future>
#include <vector>
using namespace std;

struct Stats
{
	map<string, int> word_frequences;

	void operator+=(const Stats &other)
	{
		for (const auto &[word, count] : other.word_frequences)
		{
			word_frequences[word] += count;
		}
	}
};

Stats ExploreLine(const set<string> &key_words, const string &line)
{
	Stats stat;
	stringstream ss(line);
	while (!ss.eof())
	{
		string word;
		ss >> word;
		int counter = key_words.count(word);
		if (counter != 0)
			stat.word_frequences[word] += counter;
	}
	return stat;
}

Stats ExploreKeyWordsSingleThread(const set<string> &key_words, istream &input)
{
	Stats result;
	for (string line; getline(input, line);)
	{
		result += ExploreLine(key_words, line);
	}
	return result;
}
Stats ExploreKeyWordsMultiThread(const set<string> &key_words, istream &input)
{
	Stats result;
	vector<future<Stats>> f;
	for (string line; getline(input, line);)
	{
		f.push_back(async(ExploreLine, ref(key_words), ref(line)));
	}
	for (auto &ft : f)
	{
		result += ft.get();
	}
	return result;
}

Stats ExploreKeyWords(const set<string> &key_words, istream &input)
{
	return ExploreKeyWordsMultiThread(key_words, input);
}

void TestBasic()
{
	const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
		{"yangle", 6},
		{"rocks", 2},
		{"sucks", 1}};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

void CustomTest()
{
	const set<string> key_words = {"one", "two", "three"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
	ss << "one two three";

	const map<string, int> expected =
		{
			{"one", 1},
			{"two", 1},
			{"three", 1}};

	const auto stats = ExploreKeyWords(key_words, ss);
	ASSERT_EQUAL(stats.word_frequences, expected);
}

void CustomTest()
{
	const set<string> key_words = {"one", "two", "three"};

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";
	ss << "one two three";

	const map<string, int> expected =
		{
			{"one", 1},
			{"two", 1},
			{"three", 1}};

	const auto stats = ExploreKeyWords(key_words, ss);
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
	RUN_TEST(tr, CustomTest);
}
