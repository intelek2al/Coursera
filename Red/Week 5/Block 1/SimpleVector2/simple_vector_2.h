#include <iostream>
#include <cstdint>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector
{
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size) : data(new T[size]), size(size), capacity(size)
	{
	}
	~SimpleVector()
	{
		delete[] data;
	}

	T &operator[](size_t index)
	{
		return data[index];
	}

	T *begin() const
	{
		return data;
	}

	T *end() const
	{
		return data + size;
	}

	size_t Size() const
	{
		return size;
	}

	size_t Capacity() const
	{
		return capacity;
	}

	void PushBack(T value)
	{
		if (size >= capacity)
		{
			auto new_cap = capacity == 0 ? 1 : 2 * capacity;
			auto new_data = new T[new_cap];
			move(begin(), end(), new_data);
			delete[] data;
			data = new_data;
			capacity = new_cap;
		}
		data[size++] = move(value);
	}

	// void PushBack(T &&value)
	// {
	// 	if (size >= capacity)
	// 	{
	// 		auto new_cap = capacity == 0 ? 1 : 2 * capacity;
	// 		auto new_data = new T[new_cap];
	// 		copy(begin(), end(), new_data);
	// 		delete[] data;
	// 		data = new_data;
	// 		capacity = new_cap;
	// 	}
	// 	data[size++] = value;
	// }

private:
	T *data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};
