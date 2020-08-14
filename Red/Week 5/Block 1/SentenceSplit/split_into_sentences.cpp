#include "test_runner.h"

#include <vector>
#include <algorithm>

using namespace std;

// Объявляем Sentence<Token> для произвольного типа Token
// синонимом vector<Token>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор предложений — vector<Sentence<Token>>.
template <typename Token>
using Sentence = vector<Token>;

// Класс Token имеет метод bool IsEndSentencePunctuation() const

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
{
	vector<Sentence<Token>> group;
	auto it = tokens.begin();
	while (it != tokens.end())
	{
		auto next_it = find_if(it, tokens.end(), [](auto &iter) { return (iter).IsEndSentencePunctuation(); });
		next_it = find_if(next_it, tokens.end(), [](auto &iter) { return !(iter).IsEndSentencePunctuation(); });
		Sentence<Token> tmp;
		move(it, next_it, back_inserter(tmp));
		group.push_back(move(tmp));

		it = next_it;
	}
	return group;
}

struct TestToken
{
	string data;
	bool is_end_sentence_punctuation = false;

	bool IsEndSentencePunctuation() const
	{
		return is_end_sentence_punctuation;
	}
	bool operator==(const TestToken &other) const
	{
		return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
	}
};

ostream &operator<<(ostream &stream, const TestToken &token)
{
	return stream << token.data;
}

// Тест содержит копирования объектов класса TestToken.
// Для проверки отсутствия копирований в функции SplitIntoSentences
// необходимо написать отдельный тест.
void TestSplitting()
{
	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
		vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!"}}}));

	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
		vector<Sentence<TestToken>>({{{"Split"}, {"into"}, {"sentences"}, {"!", true}}}));

	ASSERT_EQUAL(
		SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
		vector<Sentence<TestToken>>({
			{{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
			{{"Without"}, {"copies"}, {".", true}},
		}));
}

int main()
{
	TestRunner tr;
	RUN_TEST(tr, TestSplitting);
	return 0;
}

// Compile error : b "In file included from /usr/include/c++/7/bits/stl_algobase.h:71:0,
// 				from /
// 				usr / include / c++ / 7 / bits / char_traits.h : 39,
// 	from / usr / include / c++ / 7 / ios : 40,
// 	from / usr / include / c++ / 7 / istream : 38,
// 	from / usr / include / c++ / 7 / sstream : 38,
// 	from include / test_runner.h : 3,
// 	from / tmp / submissionw3omf3_j / split_into_sentences.cpp : 1 : / usr / include / c++ / 7 / bits / predefined_ops.h : In instantiation of 'bool __gnu_cxx::__ops::_Iter_pred<_Predicate>::operator()(_Iterator) [with _Iterator = __gnu_cxx::__normal_iterator<NonCopyableToken<std::__cxx11::basic_string<char> >*, std::vector<NonCopyableToken<std::__cxx11::basic_string<char> > > >; _Predicate = SplitIntoSentences(std::vector<T>) [with Token = NonCopyableToken<std::__cxx11::basic_string<char> >]::<lambda(auto:1)>]' : / usr / include / c++ / 7 / bits / stl_algo.h : 120 : 14 : required from '_RandomAccessIterator std::__find_if(_RandomAccessIterator, _RandomAccessIterator, _Predicate, std::random_access_iterator_tag) [with _RandomAccessIterator = __gnu_cxx::__normal_iterator<NonCopyableToken<std::__cxx11::basic_string<char> >*, std::vector<NonCopyableToken<std::__cxx11::basic_string<char> > > >; _Predicate = __gnu_cxx::__ops::_Iter_pred<SplitIntoSentences(std::vector<T>) [with Token = NonCopyableToken<std::__cxx11::basic_string<char> >]::<lambda(auto:1)> >]' / usr / include / c++ / 7 / bits / stl_algo.h : 161 : 23 : required from '_Iterator std::__find_if(_Iterator, _Iterator, _Predicate) [with _Iterator = __gnu_cxx::__normal_iterator<NonCopyableToken<std::__cxx11::basic_string<char> >*, std::vector<NonCopyableToken<std::__cxx11::basic_string<char> > > >; _Predicate = __gnu_cxx::__ops::_Iter_pred<SplitIntoSentences(std::vector<T>) [with Token = NonCopyableToken<std::__cxx11::basic_string<char> >]::<lambda(auto:1)> >]' / usr / include / c++ / 7 / bits / stl_algo.h : 3932 : 28 : required from '_IIter std::find_if(_IIter, _IIter, _Predicate) [with _IIter = __gnu_cxx::__normal_iterator<NonCopyableToken<std::__cxx11::basic_string<char> >*, std::vector<NonCopyableToken<std::__cxx11::basic_string<char> > > >; _Predicate = SplitIntoSentences(std::vector<T>) [with Token = NonCopyableToken<std::__cxx11::basic_string<char> >]::<lambda(auto:1)>]' / tmp / submissionw3omf3_j / split_into_sentences.cpp : 25 : 25 : required from 'std::vector<std::vector<T> > SplitIntoSentences(std::vector<T>) [with Token = NonCopyableToken<std::__cxx11::basic_string<char> >]' / tmp / submissionw3omf3_j / split_into_sentences.cpp : 133 : 40 : required from 'void GetAndPrintAnswer(std::vector<T>, bool) [with Token = NonCopyableToken<std::__cxx11::basic_string<char> >]' / tmp / submissionw3omf3_j / split_into_sentences.cpp : 201 : 49 : required from here / usr / include / c++ / 7 / bits / predefined_ops.h : 283 : 11 : error : use of deleted function 'NonCopyableToken<Text>::NonCopyableToken(const NonCopyableToken<Text>&) [with Text = std::__cxx11::basic_string<char>]'
// {
// 	return bool(_M_pred(*__it));
// }
// ^~~~~~~~~~~~~~~~~~~~compilation terminated due to - Wfatal - errors."
