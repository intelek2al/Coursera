#pragma once

#include <stdexcept>
#include <exception>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0) {
		size = a_size;
		if (a_size > capacity)
			throw invalid_argument("");
		finish = &start[size - 1] + 1;

	}

	T& operator[](size_t index) {
		if (index >= size)
			throw invalid_argument("");
		return start[index];
	}
	const T& operator[](size_t index) const {
		if (index >= size)
			throw invalid_argument("");
		return start[index];
	}

	auto begin() {
		return start.begin();
	}
	auto end() {
		return start.begin()+ size;
	}
	auto begin() const {
		return start.begin();
	}
	auto end() const {
		return start.begin()+ size;
	}

	size_t Size() const {
		return size;
	}
	size_t Capacity() const {
		return capacity;
	}

	void PushBack(const T& value) {
		if (size >= capacity)
			throw overflow_error("");
		size++;
		*finish = value;
		finish++;
	}
	T PopBack() {
		if (size == 0) {
			throw underflow_error("");
		}
		size--;
		finish--;
		return *finish;
	}

private:
	array<T, N> start;
	T *finish;
	size_t capacity = N;
	size_t size;
};

