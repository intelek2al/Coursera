#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class Deque
{
public:
	Deque() = default;
	~Deque()
	{
		front.clear();
		back.clear();
	}
	bool Empty() const
	{
		return front.empty() && back.empty();
	}
	size_t Size() const
	{
		return front.size() + back.size();
	}

	T &operator[](size_t index)
	{
		return At(index);
	}
	const T &operator[](size_t index) const
	{
		// const auto el = ;
		return At(index);
	}

	T &At(size_t index)
	{
		if (index < front.size())
		{
			return *(front.rbegin() + index);
		}
		else if ((index -= front.size()) < back.size())
		{
			return *(back.begin() + index);
		}
		else
			throw out_of_range("invalid index");
	}
	const T &At(size_t index) const
	{
		if (index < front.size())
		{
			return *(front.rbegin() + index);
		}
		else if ((index -= front.size()) < back.size())
		{
			return *(back.begin() + index);
		}
		else
			throw out_of_range("invalid index");
	}
	const T &Front() const
	{
		if (!front.empty())
			return *(front.rbegin());
		return back.front();
	}
	const T &Back() const
	{
		if (!back.empty())
			return back.back();
		return front.front();
	}
	T &Front()
	{
		if (!front.empty())
			return *(front.rbegin());
		return back.front();
	}
	T &Back()
	{
		if (!back.empty())
			return back.back();
		return front.front();
	}
	void PushBack(const T &data)
	{
		back.push_back(data);
	}

	void PushFront(const T &data)
	{
		front.push_back(data);
	}

private:
	vector<T> front;
	vector<T> back;
};

// int main()
// {
// 	{
// 		Deque<int> v;
// 		v.PushBack(2);
// 		v.PushBack(3);
// 		v.PushBack(4);
// 		v.PushBack(5);
// 		v.PushBack(6);
// 		v.PushBack(7);

// 		v.PushFront(1);
// 		v.PushFront(0);

// 		cout << v.Back() << endl;

// 		for (size_t i = 0; i < v.Size(); i++)
// 		{
// 			cout << v[i] << ' ';
// 		}
// 		cout << endl;
// 	}
// 	{
// 		Deque<int> deque;
// 		deque.PushBack(5);
// 		deque[0] = 2;
// 		deque.Front() = 1;
// 		std::cout << deque[0] << endl;
// 		deque.PushBack(3);
// 		deque.PushBack(2);
// 		deque.Back() = 22;
// 		cout << deque.Back() << endl;
// 		//        cout << deque.Front() << endl;
// 	}
// 	{
// 		cout << "test 2 _______" << '\n';
// 		Deque<int> d1;
// 		d1.PushFront(2);
// 		d1.PushFront(1);
// 		d1.PushBack(3);
// 		d1.PushBack(4);
// 		cout << d1[2] << endl;
// 		cout << d1.Back() << endl;
// 		cout << d1.Front() << endl;
// 	}

// 	{
// 		cout << "test 2 answer _______" << '\n';
// 		deque<int> d2;
// 		d2.push_front(2);
// 		d2.push_front(1);
// 		d2.push_back(3);
// 		d2.push_back(4);
// 		cout << d2[2] << endl;
// 		cout << d2.back() << endl;
// 		cout << d2.front() << endl;
// 	}

// 	return 0;
// }
