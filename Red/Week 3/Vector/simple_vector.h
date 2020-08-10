#pragma once

#include <algorithm>
#include <cstdlib>

using namespace std;

template <typename T>
class SimpleVector
{
public:
	SimpleVector()
	{
		start = nullptr;
		finish = nullptr;
		size = 0;
		capacity = 0;
	}
	explicit SimpleVector(size_t size)
	{
		this->size = capacity = size;
		start = new T[size];
		finish = start + size;
	}
	~SimpleVector()
	{
		if (capacity == 1)
			delete start;
		else
			delete[] start;
		start = nullptr;
		finish = nullptr;
		size = 0;
		capacity = 0;
	}

	T &operator[](size_t index)
	{
		return start[index];
	}

	T *begin()
	{
		return start;
	}
	T *end()
	{
		return finish;
	}

	size_t Size() const
	{
		return size;
	}
	size_t Capacity() const
	{
		return capacity;
	}
	void PushBack(const T &value)
	{
		if (capacity == 0)
		{
			capacity = 1;
		}
		else if (capacity == size)
		{
			capacity *= 2;
		}
		{
			T *p = new T[capacity];
			// for (size_t i = 0; i < size; i++) {
			// 	p[i] = start[i];
			// }
			copy(start, finish, p);
			finish = p + size;
			if (capacity == 1)
				delete start;
			else
				delete[] start;
			start = p;
		}
		size++;
		*finish = value;
		finish++;
	}

private:
	size_t size;
	size_t capacity;
	T *start;
	T *finish;
};
