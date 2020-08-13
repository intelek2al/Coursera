#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
#include <list>
#include <deque>
#include "test_runner.h"

using namespace std;

class Editor
{
public:
	Editor()
	{
		text = "";
		cursor = 0;
		cursor = 0;
		PrintType();
	}
	void PrintType()
	{
		string t(text.begin(), text.end());
		t.insert(cursor, "|");
	}
	void Left()
	{
		Decr(cursor);
		PrintType();
	}
	void Right()
	{
		Incr(cursor);
		// PrintType();
	}

	void Insert(char token)
	{
		// text_view = text;
		// string_view left = text_view.substr(0, cursor);
		// string_view right = text_view.substr(cursor, text_view.size());
		// text =

		text.insert(cursor, token);
		Incr(cursor);
	}
	void Cut(size_t tokens = 1)
	{

		// string left = text.substr(0, cursor);
		tokens = min(tokens, static_cast<size_t>(distance(cursor, text.end())));
		buffer = tokens > 0 ? SubStrList(cursor, text.end(), tokens) : make_pair(text.end(), text.end());
		// string right = (cursor + tokens < text.size()) ? ) : "";

		text = left + right;
		// cout << "-------------------------" << endl
		// 	 << "Cuted: " << buffer << "$" << endl
		// 	 << "Text now: " << text << "$" << endl
		// 	 << "Cursor now in: " << cursor << endl
		// 	 << "-------------------------" << endl;
	}
	void Copy(size_t tokens = 1)
	{
		tokens = min(tokens, static_cast<size_t>(distance(cursor, text.end())));
		buffer = tokens > 0 ? SubStrList(cursor, text.end(), tokens) : {};
		// cout << "-------------------------" << endl
		// 	 << "Copied: " << buffer << "$" << endl
		// 	 << "Text now: " << text << "$" << endl
		// 	 << "Cursor now in: " << cursor << endl
		// 	 << "-------------------------" << endl;
	}
	void Paste()
	{
		if (buffer.size() != 0)
			return;
		text.insert(cursor, buffer.first, buffer.second);
		// cout << "-------------------------" << endl
		// 	 << "After paste: " << text << "$" << endl;
		cursor = cursor + buffer.size();
		// cout << "Cursor now in: " << cursor << endl
		// 	 << "-------------------------" << endl;
	}
	string GetText() const
	{
		string res(text.begin(), text.end());
		return res;
	}

private:
	template <typename Iterator>
	pair<Iterator, Iterator> SubStrList(Iterator begin, Iterator end, size_t size)
	{
		// list<char> new_list;
		// auto = begin;
		// for (size_t i = 0; i < size; i++)
		// {
		// 	new_list.emplace_back(*it);
		// 	if (it != end)
		// 		break;
		// 	it++;
		// }
		return {begin, distance(begin, end) > size ? begin + size : end};
	}

	void Incr(list<char>::iterator &el)
	{
		if (el != text.end())
			el++;
	}
	void Decr(list<char>::iterator &el)
	{
		if (el != text.begin())
			el--;
	}
	list<char> text;
	pair<list<char>::iterator, list<char>::iterator> buffer;
	list<char>::iterator cursor = text.begin();
};

// class Editor
// {
// public:
// 	// Реализуйте конструктор по умолчанию и объявленные методы
// 	Editor()
// 	{
// 		text = "";
// 		cursor = 0;
// 		cursor = 0;
// 		PrintType();
// 	}
// 	void PrintType()
// 	{
// 		string t = text;
// 		t.insert(cursor, "|");
// 	}
// 	void Left()
// 	{
// 		Decr(cursor);
// 		PrintType();
// 	}
// 	void Right()
// 	{
// 		Incr(cursor);
// 		// PrintType();
// 	}

// 	void Insert(char token)
// 	{
// 		// text_view = text;
// 		// string_view left = text_view.substr(0, cursor);
// 		// string_view right = text_view.substr(cursor, text_view.size());
// 		// text =

// 		text.insert(cursor, {token});
// 		Incr(cursor);
// 	}
// 	void Cut(size_t tokens = 1)
// 	{

// 		string left = text.substr(0, cursor);
// 		tokens = min(tokens, text.size() - cursor);
// 		buffer = tokens > 0 ? text.substr(cursor, tokens) : "";
// 		string right = (cursor + tokens < text.size()) ? text.substr(cursor + tokens, text.size()) : "";

// 		text = left + right;
// 		// cout << "-------------------------" << endl
// 		// 	 << "Cuted: " << buffer << "$" << endl
// 		// 	 << "Text now: " << text << "$" << endl
// 		// 	 << "Cursor now in: " << cursor << endl
// 		// 	 << "-------------------------" << endl;
// 	}
// 	void Copy(size_t tokens = 1)
// 	{
// 		tokens = min(tokens, text.size() - cursor);
// 		buffer = tokens > 0 ? text.substr(cursor, tokens) : "";
// 		// cout << "-------------------------" << endl
// 		// 	 << "Copied: " << buffer << "$" << endl
// 		// 	 << "Text now: " << text << "$" << endl
// 		// 	 << "Cursor now in: " << cursor << endl
// 		// 	 << "-------------------------" << endl;
// 	}
// 	void Paste()
// 	{
// 		if (buffer == "")
// 			return;
// 		text.insert(cursor, buffer);
// 		// cout << "-------------------------" << endl
// 		// 	 << "After paste: " << text << "$" << endl;
// 		cursor += buffer.size();
// 		// cout << "Cursor now in: " << cursor << endl
// 		// 	 << "-------------------------" << endl;
// 	}
// 	string GetText() const
// 	{
// 		return text;
// 	}

// private:
// 	void Incr(int &el)
// 	{
// 		if (el <= text.size())
// 			el++;
// 	}
// 	void Decr(int &el)
// 	{
// 		if (el != 0)
// 			el--;
// 	}
// 	string text = "";
// 	string buffer = "";
// 	int cursor = 0;
// };

void Print(Editor &editor)
{
	cout << editor.GetText() << "$" << endl;
}

void TypeText(Editor &editor, const string &text)
{
	for (char c : text)
	{
		editor.Insert(c);
	}
}

void TestEditing()
{
	{
		Editor editor;

		const size_t text_len = 12;
		const size_t first_part_len = 7;
		TypeText(editor, "hello, world");
		for (size_t i = 0; i < text_len; ++i)
		{
			editor.Left();
		}
		editor.Cut(first_part_len);
		for (size_t i = 0; i < text_len - first_part_len; ++i)
		{
			editor.Right();
		}
		TypeText(editor, ", ");
		editor.Paste();
		editor.Left();
		editor.Left();
		editor.Cut(3);

		ASSERT_EQUAL(editor.GetText(), "world, hello");
	}
	{
		Editor editor;

		TypeText(editor, "misprnit");
		editor.Left();
		editor.Left();
		editor.Left();
		editor.Cut(1);
		editor.Right();
		editor.Paste();

		ASSERT_EQUAL(editor.GetText(), "misprint");
	}
}

void TestReverse()
{
	Editor editor;

	const string text = "esreveR";
	for (char c : text)
	{
		editor.Insert(c);
		editor.Left();
	}

	ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText()
{
	Editor editor;
	ASSERT_EQUAL(editor.GetText(), "");

	editor.Left();
	editor.Left();
	editor.Right();
	editor.Right();
	editor.Copy(0);
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer()
{
	Editor editor;

	editor.Paste();
	TypeText(editor, "example");
	editor.Left();
	editor.Left();
	editor.Paste();
	editor.Right();
	editor.Paste();
	editor.Copy(0);
	editor.Paste();
	editor.Left();
	editor.Cut(0);
	editor.Paste();

	ASSERT_EQUAL(editor.GetText(), "example");
}

int main()
{
	TestRunner tr;
	// Editor editor;

	// TypeText(editor, "Hello");
	// editor.Left();
	// editor.Left();
	// editor.Left();
	// editor.Cut(2);
	// editor.Left();
	// editor.Left();
	// editor.Paste();
	// cout << editor.GetText() << endl;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	return 0;
}