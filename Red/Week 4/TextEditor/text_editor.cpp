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
	template <typename Iterator>
	auto MoveIter(Iterator it, int steps)
	{
		if (steps < 0)
		{
			steps = -steps;
			for (int i = 0; i < steps && it != text.begin(); i++)
				it--;
		}
		else if (steps > 0)
		{
			for (int i = 0; i < steps && it != text.end(); i++)
				it++;
		}
		return it;
	}

public:
	Editor()
	{
		cursor = text.begin();
	}
	void PrintType()
	{
		string t(text.begin(), text.end());
		t.insert(distance(text.begin(), cursor), "|");
		cout << t << endl;
	}
	void Left()
	{
		Decr(cursor);
		// PrintType();
	}
	void Right()
	{
		Incr(cursor);
		// PrintType();
	}

	void Insert(char token)
	{
		text.insert(cursor, token);
		if (cursor == text.end())
			Incr(cursor);
		// PrintType();
	}
	auto _Copy(size_t tokens = 1)
	{
		tokens = min(tokens, static_cast<size_t>(distance(cursor, text.end())));
		auto iter_end = MoveIter(cursor, tokens);
		buffer.assign(cursor, iter_end);
		return iter_end;
		// cout << "-------------------------" << endl
		// 	 << "Copied: " << buffer << "$" << endl
		// 	 << "Text now: " << text << "$" << endl
		// 	 << "Cursor now in: " << cursor << endl
		// 	 << "-------------------------" << endl;
	}
	void Cut(size_t tokens = 1)
	{

		// string left = text.substr(0, cursor);
		tokens = min(tokens, static_cast<size_t>(distance(cursor, text.end())));
		auto iter_end = _Copy(tokens);
		text.erase(cursor, iter_end);
		cursor = iter_end;
		// {
		// 	cout << "-------------------------" << endl
		// 		 << "Cuted: " << string(buffer.begin(), buffer.end()) << "$" << endl
		// 		 << "Text now: " << string(buffer.begin(), buffer.end()) << "$" << endl
		// 		 << "Cursor now in: " << distance(text.begin(), cursor) << " > " << *cursor << endl
		// 		 << "-------------------------" << endl;
		// }
	}

	void Copy(size_t tokens = 1)
	{
		tokens = min(tokens, static_cast<size_t>(distance(cursor, text.end())));
		auto iter_end = MoveIter(cursor, tokens);
		buffer.assign(cursor, iter_end);
		// {

		// 	cout << "-------------------------" << endl
		// 		 << "Copied: " << string(buffer.begin(), buffer.end()) << "$" << endl
		// 		 << "Text now: " << string(buffer.begin(), buffer.end()) << "$" << endl
		// 		 << "Cursor now in: " << distance(text.begin(), cursor) << endl
		// 		 << "-------------------------" << endl;
		// }
	}
	void Paste()
	{
		if (buffer.size() == 0)
			return;

		text.insert(cursor, buffer.begin(), buffer.end());
		// cout << "-------------------------" << endl
		// 	 << "After paste: " << text << "$" << endl;
		// cursor = MoveIter(cursor, buffer.size());
		// cout << "Cursor now in: " << cursor << endl
		// 	 << "-------------------------" << endl;
		// PrintType();
	}
	string GetText() const
	{
		string res(text.begin(), text.end());
		return res;
	}

private:
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
	list<char> buffer;
	list<char>::iterator cursor = text.begin();
};

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

void TestCut()
{
	Editor editor;
	//1
	editor.Cut(10);
	editor.Insert('a');
	editor.Left();
	//2
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	//3
	editor.Cut(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "a");
	TypeText(editor, "bcde");
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcde");
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	//5
	editor.Cut(5);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	//6
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bcde");
	editor.Right();
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "bde");
	editor.Cut(1);
	editor.Cut(1);
	ASSERT_EQUAL(editor.GetText(), "b");
}
void TestCopy()
{
	Editor editor;
	editor.Copy(10);
	editor.Insert('a');
	editor.Paste();
	editor.Left();
	ASSERT_EQUAL(editor.GetText(), "a");
	editor.Copy(1);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa"); //between a
	editor.Copy(0);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "aa");
	TypeText(editor, "bcde");
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	editor.Left();
	//4
	editor.Cut(10);
	ASSERT_EQUAL(editor.GetText(), "");
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "abcdea");
}
void TestCopyPasteLastChars()
{
	Editor editor;
	TypeText(editor, "happy birthday");
	editor.Left();
	editor.Left();
	editor.Copy(5);
	editor.Paste();
	ASSERT_EQUAL(editor.GetText(), "happy birthdayay");
}

int main()
{
	TestRunner tr;
	// Editor editor;

	// TypeText(editor, "Hello");
	// editor.Left();
	// editor.Left();
	// editor.Left();
	// editor.Copy(2);
	// editor.Left();
	// editor.Left();
	// editor.Paste();
	// Print(editor);
	// cout << editor.GetText() << endl;
	RUN_TEST(tr, TestEditing);
	RUN_TEST(tr, TestReverse);
	RUN_TEST(tr, TestNoText);
	RUN_TEST(tr, TestEmptyBuffer);
	RUN_TEST(tr, TestCut);
	RUN_TEST(tr, TestCopy);
	RUN_TEST(tr, TestCopyPasteLastChars);
	return 0;
}